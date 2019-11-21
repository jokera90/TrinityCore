#include "ScriptPCH.h"
#include "Chat.h"
#include "WorldSession.h"
#include  "ScriptedGossip.h"
#include "GossipDef.h"
#include "DBCStores.h"
#include "Item.h"
/*
<--------------------------------------------------------------------------->
- Developer(s): Ghostcrawler336
- Made By??
- Complete: %0
- ScriptName: 'World chat'
- Comment: Tested on 3.3.5a.
- Updated By Obitus on February 18th, 2016
<--------------------------------------------------------------------------->
*/

#include "ScriptMgr.h"
#include "Chat.h"
#include "Player.h"
#include "Common.h"

/* Colors */
#define MSG_COLOR_ORANGE "|cffFFA500"
#define MSG_COLOR_DARKORANGE "|cffFF8C00"
#define MSG_COLOR_RED "|cffFF0000"
#define MSG_COLOR_LIGHTRED "|cffD63931"
#define MSG_COLOR_ROYALBLUE "|cff4169E1"
#define MSG_COLOR_LIGHTBLUE "|cffADD8E6"
#define MSG_COLOR_YELLOW "|cffFFFF00"
#define MSG_COLOR_GREEN "|cff008000"
#define MSG_COLOR_PURPLE "|cffDA70D6"
#define MSG_COLOR_WHITE  "|cffffffff"
#define MSG_COLOR_SUBWHITE  "|cffbbbbbb"

/* Ranks */
#define ADMINISTRATOR "Admin"
#define HEADGM "Head GM"
#define GAMEMASTER "GM"
#define DEVELOPER "Developer"
#define OWNER "Owner"
#define VIP "Vip"
#define PLAYER "Player"
#define EVENTM "Event Master"
/*
class World_Chat : public CommandScript
{
public:
	World_Chat() : CommandScript("World_Chat") { }


	std::vector<ChatCommand> GetCommands() const override
	{
		static std::vector<ChatCommand> WorldChatCommandTable =
		{
			{ "world",  rbac::RBAC_PERM_COMMAND_WORLD_CHAT, false, &HandleWorldChatCommand, "" }
		};

		return WorldChatCommandTable;
	}

	static bool HandleWorldChatCommand(ChatHandler * pChat, const char * msg)
	{
		if (!*msg)
			return false;

		Player * player = pChat->GetSession()->GetPlayer();
		char message[1024];

		switch (player->GetSession()->GetSecurity())
		{
		case SEC_PLAYER:
			snprintf(message, 1024, "[World][Player][%s%s|r]: %s%s|r", MSG_COLOR_WHITE, player->GetName().c_str(), MSG_COLOR_LIGHTBLUE, msg);
			sWorld->SendGlobalText(message, NULL);
			break;

		/*case SEC_VIP:
			snprintf(message, 1024, "[World][Vip][%s%s|r]: %s%s|r", MSG_COLOR_WHITE, player->GetName().c_str(), MSG_COLOR_PURPLE, msg);
			sWorld->SendGlobalText(message, NULL);
			break;

		case SEC_GAMEMASTER:
			snprintf(message, 1024, "[World][GM][%s%s|r]: %s%s|r", MSG_COLOR_WHITE, player->GetName().c_str(), MSG_COLOR_YELLOW, msg);
			sWorld->SendGlobalText(message, NULL);
			break;

		/*case SEC_EVENTM:
			snprintf(message, 1024, "[World][Event Master][%s%s|r]: %s%s|r", MSG_COLOR_WHITE, player->GetName().c_str(), MSG_COLOR_ORANGE, msg);
			sWorld->SendGlobalText(message, NULL);
			break;
			
		case SEC_HEADGM:
			snprintf(message, 1024, "[World][Head GM][%s%s|r]: %s%s|r", MSG_COLOR_WHITE, player->GetName().c_str(), MSG_COLOR_GREEN, msg);
			sWorld->SendGlobalText(message, NULL);
			break;

		case SEC_DEVELOPER:
			snprintf(message, 1024, "[World][Developer][%s%s|r]: %s%s|r", MSG_COLOR_WHITE, player->GetName().c_str(), MSG_COLOR_ROYALBLUE, msg);
			sWorld->SendGlobalText(message, NULL);
			break;
			
		case SEC_ADMINISTRATOR:
			snprintf(message, 1024, "[World][Admin][%s%s|r]: %s%s|r", MSG_COLOR_WHITE, player->GetName().c_str(), MSG_COLOR_RED, msg);
			sWorld->SendGlobalText(message, NULL);
			break;

		/*case SEC_OWNER:
			snprintf(message, 1024, "[World][Owner][%s%s|r]: %s%s|r", MSG_COLOR_WHITE, player->GetName().c_str(), MSG_COLOR_RED, msg);
			sWorld->SendGlobalText(message, NULL);
			break;

		case SEC_CONSOLE:
			snprintf(message, 1024, "[World][%sAdministrator|r][%s%s|r]: %s%s|r", MSG_COLOR_RED, MSG_COLOR_LIGHTRED, player->GetName().c_str(),
				MSG_COLOR_LIGHTBLUE, msg);
			sWorld->SendGlobalText(message, NULL);
			break;

		}
		return true;
	}
};

void AddSC_World_Chat()
{
	new World_Chat;
}

*/

