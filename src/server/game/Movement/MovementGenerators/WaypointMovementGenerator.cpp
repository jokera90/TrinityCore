/*
 * Copyright (C) 2008-2017 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2005-2009 MaNGOS <http://getmangos.com/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "WaypointMovementGenerator.h"
#include "Creature.h"
#include "CreatureAI.h"
#include "Log.h"
#include "MapManager.h"
#include "MoveSpline.h"
#include "MoveSplineInit.h"
#include "ObjectMgr.h"
#include "Player.h"
#include "Transport.h"
#include "WaypointDefines.h"
#include "WaypointManager.h"
#include "World.h"

WaypointMovementGenerator<Creature>::WaypointMovementGenerator(WaypointPath& path, bool repeating)
{
    _path = &path;
    _nextMoveTime = 0;
    _recalculateSpeed = false;
    _isArrivalDone = false;
    _pathId = 0;
    _repeating = repeating;
    _loadedFromDB = false;
    _stalled = false;
    _done = false;
}

void WaypointMovementGenerator<Creature>::LoadPath(Creature* creature)
{
    if (_loadedFromDB)
    {
        if (!_pathId)
            _pathId = creature->GetWaypointPath();

        _path = sWaypointMgr->GetPath(_pathId);
    }

    if (!_path)
    {
        // No path id found for entry
        TC_LOG_ERROR("sql.sql", "WaypointMovementGenerator::LoadPath: creature %s (Entry: %u GUID: %u DB GUID: %u) doesn't have waypoint path id: %u", creature->GetName().c_str(), creature->GetEntry(), creature->GetGUID().GetCounter(), creature->GetSpawnId(), _pathId);
        return;
    }

    _nextMoveTime.Reset(3000);

    if (CanMove(creature))
        StartMoveNow(creature);
}

void WaypointMovementGenerator<Creature>::DoInitialize(Creature* creature)
{
    _done = false;
    LoadPath(creature);
}

void WaypointMovementGenerator<Creature>::DoFinalize(Creature* creature)
{
    creature->ClearUnitState(UNIT_STATE_ROAMING | UNIT_STATE_ROAMING_MOVE);
    creature->SetWalk(false);
}

void WaypointMovementGenerator<Creature>::DoReset(Creature* creature)
{
    if (!_done && CanMove(creature))
        StartMoveNow(creature);
    else if (_done)
    {
        // mimic IdleMovementGenerator
        if (!creature->IsStopped())
            creature->StopMoving();
    }
}

void WaypointMovementGenerator<Creature>::OnArrived(Creature* creature)
{
    if (!_path || _path->nodes.empty())
        return;

    WaypointNode const &waypoint = _path->nodes.at(_currentNode);
    if (waypoint.delay)
    {
        creature->ClearUnitState(UNIT_STATE_ROAMING_MOVE);
        _nextMoveTime.Reset(waypoint.delay);
    }

    if (waypoint.eventId && urand(0, 99) < waypoint.eventChance)
    {
        TC_LOG_DEBUG("maps.script", "Creature movement start script %u at point %u for %s.", waypoint.eventId, _currentNode, creature->GetGUID().ToString().c_str());
        creature->ClearUnitState(UNIT_STATE_ROAMING_MOVE);
        creature->GetMap()->ScriptsStart(sWaypointScripts, waypoint.eventId, creature, nullptr);
    }

    // inform AI
    if (creature->AI())
    {
        creature->AI()->MovementInform(WAYPOINT_MOTION_TYPE, _currentNode);

        ASSERT(_currentNode < _path->nodes.size(), "WaypointMovementGenerator::OnArrived: tried to reference a node id (%u) which is not included in path (%u)", _currentNode, _path->id);
        creature->AI()->WaypointReached(_path->nodes[_currentNode].id, _path->id);
    }

    creature->UpdateWaypointID(_currentNode);
}

bool WaypointMovementGenerator<Creature>::StartMove(Creature* creature)
{
    if (!creature || !creature->IsAlive())
        return true;

    if (_done || !_path || _path->nodes.empty())
        return true;

    // if the owner is the leader of its formation, check members status
    if (creature->IsFormationLeader() && !creature->IsFormationLeaderMoveAllowed())
    {
        _nextMoveTime.Reset(1000);
        return true;
    }

    bool transportPath = creature->HasUnitMovementFlag(MOVEMENTFLAG_ONTRANSPORT) && !creature->GetTransGUID().IsEmpty();

    if (_isArrivalDone)
    {
        if ((_currentNode == _path->nodes.size() - 1) && !_repeating) // If that's our last waypoint
        {
            WaypointNode const &waypoint = _path->nodes.at(_currentNode);

            float x = waypoint.x;
            float y = waypoint.y;
            float z = waypoint.z;
            float o = creature->GetOrientation();

            if (!transportPath)
                creature->SetHomePosition(x, y, z, o);
            else
            {
                if (Transport* trans = creature->GetTransport())
                {
                    o -= trans->GetOrientation();
                    creature->SetTransportHomePosition(x, y, z, o);
                    trans->CalculatePassengerPosition(x, y, z, &o);
                    creature->SetHomePosition(x, y, z, o);
                }
                else
                    transportPath = false;
                // else if (vehicle) - this should never happen, vehicle offsets are const
            }
            _done = true;
            return true;
        }

        _currentNode = (_currentNode + 1) % _path->nodes.size();

        // inform AI
        if (creature->AI())
        {
            ASSERT(_currentNode < _path->nodes.size(), "WaypointMovementGenerator::StartMove: tried to reference a node id (%u) which is not included in path (%u)", _currentNode, _path->id);
            creature->AI()->WaypointStarted(_path->nodes[_currentNode].id, _path->id);
        }
    }

    WaypointNode const &waypoint = _path->nodes.at(_currentNode);
    Position formationDest(waypoint.x, waypoint.y, waypoint.z, (waypoint.orientation && waypoint.delay) ? waypoint.orientation : 0.0f);

    _isArrivalDone = false;
    _recalculateSpeed = false;

    creature->AddUnitState(UNIT_STATE_ROAMING_MOVE);

    Movement::MoveSplineInit init(creature);

    //! If creature is on transport, we assume waypoints set in DB are already transport offsets
    if (transportPath)
    {
        init.DisableTransportPathTransformations();
        if (TransportBase* trans = creature->GetDirectTransport())
        {
            float orientation = formationDest.GetOrientation();
            trans->CalculatePassengerPosition(formationDest.m_positionX, formationDest.m_positionY, formationDest.m_positionZ, &orientation);
            formationDest.SetOrientation(orientation);
        }
    }

    //! Do not use formationDest here, MoveTo requires transport offsets due to DisableTransportPathTransformations() call
    //! but formationDest contains global coordinates
    init.MoveTo(waypoint.x, waypoint.y, waypoint.z);

    //! Accepts angles such as 0.00001 and -0.00001, 0 must be ignored, default value in waypoint table
    if (waypoint.orientation && waypoint.delay)
        init.SetFacing(waypoint.orientation);

    switch (waypoint.moveType)
    {
        case WAYPOINT_MOVE_TYPE_LAND:
            init.SetAnimation(Movement::ToGround);
            break;
        case WAYPOINT_MOVE_TYPE_TAKEOFF:
            init.SetAnimation(Movement::ToFly);
            break;
        case WAYPOINT_MOVE_TYPE_RUN:
            init.SetWalk(false);
            break;
        case WAYPOINT_MOVE_TYPE_WALK:
            init.SetWalk(true);
            break;
        default:
            break;
    }

    init.Launch();

    // inform formation
    creature->SignalFormationMovement(formationDest, waypoint.id, waypoint.moveType, (waypoint.orientation && waypoint.delay) ? true : false);

    return true;
}

bool WaypointMovementGenerator<Creature>::DoUpdate(Creature* creature, uint32 diff)
{
    if (!creature || !creature->IsAlive())
        return true;

    if (_done || !_path || _path->nodes.empty())
        return true;

    if (_stalled || creature->HasUnitState(UNIT_STATE_NOT_MOVE) || creature->IsMovementPreventedByCasting())
    {
        creature->StopMoving();
        return true;
    }

    if (!_nextMoveTime.Passed())
    {
        _nextMoveTime.Update(diff);
        if (_nextMoveTime.Passed())
            return StartMoveNow(creature);
    }
    else
    {
        // Set home position at place on waypoint movement.
        if (!creature->HasUnitMovementFlag(MOVEMENTFLAG_ONTRANSPORT) || creature->GetTransGUID().IsEmpty())
            creature->SetHomePosition(creature->GetPosition());

        if (creature->movespline->Finalized())
        {
            OnArrived(creature);
            _isArrivalDone = true;

            if (_nextMoveTime.Passed())
                return StartMove(creature);
        }
        else if (_recalculateSpeed)
        {
            if (_nextMoveTime.Passed())
                StartMove(creature);
        }
    }
    return true;
 }

void WaypointMovementGenerator<Creature>::MovementInform(Creature* creature)
{
    if (creature->AI())
        creature->AI()->MovementInform(WAYPOINT_MOTION_TYPE, _currentNode);
}

bool WaypointMovementGenerator<Creature>::GetResetPos(Creature*, float& x, float& y, float& z)
{
    // prevent a crash at empty waypoint path.
    if (!_path || _path->nodes.empty())
        return false;

    WaypointNode const &waypoint = _path->nodes.at(_currentNode);

    x = waypoint.x;
    y = waypoint.y;
    z = waypoint.z;
    return true;
}

void WaypointMovementGenerator<Creature>::Pause(uint32 timer/* = 0*/)
{
    _stalled = timer ? false : true;
    _nextMoveTime.Reset(timer ? timer : 1);
}

