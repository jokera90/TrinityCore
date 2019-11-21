#include "ScriptPCH.h"
#include "AccountMgr.h"
#include "Chat.h"
#include "DatabaseEnv.h"
#include "ScriptedGossip.h"
#include "GossipDef.h"
#include "ScriptMgr.h"
#include "ScriptedEscortAI.h"
#include "ScriptedCreature.h"
#include "Define.h"
#include "Player.h"
#include "WorldSession.h"
#include "MotionMaster.h"
#include "Player.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "ScriptMgr.h"
#include "CreatureAI.h"
// .. more includes
#define DEFAULT_GOSSIP_MESSAGE              0xffffff
#define dbname "test"
class Npc_helper : public CreatureScript
{
public:
	Npc_helper() : CreatureScript("chrs2"){}

	class Npc_helperAI : public ScriptedAI
	{
	public:
		Npc_helperAI(Creature* creature) : ScriptedAI(creature){}
		bool Main(Player* player, Creature* creature)
		{
			AddGossipItemFor(player, 10, "Valhala", 1, 1);
			AddGossipItemFor(player, 10, "Odin", 1, 1);
			AddGossipItemFor(player, 10, "VendorCode", 1, 10, "",0, true);
			AddGossipItemFor(player, 10, "Actionhouse test", 1, 2);
			AddGossipItemFor(player, 10, "Actionhouse test", 1, 3);
			SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
			return true;

		}
		bool GossipHello(Player* player) override
		{
			if (player->IsGameMaster())
				return Main(player, me);
			else
				return OnGossipHello(player, me);
		}
		static bool OnGossipHello(Player* player, Creature* creature)
		{
			AddGossipItemFor(player, 10, "Earth", 1, 1);
			AddGossipItemFor(player, 10, "SuperMen", 1, 1);
			SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, creature->GetGUID());
			return true;
		}
		bool GossipSelect(Player* player, uint32 menuid, uint32 gossipListId) override
		{
			uint32 sender = player->PlayerTalkClass->GetGossipOptionSender(gossipListId);
			uint32 action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
			return OnGossipSelect(player, me, sender, action);
		}
		static bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action)
		{
			ClearGossipMenuFor(player);
			switch (action)
			{
			case 1:
			{
				player->GetSession()->SendNotification("Strahil e umen");
				OnGossipHello(player, creature);
				break;
			}
			case 2:
				player->GetSession()->SendAuctionHello(creature->GetGUID(), creature);
				break;
			case 3:
				player->GetSession()->SendListInventory(creature->GetGUID(), 9999998);
				break;

			}
			return true;
		}
		bool GossipSelectCode(Player* player, uint32 menuid, uint32 gossipListId, const char* code)
		{
			uint32 sender = player->PlayerTalkClass->GetGossipOptionSender(gossipListId);
			uint32 action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
			
			return OnGossipSelectCode(player, me, sender, action, code);
		}
		static bool OnGossipSelectCode(Player*player, Creature* creature, uint32 sender, uint32 action, const char* code)
		{
			switch (action)
			{
			case 10:
			{
				uint32 vendorentry = atol(code);
				player->GetSession()->SendListInventory(creature->GetGUID(), vendorentry);
				player->GetSession()->SendNotification("%u", vendorentry);
				break;

			}
			}
			return true;
		}
		
	};
	CreatureAI* GetAI(Creature* creature) const override
	{
		return new Npc_helperAI(creature);
	}

};
class npc_kalecgos2 : public CreatureScript
{
public:
	npc_kalecgos2() : CreatureScript("chrs") { }

	class npc_kalecgos2AI : public ScriptedAI
	{
	public:
		npc_kalecgos2AI(Creature* creature) : ScriptedAI(creature) { }