class NewItemSC : public ItemScript
{
public:
	NewItemSC() : ItemScript("WaRZoNe"){}


	enum Number
	{
		A = 32,
		B = 533,
		C = 266,
		D = -1,
	};
	void Tartas(Player* player, Item* item, const char* code)
	{

			//Player* target = ObjectAccessor::FindPlayerByName(code);
			Player* target = ObjectAccessor::FindConnectedPlayerByName(code);
			char name[256];
			char gender[256];
			char guild[256];
			char kills[256];
			char honor[256];
			char arena[256];
			char map[256];
			char x[256];
			char y[256];
			//char z[256];
			//char test[256];
			//char test2[256];
			std::string mapname = target->FindMap()->GetMapName();
			uint32 playertest = target->GetGUID();
			uint8 gendertest = target->getGender();
			uint32 guildtest = target->GetGuildId();
			uint32 areaId = target->GetAreaId();
			uint32 zoneId = target->GetZoneId();
			std::string areaName = "Unknown";
			std::string zoneName = "Unknown";
			if (AreaTableEntry const* area = sAreaTableStore.LookupEntry(areaId))
			{
				int locale = player->GetSession()->GetSessionDbcLocale();
				areaName = area->area_name[locale];
				if (AreaTableEntry const* zone = sAreaTableStore.LookupEntry(area->zone))
					zoneName = zone->area_name[locale];
			}
			if (playertest == 0)
				sprintf(name, "Name: None");
			else
				sprintf(name, "Name: %s", target->GetSession()->GetPlayerName().c_str());
			if (gendertest == 0)
				sprintf(gender, "Gender: Male");
			else
				sprintf(gender, "Gender: Female");
			if (guildtest == 0)
				sprintf(guild, "Guild: None");
			else
				sprintf(guild, "Guild: %s", target->GetGuildName().c_str());
			sprintf(kills, "HonorKills: %u", target->GetUInt32Value(PLAYER_FIELD_LIFETIME_HONORABLE_KILLS));
			sprintf(honor, "HonorPoints: %u", target->GetHonorPoints());
			sprintf(arena, "ArenaPoints: %u", target->GetArenaPoints());
			sprintf(map, "Map: %u (%s)", target->GetMapId(), mapname.c_str());
			sprintf(y, "Area: %u %s Zone: %u %s", areaId, areaName.c_str(), zoneId, zoneName.c_str());
			sprintf(x, "X: %f Y:%f Z:%f", target->GetPositionX(), target->GetPositionY(), target->GetPositionZ());
			AddGossipItemFor(player,GOSSIP_ICON_DOT, "Admin Menu", GOSSIP_SENDER_MAIN, 1);
			AddGossipItemFor(player,GOSSIP_ICON_DOT, name, GOSSIP_SENDER_MAIN, 1);
			AddGossipItemFor(player,GOSSIP_ICON_DOT, gender, GOSSIP_SENDER_MAIN, 1);
			AddGossipItemFor(player,GOSSIP_ICON_DOT, guild, GOSSIP_SENDER_MAIN, 1);
			AddGossipItemFor(player,GOSSIP_ICON_DOT, kills, GOSSIP_SENDER_MAIN, 1);
			AddGossipItemFor(player,GOSSIP_ICON_DOT, honor, GOSSIP_SENDER_MAIN, 1);
			AddGossipItemFor(player,GOSSIP_ICON_DOT, arena, GOSSIP_SENDER_MAIN, 1);
			AddGossipItemFor(player,GOSSIP_ICON_DOT, map, GOSSIP_SENDER_MAIN, 1);
			AddGossipItemFor(player,GOSSIP_ICON_DOT, x, GOSSIP_SENDER_MAIN, 1);
			AddGossipItemFor(player,GOSSIP_ICON_DOT, y, GOSSIP_SENDER_MAIN, 1);
			SendGossipMenuFor(player,DEFAULT_GOSSIP_MESSAGE, item->GetGUID());

	}

