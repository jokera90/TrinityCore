#include "ScriptPCH.h"
#include "GossipDef.h"
#include "ScriptMgr.h"
#include "Player.h"
#include "WorldSession.h"
#include "ScriptedGossip.h"




class multi_gem : public CreatureScript
{
	public:
		multi_gem() : CreatureScript("multi_gem"){}

		class multi_genAI : public ScriptedAI
		{
		public:
			multi_genAI(Creature* creature) : ScriptedAI(creature){}

			bool GossipHello(Player* player) override
			{
				return OnGossipHello(player, me);
			}

		bool OnGossipHello(Player * player, Creature* creature)
		{
			AddGossipItemFor(player, 4, "|cff00ff00|TInterface\\icons\\INV_JEWELCRAFTING_GEM_38:24|t|r Yellow", GOSSIP_SENDER_MAIN, 0);
			AddGossipItemFor(player,4, "|cff00ff00|TInterface\\icons\\INV_JEWELCRAFTING_GEM_42:24|t|r Blue", GOSSIP_SENDER_MAIN, 1);
			AddGossipItemFor(player,4, "|cff00ff00|TInterface\\icons\\INV_JEWELCRAFTING_GEM_37:24|t|r Red", GOSSIP_SENDER_MAIN, 2);
			AddGossipItemFor(player,4, "|cff00ff00|TInterface\\icons\\INV_JEWELCRAFTING_GEM_40:24|t|r Purple", GOSSIP_SENDER_MAIN, 3);
			AddGossipItemFor(player,4, "|cff00ff00|TInterface\\icons\\INV_JEWELCRAFTING_GEM_41:24|t|r Green", GOSSIP_SENDER_MAIN, 4);
			AddGossipItemFor(player,4, "|cff00ff00|TInterface\\icons\\INV_JEWELCRAFTING_GEM_39:24|t|r Orange", GOSSIP_SENDER_MAIN, 5);
			AddGossipItemFor(player,4, "|cff00ff00|TInterface\\icons\\INV_JEWELCRAFTING_GEM_31:24|t|r Meta", GOSSIP_SENDER_MAIN, 6);
			AddGossipItemFor(player,4, "|cff00ff00|TInterface\\icons\\spell_magic_lesserinvisibilty:24|t|r Nevermind", GOSSIP_SENDER_MAIN, 7);
			AddGossipItemFor(player,4, "Code", GOSSIP_SENDER_MAIN,9,"",0,true);
			SendGossipMenuFor(player,9425, creature->GetGUID());
			return true;
		}
		bool GossipSelect(Player* player, uint32 menuid, uint32 gossipListId) override
		{
			uint32 action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
			uint32 sender = player->PlayerTalkClass->GetGossipOptionSender(gossipListId);
			return OnGossipSelect(player, me, sender , action);
		}
		bool OnGossipSelect(Player * Player, Creature * Creature, uint32 sender, uint32 action)
		{
			if(!Player)
				return true;
			
			WorldSession * m_session = Player->GetSession();
			
			switch(action)
			{
				case 0:
					{
						m_session->SendListInventory(Creature->GetGUID(),54);
					}break;
				case 1:
					{

						Player->GetSession()->GetCurrentVendor();
						Player->GetSession()->SetCurrentVendor(54);
						m_session->SendListInventory(Creature->GetGUID(), 54);
						Player->PlayerTalkClass->SendCloseGossip();
					}break;
				case 2:
					{
						Player->GetSession()->SetCurrentVendor(500092);
						m_session->SendListInventory(Creature->GetGUID(),500092);
						Player->PlayerTalkClass->SendCloseGossip();
					}break;
				case 3:
					{
						m_session->SendListInventory(Creature->GetGUID(),500073);
						
					}break;
				case 4:
					{			
						m_session->SendListInventory(Creature->GetGUID(), 500041);
				    }break;
				case 5:
					{
						m_session->SendListInventory(Creature->GetGUID(),500067);
						
					}break;
				case 6:
					{
						m_session->SendListInventory(Creature->GetGUID(),2500062);
					}break;
				case 7: // Close Gossips
					{
						Player->PlayerTalkClass->SendCloseGossip();
					}break;
			}
			return true;
		}
		bool GossipSelectCode(Player* player, uint32 menuid, uint32 gossipListId, const char* code) override
		{
			uint32 action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
			uint32 sender = player->PlayerTalkClass->GetGossipOptionSender(gossipListId);
			return OnGossipSelectCode(player, me, sender, action, code);
		}
		bool OnGossipSelectCode(Player* player, Creature* Creature, uint32 sender, uint32 action, const char* code)
		{
			if (!player)
			return true; 

			WorldSession * m_session = player->GetSession();

			switch (action)
			{
			case 9:
			{
			    uint32 entry = atoi(code);
				m_session->SendListInventory(Creature->GetGUID(), entry);
				m_session->SendNotification("%u", entry);
				break;
			}
			
			}
			return true;
		}
		};
		CreatureAI* GetAI(Creature* creature) const override
		{
			return new multi_genAI(creature);
		}
};

void AddSC_multi_gem()
{
	new multi_gem();
}