		bool GossipSelect(Player* player, uint32 /*menuId*/, uint32 gossipListId) override
		{
			uint32 const action = player->PlayerTalkClass->GetGossipOptionAction(gossipListId);
			ClearGossipMenuFor(player);
			switch (action)
			{
			case GOSSIP_ACTION_INFO_DEF:
				AddGossipItemFor(player, GOSSIP_ICON_CHAT,"test", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
				SendGossipMenuFor(player, 12500, me->GetGUID());
				break;
			case GOSSIP_ACTION_INFO_DEF + 1:
				AddGossipItemFor(player, GOSSIP_ICON_CHAT, "test2", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
				SendGossipMenuFor(player, 12502, me->GetGUID());
				break;
			case GOSSIP_ACTION_INFO_DEF + 2:
				AddGossipItemFor(player, GOSSIP_ICON_CHAT, "test3", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
				SendGossipMenuFor(player, 12606, me->GetGUID());
				break;
			case GOSSIP_ACTION_INFO_DEF + 3:
				AddGossipItemFor(player, GOSSIP_ICON_CHAT, "test4", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
				SendGossipMenuFor(player, 12607, me->GetGUID());
				break;
			case GOSSIP_ACTION_INFO_DEF + 4:
				SendGossipMenuFor(player, 12608, me->GetGUID());
				break;
			}

			return true;
		}

		bool GossipHello(Player* player) override
		{
			AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Seriozno li?", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);
			SendGossipMenuFor(player, 12498, me->GetGUID());

			return true;
		}

	};

	CreatureAI* GetAI(Creature* creature) const override
	{
		return new npc_kalecgos2AI(creature);
	}
};
void AddSC_Fuck_up()
{
	new Npc_helper();
	new npc_kalecgos2();
}
/*
class guard90 : public CreatureScript
{
    public:
      guard90() : CreatureScript("chrs2") { }

	  class guard90AI : public ScriptedAI
	  {
	  public:
		  guard90AI(Creature* creature) : ScriptedAI(creature){ }

        void MainMenu(Player* player)
        {
            QueryResult result = CharacterDatabase.PQuery("SELECT gender FROM characters WHERE guid = %u", player->GetGUID());
            if(!result)
            {
                CloseGossipMenuFor(player);
            }
            Field* fields = result->Fetch();
            uint32 gen = fields[0].GetUInt8();

            char dpz [256];
            char vpz [256];
            char kills [256];
            char gend [256];
            switch (gen)
            {
                case 1:
                    sprintf(gend, "|cffFF0066Sex: |CFFFF0000Female");
                    break;
                case 0:
                    sprintf(gend, "|cffFF0066Sex: |CFFFF0000Male");
                    break;
                default:
                    sprintf(gend, "|cffFF0066Sex: |CFFFF0000Unknown");
                    break;
            }
            sprintf(dpz, "|cffFF0066Honor: |CFFFF0000%u|r", player->GetHonorPoints());
            sprintf(vpz, "|CffFF0066Arena: |CFFFF0000%u|r", player->GetArenaPoints());
            sprintf(kills, "|cffFF0066Kills: |CFFFF0000%u|r", player->GetUInt32Value(PLAYER_FIELD_LIFETIME_HONORABLE_KILLS));
         AddGossipItemFor(player,GOSSIP_ICON_DOT, "Character Settings", GOSSIP_SENDER_MAIN, 15);
         //AddGossipItemFor(player,GOSSIP_ICON_DOT, dpz, GOSSIP_SENDER_MAIN, 15);
         //AddGossipItemFor(player,GOSSIP_ICON_DOT, vpz, GOSSIP_SENDER_MAIN, 15);
        // AddGossipItemFor(player,GOSSIP_ICON_DOT, kills, GOSSIP_SENDER_MAIN, 15);
       //  AddGossipItemFor(player,GOSSIP_ICON_DOT, gend, GOSSIP_SENDER_MAIN, 15);
         AddGossipItemFor(player,GOSSIP_ICON_DOT, "|cffFF0066Reset |CFFFF0000Spells", GOSSIP_SENDER_MAIN, 1);
         AddGossipItemFor(player,GOSSIP_ICON_DOT, "|cffFF0066Reset |CFFFF0000Talents", GOSSIP_SENDER_MAIN, 2);
		 AddGossipItemFor(player, 10, "vendorcode", 1, 3, "", 0, true);
            player->PlayerTalkClass->SendGossipMenu(1, me->GetGUID());
        }

        bool GossipHello(Player* player)
        {
            MainMenu(player);
            return true;
        }
        
        bool OnGossipSelect(Player* player, Creature* creature, uint32 uiSender, uint32 uiAction)
        {
            player->PlayerTalkClass->ClearMenus();
            
            switch(uiAction)
            {
                case 1:
                    player->ResetSpells();
                    MainMenu(player);
                    break;
                case 2:
                    player->ResetTalents();
                    MainMenu(player);
                    break;
                case 15:
                        MainMenu(player);
                        break;
                return true;
            }
        }
		void OnGossipSelectCode(Player* player, Creature* creature, uint32 action, uint32 sender, const char*code)
		{
			switch (action)
			{
			case 3:
			{
				uint32 vendorentry = atol(code);
				player->GetSession()->SendListInventory(player->GetGUID(), vendorentry);
				break;
			}
			}

		}
		CreatureAI* GetAI(Creature* creature) const override
		{
			return new guard90AI(creature);
		}
};

void AddSC_chrs2()
{
   new guard90();
}*/