void WaypointMovementGenerator<Creature>::Resume(uint32 overrideTimer/* = 0*/)
{
    _stalled = false;
    if (overrideTimer)
        _nextMoveTime.Reset(overrideTimer);
}

bool WaypointMovementGenerator<Creature>::CanMove(Creature* creature)
{
    return _nextMoveTime.Passed() && !creature->HasUnitState(UNIT_STATE_NOT_MOVE) && !creature->IsMovementPreventedByCasting();
}

//----------------------------------------------------//

#define FLIGHT_TRAVEL_UPDATE 100
#define TIMEDIFF_NEXT_WP 250
#define SKIP_SPLINE_POINT_DISTANCE_SQ (40.f * 40.f)
#define PLAYER_FLIGHT_SPEED 32.0f

uint32 FlightPathMovementGenerator::GetPathAtMapEnd() const
{
    if (_currentNode >= _path.size())
        return _path.size();

    uint32 curMapId = _path[_currentNode]->MapID;
    for (uint32 itr = _currentNode; itr < _path.size(); ++itr)
        if (_path[itr]->MapID != curMapId)
            return itr;

    return _path.size();
}

bool IsNodeIncludedInShortenedPath(TaxiPathNodeEntry const* p1, TaxiPathNodeEntry const* p2)
{
    return p1->MapID != p2->MapID || std::pow(p1->LocX - p2->LocX, 2) + std::pow(p1->LocY - p2->LocY, 2) > SKIP_SPLINE_POINT_DISTANCE_SQ;
}

