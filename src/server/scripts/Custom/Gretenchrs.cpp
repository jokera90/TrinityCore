#include "ScriptPCH.h"
#include "GossipDef.h"
#include "ScriptedGossip.h"
#include "WorldSession.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"




class chrs : public CreatureScript
{
public:
	chrs() : CreatureScript("chrs") { }

	void MainMenu(Player * player, Creature * creature)
	{
		char dpz[256];
		char vpz[256];
		char kills[256];
		char guildid[256];
		char area[256];
		char map[256];
		char phasemask[256];
		char zone[256];
		char x[256];
		char y[256];
		char z[256];
		char name[256];
		sprintf(name, "Name: %s", player->GetSession()->GetPlayerName().c_str());
		sprintf(zone, "Zone: %u", player->GetZoneId());
		sprintf(area, "Area: %u", player->GetAreaId());
		sprintf(dpz, "|cffFF0066Honor: |CFFFF0000%u|r", player->GetHonorPoints());
		sprintf(vpz, "|CffFF0066Arena: |CFFFF0000%u|r", player->GetArenaPoints());
		sprintf(kills, "|cffFF0066Kills: |CFFFF0000%u|r", player->GetUInt32Value(PLAYER_FIELD_LIFETIME_HONORABLE_KILLS));
		sprintf(guildid, "|cffFF0066Guild : |CFFFF0000%u|r", player->GetUInt32Value(PLAYER_GUILDID));
		sprintf(map, "|cffFF0066Map : |CFFFF0000%u|r", player->GetSession()->GetPlayer()->GetMapId());
		sprintf(phasemask, "|cffFF0066Phasemask: |CFFFF0000%u|r", player->GetPhaseMask());
		sprintf(x, "X: %f", player->GetSession()->GetPlayer()->GetPositionX());
		sprintf(y, "Y: %f", player->GetSession()->GetPlayer()->GetPositionY());
		sprintf(z, "Z: %f", player->GetSession()->GetPlayer()->GetPositionZ());
		AddGossipItemFor(player,GOSSIP_ICON_DOT, "Character Settings", GOSSIP_SENDER_MAIN, 15);
		AddGossipItemFor(player,GOSSIP_ICON_DOT, name, GOSSIP_SENDER_MAIN, 15);
		AddGossipItemFor(player,GOSSIP_ICON_DOT, dpz, GOSSIP_SENDER_MAIN, 15);
		AddGossipItemFor(player,GOSSIP_ICON_DOT, vpz, GOSSIP_SENDER_MAIN, 15);
		AddGossipItemFor(player,GOSSIP_ICON_DOT, kills, GOSSIP_SENDER_MAIN, 15);
		AddGossipItemFor(player,GOSSIP_ICON_DOT, guildid, GOSSIP_SENDER_MAIN, 15);
		AddGossipItemFor(player,GOSSIP_ICON_DOT, zone, GOSSIP_SENDER_MAIN, 15);
		AddGossipItemFor(player,GOSSIP_ICON_DOT, area, GOSSIP_SENDER_MAIN, 15);
		AddGossipItemFor(player,GOSSIP_ICON_DOT, map, GOSSIP_SENDER_MAIN, 15);
		AddGossipItemFor(player,GOSSIP_ICON_DOT, x, GOSSIP_SENDER_MAIN, 15);
		AddGossipItemFor(player,GOSSIP_ICON_DOT, y, GOSSIP_SENDER_MAIN, 15);
		AddGossipItemFor(player,GOSSIP_ICON_DOT, z, GOSSIP_SENDER_MAIN, 15);
		AddGossipItemFor(player,GOSSIP_ICON_DOT, phasemask, GOSSIP_SENDER_MAIN, 15);
		AddGossipItemFor(player,GOSSIP_ICON_DOT, "|cffFF0066Reset |CFFFF0000Spells", GOSSIP_SENDER_MAIN, 1);
		AddGossipItemFor(player,GOSSIP_ICON_DOT, "|cffFF0066Reset |CFFFF0000Talents", GOSSIP_SENDER_MAIN, 2);
		SendGossipMenuFor(player,DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
	}

	bool OnGossipHello(Player* player, Creature* creature)
	{
		MainMenu(player, creature);
		return true;
	}

	bool OnGossipSelect(Player* player, Creature* creature, uint32 uiSender, uint32 uiAction)
	{
		player->PlayerTalkClass->ClearMenus();

		switch (uiAction)
		{
		case 1:
			player->ResetSpells();
			MainMenu(player, creature);
			break;
		case 2:
			player->ResetTalents();
			MainMenu(player, creature);
			break;
		case 15:
			MainMenu(player, creature);
			break;
			return true;
		}
	}
	CreatureAI* GetAI(Creature* creature) const override
	{
		return 0;
	}
};
void AddSC_chrs()
{
	new chrs();
}