	void Stern(Player* player, Item* item)
	{
		AddGossipItemFor(player,10, "Gem", GOSSIP_SENDER_MAIN, 4);
		AddGossipItemFor(player,10, "Gem", GOSSIP_SENDER_MAIN, 4);
		AddGossipItemFor(player,10, "Gem", GOSSIP_SENDER_MAIN, 4);
		SendGossipMenuFor(player,DEFAULT_GOSSIP_MESSAGE, item->GetGUID());
	}

	void Sargeras(Player* player, Item* item)
	{
		char name[256];
		char gender[256];
		char guild[256];
		char kills[256];
		char honor[256];
		char arena[256];
		char map[256];
		char x[256];
		char y[256];
		//char z[256];
		char test[256];
		//char test2[256];
		char mapcord[256];
		//char fin3[256];
		float tran = (((player->GetPositionX()*D) - C) / B) + A;
		float tran2 = (((player->GetPositionY()*D) - C) / B) + A;
		std::string mapname = player->FindMap()->GetMapName();
		uint32 playertest = player->GetGUID();
		uint8 gendertest = player->getGender();
		uint32 guildtest = player->GetGuildId();
		uint32 areaId = player->GetAreaId();
		uint32 zoneId = player->GetZoneId();
		std::string areaName = "Unknown";
		std::string zoneName = "Unknown";
		if (AreaTableEntry const* area = sAreaTableStore.LookupEntry(areaId))
		{
			int locale = player->GetSession()->GetSessionDbcLocale();
			areaName = area->area_name[locale];
			if (AreaTableEntry const* zone = sAreaTableStore.LookupEntry(area->zone))
				zoneName = zone->area_name[locale];
		}
		if (playertest == 0)
			sprintf(name, "Name: None");
		else
			sprintf(name, "Name: %s", player->GetSession()->GetPlayerName().c_str());
		if (gendertest == 0)
			sprintf(gender, "Gender: Male");
		else
			sprintf(gender, "Gender: Female");
		if (guildtest == 0)
			sprintf(guild, "Guild: None");
		else
			sprintf(guild, "Guild: %s", player->GetGuildName().c_str());
		sprintf(kills, "HonorKills: %u", player->GetUInt32Value(PLAYER_FIELD_LIFETIME_HONORABLE_KILLS));
		sprintf(honor, "HonorPoints: %u", player->GetHonorPoints());
		sprintf(arena, "ArenaPoints: %u", player->GetArenaPoints());
		sprintf(map, "Map: %u (%s)", player->GetMapId(), mapname.c_str());
		sprintf(y, "Area: %u %s Zone: %u %s", areaId, areaName.c_str(), zoneId, zoneName.c_str());
		sprintf(x, "X: %f Y:%f Z:%f", player->GetPositionX(), player->GetPositionY(), player->GetPositionZ());
		sprintf(test, "%s", player->GetMapAreaAndZoneString().c_str());
		sprintf(mapcord, "X:%f Y:%f", tran2, tran);
		AddGossipItemFor(player,GOSSIP_ICON_DOT, "Admin Menu", GOSSIP_SENDER_MAIN, 1);
		AddGossipItemFor(player,GOSSIP_ICON_DOT, name, GOSSIP_SENDER_MAIN, 1);
		AddGossipItemFor(player,GOSSIP_ICON_DOT, gender, GOSSIP_SENDER_MAIN, 1);
		AddGossipItemFor(player,GOSSIP_ICON_DOT, guild, GOSSIP_SENDER_MAIN, 1);
		AddGossipItemFor(player,GOSSIP_ICON_DOT, kills, GOSSIP_SENDER_MAIN, 1);
		AddGossipItemFor(player,GOSSIP_ICON_DOT, honor, GOSSIP_SENDER_MAIN, 1);
		AddGossipItemFor(player,GOSSIP_ICON_DOT, arena, GOSSIP_SENDER_MAIN, 1);
		AddGossipItemFor(player,GOSSIP_ICON_DOT, map, GOSSIP_SENDER_MAIN, 1);
		AddGossipItemFor(player,GOSSIP_ICON_DOT, x, GOSSIP_SENDER_MAIN, 1);
		AddGossipItemFor(player,GOSSIP_ICON_DOT, y, GOSSIP_SENDER_MAIN, 1);
		AddGossipItemFor(player,GOSSIP_ICON_DOT, test, GOSSIP_SENDER_MAIN, 1);
		AddGossipItemFor(player,GOSSIP_ICON_DOT, mapcord, GOSSIP_SENDER_MAIN, 1);
		AddGossipItemFor(player,GOSSIP_ICON_DOT, "Testmenu", GOSSIP_SENDER_MAIN, 3);
		AddGossipItemFor(player,GOSSIP_ICON_DOT, "Online PlayerInfo", GOSSIP_SENDER_MAIN, 4, "", 0, true);
		AddGossipItemFor(player,GOSSIP_ICON_DOT, "test", GOSSIP_SENDER_MAIN, 5);
		SendGossipMenuFor(player,DEFAULT_GOSSIP_MESSAGE, item->GetGUID());
		
	}
	void VoidWarrior(Player* player, Item* item)
	{
		char name[256];
		uint32 playertest = player->GetGUID();
		if (playertest == 0)
			sprintf(name, "Name: None");
		else
			sprintf(name, "Name: %s", player->GetSession()->GetPlayerName().c_str());

		AddGossipItemFor(player,GOSSIP_ICON_DOT, "Player Menu", GOSSIP_SENDER_MAIN, 2);
		AddGossipItemFor(player,GOSSIP_ICON_DOT, name, GOSSIP_SENDER_MAIN, 2);
		SendGossipMenuFor(player,DEFAULT_GOSSIP_MESSAGE, item->GetGUID());
	}
	bool OnUse(Player* player, Item* item, SpellCastTargets const& targets) override
	{
		player->PlayerTalkClass->ClearMenus();
		if (player->GetSession()->GetSecurity() > 0)
		{
			Sargeras(player, item);
		}
		else if (player->IsGameMaster())
		{
			Stern(player, item);
		}
		else
		{
			VoidWarrior(player, item);
		}
		return true;
	}
	void OnGossipSelect(Player* player, Item* item, uint32 sender, uint32 action)
	{
		player->PlayerTalkClass->ClearMenus();
		switch (action)
		{
		case 1:
			Sargeras(player, item);
			break;
		case 2:
			VoidWarrior(player, item);
			break;
		default:
			break;
		}
	}
	void OnGossipSelectCode(Player* player, Item* item, uint32 sender, uint32 action, const char* code)
	{
		player->PlayerTalkClass->ClearMenus();
		switch (action)
		{
		case 4:
			Tartas(player, item, code);
			break;
		default:
			break;
		}
	}
};
void AddSC_NewItemSC()
{
	new NewItemSC();
}