void FlightPathMovementGenerator::LoadPath(Player* player)
{
    _pointsForPathSwitch.clear();
    std::deque<uint32> const& taxi = player->m_taxi.GetPath();
    for (uint32 src = 0, dst = 1; dst < taxi.size(); src = dst++)
    {
        uint32 path, cost;
        sObjectMgr->GetTaxiPath(taxi[src], taxi[dst], path, cost);
        if (path > sTaxiPathNodesByPath.size())
            return;

        TaxiPathNodeList const& nodes = sTaxiPathNodesByPath[path];
        if (!nodes.empty())
        {
            TaxiPathNodeEntry const* start = nodes[0];
            TaxiPathNodeEntry const* end = nodes[nodes.size() - 1];
            bool passedPreviousSegmentProximityCheck = false;
            for (uint32 i = 0; i < nodes.size(); ++i)
            {
                if (passedPreviousSegmentProximityCheck || !src || _path.empty() || IsNodeIncludedInShortenedPath(_path[_path.size() - 1], nodes[i]))
                {
                    if ((!src || (IsNodeIncludedInShortenedPath(start, nodes[i]) && i >= 2)) &&
                        (dst == taxi.size() - 1 || (IsNodeIncludedInShortenedPath(end, nodes[i]) && i < nodes.size() - 1)))
                    {
                        passedPreviousSegmentProximityCheck = true;
                        _path.push_back(nodes[i]);
                    }
                }
                else
                {
                    _path.pop_back();
                    --_pointsForPathSwitch.back().PathIndex;
                }
            }
        }

        _pointsForPathSwitch.push_back({ uint32(_path.size() - 1), int32(cost) });
    }
}

void FlightPathMovementGenerator::DoInitialize(Player* player)
{
    Reset(player);
    InitEndGridInfo();
}

void FlightPathMovementGenerator::DoFinalize(Player* player)
{
    // remove flag to prevent send object build movement packets for flight state and crash (movement generator already not at top of stack)
    player->ClearUnitState(UNIT_STATE_IN_FLIGHT);

    player->Dismount();
    player->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_REMOVE_CLIENT_CONTROL | UNIT_FLAG_TAXI_FLIGHT);

    if (player->m_taxi.empty())
    {
        player->getHostileRefManager().setOnlineOfflineState(true);
        // update z position to ground and orientation for landing point
        // this prevent cheating with landing  point at lags
        // when client side flight end early in comparison server side
        player->StopMoving();
        player->SetFallInformation(0, player->GetPositionZ());
    }

    player->RemoveFlag(PLAYER_FLAGS, PLAYER_FLAGS_TAXI_BENCHMARK);
}

void FlightPathMovementGenerator::DoReset(Player* player)
{
    player->getHostileRefManager().setOnlineOfflineState(false);
    player->AddUnitState(UNIT_STATE_IN_FLIGHT);
    player->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_REMOVE_CLIENT_CONTROL | UNIT_FLAG_TAXI_FLIGHT);

    Movement::MoveSplineInit init(player);
    uint32 end = GetPathAtMapEnd();
    for (uint32 i = GetCurrentNode(); i != end; ++i)
    {
        G3D::Vector3 vertice(_path[i]->LocX, _path[i]->LocY, _path[i]->LocZ);
        init.Path().push_back(vertice);
    }
    init.SetFirstPointId(GetCurrentNode());
    init.SetFly();
    init.SetVelocity(PLAYER_FLIGHT_SPEED);
    init.Launch();
}

bool FlightPathMovementGenerator::DoUpdate(Player* player, uint32 /*diff*/)
{
    uint32 pointId = (uint32)player->movespline->currentPathIdx();
    if (pointId > _currentNode)
    {
        bool departureEvent = true;
        do
        {
            DoEventIfAny(player, _path[_currentNode], departureEvent);
            while (!_pointsForPathSwitch.empty() && _pointsForPathSwitch.front().PathIndex <= _currentNode)
            {
                _pointsForPathSwitch.pop_front();
                player->m_taxi.NextTaxiDestination();
                if (!_pointsForPathSwitch.empty())
                {
                    player->UpdateAchievementCriteria(ACHIEVEMENT_CRITERIA_TYPE_GOLD_SPENT_FOR_TRAVELLING, _pointsForPathSwitch.front().Cost);
                    player->ModifyMoney(-_pointsForPathSwitch.front().Cost);
                }
            }

            if (pointId == _currentNode)
                break;

            if (_currentNode == _preloadTargetNode)
                PreloadEndGrid();
            _currentNode += departureEvent ? 1 : 0;
            departureEvent = !departureEvent;
        }
        while (true);
    }

    return _currentNode < (_path.size() - 1);
}

void FlightPathMovementGenerator::SetCurrentNodeAfterTeleport()
{
    if (_path.empty() || _currentNode >= _path.size())
        return;

    uint32 map0 = _path[_currentNode]->MapID;
    for (size_t i = _currentNode + 1; i < _path.size(); ++i)
    {
        if (_path[i]->MapID != map0)
        {
            _currentNode = i;
            return;
        }
    }
}

void FlightPathMovementGenerator::DoEventIfAny(Player* player, TaxiPathNodeEntry const* node, bool departure)
{
    if (uint32 eventid = departure ? node->DepartureEventID : node->ArrivalEventID)
    {
        TC_LOG_DEBUG("maps.script", "Taxi %s event %u of node %u of path %u for player %s", departure ? "departure" : "arrival", eventid, node->NodeIndex, node->PathID, player->GetName().c_str());
        player->GetMap()->ScriptsStart(sEventScripts, eventid, player, player);
    }
}

bool FlightPathMovementGenerator::GetResetPos(Player*, float& x, float& y, float& z)
{
    TaxiPathNodeEntry const* node = _path[_currentNode];
    x = node->LocX;
    y = node->LocY;
    z = node->LocZ;
    return true;
}

void FlightPathMovementGenerator::InitEndGridInfo()
{
    /*! Storage to preload flightmaster grid at end of flight. For multi-stop flights, this will
       be reinitialized for each flightmaster at the end of each spline (or stop) in the flight. */
    uint32 nodeCount = _path.size();        //! Number of nodes in path.
    _endMapId = _path[nodeCount - 1]->MapID; //! MapId of last node
    _preloadTargetNode = nodeCount - 3;
    _endGridX = _path[nodeCount - 1]->LocX;
    _endGridY = _path[nodeCount - 1]->LocY;
}

void FlightPathMovementGenerator::PreloadEndGrid()
{
    // used to preload the final grid where the flightmaster is
    Map* endMap = sMapMgr->FindBaseNonInstanceMap(_endMapId);

    // Load the grid
    if (endMap)
    {
        TC_LOG_DEBUG("misc", "Preloading rid (%f, %f) for map %u at node index %u/%u", _endGridX, _endGridY, _endMapId, _preloadTargetNode, (uint32)(_path.size() - 1));
        endMap->LoadGrid(_endGridX, _endGridY);
    }
    else
        TC_LOG_DEBUG("misc", "Unable to determine map to preload flightmaster grid");
}
