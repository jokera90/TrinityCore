#include "ScriptPCH.h"
#include "Language.h"
#include "Log.h"
#include "AccountMgr.h"
#include "Chat.h"
#include "Player.h"
#include "WorldSession.h"
#include "DBCStores.h"
#include "Item.h"
#include "DatabaseEnv.h"
#include "GossipDef.h"
#include "ScriptedGossip.h"

#define DEFAULT_GOSSIP_MESSAGE              0xffffff
#define NULL 0

using namespace std;

class PlayerHelper : public ItemScript
{
public:
	PlayerHelper() : ItemScript("PlrH") {}
	int input[5];
	float input1[5];
	enum Nubers
	{
		A = 32,
		B = 533,
		C = 266,
		D = -1,
	};
	std::string MoneyString(uint32 incopper)
	{
		uint32 gold = incopper / 10000;
		incopper -= gold * 10000;
		uint32 silver = incopper / 100;
		incopper -= silver * 100;
		uint32 copper = incopper;

		std::ostringstream ss;

		if (gold)
			ss << gold;//<< "|TInterface\\MoneyFrame\\UI-GoldIcon:14:14|t";
			if (silver)
				ss << silver;// << "|TInterface\\MONEYFRAME\\UI-SilverIcon:14:14|t";
				if (copper)
					ss << copper;// << "|TInterface\\MoneyFrame\\UI-CopperIcon:14:14|t";

		if (!gold && !silver && !copper)
			ss << "NAH";

		return ss.str();
	}
	void First(Player* player, Item* item) // ROOT MENU
	{
		AddGossipItemFor(player,10, "ADMIN MENU", GOSSIP_SENDER_MAIN, 6);
		AddGossipItemFor(player,10, "GM MENU", GOSSIP_SENDER_MAIN, 2);
		AddGossipItemFor(player,10, "PLAYER MENU", GOSSIP_SENDER_MAIN, 3,"",0,true);
		AddGossipItemFor(player,10, "test menu", GOSSIP_SENDER_MAIN, 4);
		AddGossipItemFor(player,10, "test menu2", GOSSIP_SENDER_MAIN, 5);
		SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, item->GetGUID());

	}
	void Second(Player* player, Item* item) // GM MENU
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
		AddGossipItemFor(player,10, "ADMIN MENU", GOSSIP_SENDER_MAIN, 1);
		AddGossipItemFor(player,GOSSIP_ICON_DOT, name, GOSSIP_SENDER_MAIN, 2);
		AddGossipItemFor(player,GOSSIP_ICON_DOT, gender, GOSSIP_SENDER_MAIN, 2);
		AddGossipItemFor(player,GOSSIP_ICON_DOT, guild, GOSSIP_SENDER_MAIN, 2);
		AddGossipItemFor(player,GOSSIP_ICON_DOT, kills, GOSSIP_SENDER_MAIN, 2);
		AddGossipItemFor(player,GOSSIP_ICON_DOT, honor, GOSSIP_SENDER_MAIN, 2);
		AddGossipItemFor(player,GOSSIP_ICON_DOT, arena, GOSSIP_SENDER_MAIN, 2);
		AddGossipItemFor(player,GOSSIP_ICON_DOT, map, GOSSIP_SENDER_MAIN, 2);
		AddGossipItemFor(player,GOSSIP_ICON_DOT, x, GOSSIP_SENDER_MAIN, 2);
		AddGossipItemFor(player,GOSSIP_ICON_DOT, y, GOSSIP_SENDER_MAIN, 2);
		AddGossipItemFor(player,GOSSIP_ICON_DOT, test, GOSSIP_SENDER_MAIN, 2);
		AddGossipItemFor(player,GOSSIP_ICON_DOT, mapcord, GOSSIP_SENDER_MAIN, 2);
		AddGossipItemFor(player,GOSSIP_ICON_DOT, "Account createTest", GOSSIP_SENDER_MAIN, 34,"",0,true);
		AddGossipItemFor(player,GOSSIP_ICON_DOT, "test", GOSSIP_SENDER_MAIN, 5);
		SendGossipMenuFor(player,DEFAULT_GOSSIP_MESSAGE, item->GetGUID());
	}
	void Ter(Player* player, Item* item, const char* code) // PLAYER MENU
	{
		uint32 test = atol(code);
		//string srch = atol((char*)code);
		QueryResult result = CharacterDatabase.PQuery("SELECT m_id, m_name_lang_enus FROM db_taxinodes_12340 WHERE m_id LIKE '%u' LIMIT 10", test);
		Field *field = NULL;
		do
		{
			field = result->Fetch();
			uint32 entry = field[0].GetUInt32();
			string name = field[1].GetString();
			char send[256];
			snprintf(send, 256, "Id: %u Name: %s", entry, name.c_str());
			AddGossipItemFor(player, 10, send, GOSSIP_SENDER_MAIN, 3);
		} while (result->NextRow());

		SendGossipMenuFor(player,DEFAULT_GOSSIP_MESSAGE, item->GetGUID());
	}
	void Der(Player* player, Item* item) // TEST MENU
	{
		AddGossipItemFor(player,10, "TestMenu1", GOSSIP_SENDER_MAIN, 4);
		AddGossipItemFor(player,10, "admin menu", GOSSIP_SENDER_MAIN, 1);
		AddGossipItemFor(player,10, "GenpropID", GOSSIP_SENDER_MAIN, 49,"",0,true);
		AddGossipItemFor(player,10, "itemdipinfo", GOSSIP_SENDER_MAIN, 50,"",0,true);
		AddGossipItemFor(player,10, "TestMenu1", GOSSIP_SENDER_MAIN, 4);
		AddGossipItemFor(player,10, "TestMenu1", GOSSIP_SENDER_MAIN, 4);
		SendGossipMenuFor(player,DEFAULT_GOSSIP_MESSAGE, item->GetGUID());
	}
	void Ber(Player* player, Item* item) // TEST2 MENU
	{ 
		QueryResult result = CharacterDatabase.PQuery("SELECT gold FROM characters_gold_bank WHERE guid = %u", player->GetGUID());
		if (!result)
		{
			CloseGossipMenuFor(player);
		}
		Field*fields = result->Fetch();
		uint32 gold = fields[0].GetUInt32();
		char test[256];
		char test2[256];
		if (gold == 0)
			sprintf(test, "GoldBank: None");
		else
			sprintf(test, "GoldBank: %u", gold);
		sprintf(test2, "PlayerGold: %s", MoneyString(player->GetMoney()).c_str());
		AddGossipItemFor(player,10, "admin menu", GOSSIP_SENDER_MAIN, 1);
		AddGossipItemFor(player,10, test, GOSSIP_SENDER_MAIN, 5);
		AddGossipItemFor(player,10, test2, GOSSIP_SENDER_MAIN, 5);
		AddGossipItemFor(player,10, "Deposit", GOSSIP_SENDER_MAIN, 30,"",0,true);
		AddGossipItemFor(player,10, "Withdrow", GOSSIP_SENDER_MAIN, 31,"",0,true);
		SendGossipMenuFor(player,DEFAULT_GOSSIP_MESSAGE, item->GetGUID());
	}
	void Ker(Player* player, Item*item)
	{
		QueryResult result = CharacterDatabase.PQuery("SELECT Xsor, Ysor FROM start WHERE guid = %u", player->GetGUID());
		QueryResult res = CharacterDatabase.PQuery("SELECT map, x, y, z FROM teleport WHERE guid = %u", player->GetGUID());
		if (!result)
		{
			CloseGossipMenuFor(player);
		}
		//else if (!res)
		//{
			//CloseGossipMenuFor(player);
		//}

		Field*fields = result->Fetch();
		float Xsor = fields[0].GetFloat();
		float Ysor = fields[1].GetFloat();
		Field*fields2 = res->Fetch();
		uint32 m = fields2[0].GetUInt32();

		std::string mapname = "Unknown";
		if (MapEntry const * map = sMapStore.LookupEntry(m))
		{
			int local = player->GetSession()->GetSessionDbcLocale();
			mapname = map->name[local];
		}
		float mx = fields2[1].GetFloat();
		float my = fields2[2].GetFloat();
		float mz = fields2[3].GetFloat();
		float Y = (((Xsor - A)*B) + C)*D;
		float X = (((Ysor - A)*B) + C)*D;
		uint8 revY = (((player->GetPositionX()*D) - C) / B) + A;
		uint8 revX = (((player->GetPositionY()*D) - D) / B) + A;
		char test[256];
		char test2[256];
		char test3[256];
		char test4[256];
		char test5[256];
		char test6[256];
		char test7[256];
		char test8[256];
		char test9[256];
		sprintf(test, "Change Y:%.0f", Ysor);
		sprintf(test2, "X:%.2f Y:%.2f", X, Y);
		sprintf(test3, "X:%.2f Y:%.2f Z:%.2f", player->GetPositionX(), player->GetPositionY(), player->GetPositionZ());
		sprintf(test4, "X:%u Y:%u", revX, revY);
		sprintf(test6, "Map: %u (%s) PMap: %u", m, mapname.c_str(), player->GetMapId());
		sprintf(test7, "X: %.2f", mx);
		sprintf(test8, "Y: %.2f", my);
		sprintf(test9, "Z: %2f", mz);
		sprintf(test5, "Change X: %.0f", Xsor);
		AddGossipItemFor(player, 10, test2, GOSSIP_SENDER_MAIN, 6);
		AddGossipItemFor(player, 10, test3, GOSSIP_SENDER_MAIN, 40);
		AddGossipItemFor(player, 10, test4, GOSSIP_SENDER_MAIN, 6);
		AddGossipItemFor(player, 10, test5, GOSSIP_SENDER_MAIN, 20, "", 0, true);
		AddGossipItemFor(player, 10, test, GOSSIP_SENDER_MAIN, 21, "", 0, true);
		AddGossipItemFor(player, 10, test6, GOSSIP_SENDER_MAIN, 22, "", 0, true);
		AddGossipItemFor(player, 10, test7, GOSSIP_SENDER_MAIN, 23, "", 0, true);
		AddGossipItemFor(player, 10, test8, GOSSIP_SENDER_MAIN, 24, "", 0, true);
		AddGossipItemFor(player, 10, test9, GOSSIP_SENDER_MAIN, 25, "", 0, true);
		AddGossipItemFor(player, 10, "Teleport", GOSSIP_SENDER_MAIN, 26, "", 0, false);
		AddGossipItemFor(player, 10, "Update cords", GOSSIP_SENDER_MAIN, 28);
		AddGossipItemFor(player, 10, "Taxi EntryTele", GOSSIP_SENDER_MAIN, 33, "", 0, true);
		AddGossipItemFor(player, GOSSIP_ICON_DOT, "Cord from guid", GOSSIP_SENDER_MAIN, 32, "", 0, true);
		AddGossipItemFor(player, 10, "Back=>", GOSSIP_SENDER_MAIN, 1);
		SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, item->GetGUID());

	}
	void Mer(Player* player, Item* item)
	{
		ClearGossipMenuFor(player);
		//float x, y, z;
		char dum[256];//, rum[256], kum[256];
		sprintf(dum, "X: %f\nY: %f\nZ: %f", player->GetPositionX(), player->GetPositionY(), player->GetPositionZ());
		//AddGossipItemFor(player, 10, "reflesh", GOSSIP_SENDER_MAIN, 40);
		AddGossipItemFor(player, 10, dum, GOSSIP_SENDER_MAIN, 40);
		AddGossipItemFor(player, 10, "folward/backward-/+", GOSSIP_SENDER_MAIN, 46, "", 0, true);
		AddGossipItemFor(player, 10, "left/right-/+", GOSSIP_SENDER_MAIN, 47, "", 0, true);
		AddGossipItemFor(player, 10, "up/down-/+", GOSSIP_SENDER_MAIN, 48, "", 0, true);
		AddGossipItemFor(player, 10, "Telepoty X Y Z Map", GOSSIP_SENDER_MAIN, 45, "", 0, true);
		AddGossipItemFor(player, 10, "Back=>", GOSSIP_SENDER_MAIN, 6);
		SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, item->GetGUID());
	}
	bool OnUse(Player* player, Item* item, SpellCastTargets const& targets) override
	{
		player->PlayerTalkClass->ClearMenus();
		if (player->GetSession()->GetSecurity() > 0)
		{
			Ker(player, item);
		}
		else {
			Der(player, item);

		}
		return true;
	}
	void OnGossipSelect(Player* player, Item* item, uint32 sender, uint32 action)
	{
		player->PlayerTalkClass->ClearMenus();
		switch (action)
		{
		case 1:
			First(player, item);
			break;
		case 2:
			Second(player, item);
			break;
		case 4:
			Der(player, item);
			break;
		case 5:
			Ber(player, item);
			break;
		case 6:
			Ker(player, item);
			break;
		case 26:
		{
			QueryResult result = CharacterDatabase.PQuery("SELECT map, x, y, z FROM teleport WHERE guid = %u",player->GetGUID());

			if (!result)
			{
				CloseGossipMenuFor(player);
			}
			Field*fields = result->Fetch();
			uint32 m = fields[0].GetUInt32();
			float x = fields[1].GetFloat();
			float y = fields[2].GetFloat();
			float z = fields[3].GetFloat();
			float o = player->GetOrientation();
			player->TeleportTo(m, x, y, z, o);
			Ker(player, item);
			break;
		}
		case 27:
		{
				Ber(player, item);
			break;
		}
		case 28:
		{
			QueryResult result = CharacterDatabase.PQuery("SELECT Ysor,Xsor FROM start WHERE guid = %u",player->GetGUID());
			Field*fields = result->Fetch();
			float y, x2;
			float x, y2;
			y = fields[0].GetFloat();
			x = fields[1].GetFloat();
			x2 = (((y - A)*B) + C)*D;
			y2 = (((x - A)*B) + C)*D;
			CharacterDatabase.PExecute("UPDATE teleport SET y = %f WHERE guid = %u", y2, player->GetGUID());
			CharacterDatabase.PExecute("UPDATE teleport SET x = %f WHERE guid = %u", x2, player->GetGUID());
			Ker(player, item);
			break;
		}
		case 40:
		{
			Mer(player, item);
			break;
		}
		default:
			break;
		}

	}
	void OnGossipSelectCode(Player* player, Item* item, uint32 sender, uint32 action, const char* code)
	{
		player->PlayerTalkClass->ClearMenus();

		switch (action)
		{
		case 3:
		{
			
		uint32 additem = 0;
		//char const* id = strtok((char*)code, "Hitem");
		char const* id = ChatHandler(player->GetSession()).extractKeyFromLink((char*)code, "Hitem");
		additem = atoul(id);
		char* ammount = strtok(NULL, " ");
		uint32 amount = 1;
		if (ammount)
			amount = strtol(ammount, NULL, 10);
		if (amount == 0)
			amount = 1;

		Player*target = player->GetSelectedPlayer();
		if (target)
		{
			target->AddItem(additem, amount);
			First(player, item);
		}
		else
		{
			player->AddItem(additem, amount);
			First(player, item);
		}
		break;
			//uint32 test = atol(code);
			//Ter(player, item, code);
		}
		case 20:
		{
			uint32 XTR = atol(code);
			CharacterDatabase.PExecute("UPDATE start SET Xsor = %u WHERE guid = %u", XTR, player->GetGUID());
			Ker(player, item);
			break;
		}
		case 21: 
		{
			uint32 YTR = atol(code);
			CharacterDatabase.PExecute("UPDATE start SET Ysor = %u WHERE guid = %u", YTR, player->GetGUID());
			Ker(player, item);
			break; 
		}
		case 22:
		{
			input[1] = atol(code);
			CharacterDatabase.PExecute("UPDATE teleport SET map = %u WHERE guid = %u", input[1], player->GetGUID());
			Ker(player, item);
			break;
		}
		case 23:
		{
			input1[1] = atof(code);
			CharacterDatabase.PExecute("UPDATE teleport SET x = %f WHERE guid = %u", input1[1], player->GetGUID());
			Ker(player, item);
			break;
		}
		case 24:
		{
			input1[2] = atof(code);
			CharacterDatabase.PExecute("UPDATE teleport SET y = %f WHERE guid = %u", input1[2], player->GetGUID());
			Ker(player, item);
			break;
		}
		case 25:
		{
			input1[3] = atof(code);
			CharacterDatabase.PExecute("UPDATE teleport SET z = %f WHERE guid = %u", input1[3], player->GetGUID());
			Ker(player, item);
			break;
		}
		case 30:
		{
			QueryResult result = CharacterDatabase.PQuery("SELECT money FROM characters WHERE guid = %u", player->GetGUID());

			Field* field = result->Fetch();
			uint32 money = (field[0].GetUInt32() / 10000);
			uint32 deposit = atol(code);
			int32 gold = (player->GetMoney()/10000);
			int32 mod = gold - deposit;
			if (money == deposit)
			{
				CharacterDatabase.PExecute("UPDATE characters_gold_bank SET gold = gold+%u WHERE guid = %u", money, player->GetGUID());
				player->ModifyMoney((-1 * money)*GOLD);
			}
			else if (money == 0)
			{
				player->GetSession()->SendNotification("You dont have %u gold", deposit);
			}
			else if(mod > 0)
			{
			    CharacterDatabase.PExecute("UPDATE characters_gold_bank SET gold = gold+%u WHERE guid = %u", deposit, player->GetGUID());
				player->ModifyMoney((-1 * deposit)*GOLD);
				player->GetSession()->SendNotification("You deposit %u gold", deposit);
			}
			Ber(player, item);
			break;
		}
		case 31:
		{
			QueryResult result = CharacterDatabase.PQuery("SELECT gold FROM characters_gold_bank WHERE guid = %u", player->GetGUID());
			Field* fields = result->Fetch();
			uint32 goldbank = fields[0].GetUInt32();
			uint32 gold = player->GetMoney();
			uint32 withdrow = atol(code);
			int32 error = gold + withdrow;
			if (error >= (200000*GOLD))
			{
				player->GetSession()->SendNotification("YOUR ARE TRYING TO WITHDOWM OVER 200000 GOLD");
			}
			else if (goldbank < withdrow)
			{
				CharacterDatabase.PExecute("UPDATE characters_gold_bank SET gold = gold-%u WHERE guid = %u", goldbank, player->GetGUID());
				player->ModifyMoney(goldbank*GOLD);
				player->GetSession()->SendNotification("You dont have enough gold, all gold from the bank is withdrowed");
			}
			else
			{
				CharacterDatabase.PExecute("UPDATE characters_gold_bank SET gold = gold-%u WHERE guid = %u", withdrow, player->GetGUID());
				player->ModifyMoney(withdrow*GOLD);
			}
			Ber(player, item);
			break;
		
		}
		case 32:
		{
			uint32 guid = atol(code);
			QueryResult result = CharacterDatabase.PQuery("SELECT position_x, position_y FROM characters WHERE guid = %u", guid);
			Field*fields = result->Fetch();
			float x, y, x2, y2, x3, y3;
			x = fields[0].GetFloat();
			y = fields[1].GetFloat();
			x2 = (((y - A)*B) + C)*D;
			y2 = (((x - A)*B) + C)*D;
			x3 = (((y*D) - D) / B) + A;
			y3 = (((x*D) - D) / B) + A;
			CharacterDatabase.PExecute("UPDATE start SET Xsor = %f WHERE guid = %u", x3,player->GetGUID());
			CharacterDatabase.PExecute("UPDATE start SET Ysor = %f WHERE guid = %u", y3, player->GetGUID());
			Ker(player, item);
			break;
		}
		case 33:
		{
			uint32 entry = atol(code);
			TaxiNodesEntry const * info = sTaxiNodesStore.LookupEntry(entry);
			if (!entry)
			{
				player->GetSession()->SendNotification("No entry");
				Ker(player, item);
			}
			else
			{
				CharacterDatabase.PExecute("UPDATE teleport set map = %u, x= %f, y =%f, z=%f where guid = %u", info->map_id, info->x, info->y, info->z, player->GetGUID());
				Ker(player, item);
			}
			break;
		}
		case 34:
		{
			if (!*code)
				Ker(player, item);

			std::string email;

			///- %Parse the command line arguments
			char* accountName = strtok((char*)code, " ");
			char* password = strtok(NULL, " ");
			char* possibleEmail = strtok(NULL, " ' ");
			if (possibleEmail)
				email = possibleEmail;

			if (!accountName || !password)
				Ker(player, item);

			if (strchr(accountName, '@'))
			{
				ChatHandler(player->GetSession()).PSendSysMessage(LANG_ACCOUNT_USE_BNET_COMMANDS);
				ChatHandler(player->GetSession()).SetSentErrorMessage(true);
				Ker(player, item);
			}

			switch (sAccountMgr->CreateAccount(std::string(accountName), std::string(password), email))
			{
			case AccountOpResult::AOR_OK:
				ChatHandler(player->GetSession()).PSendSysMessage(LANG_ACCOUNT_CREATED, accountName);
				if (player->GetSession())
				{
					TC_LOG_INFO("entities.player.character", "Account: %d (IP: %s) Character:[%s] (GUID: %u) created Account %s (Email: '%s')",
						player->GetSession()->GetAccountId(), player->GetSession()->GetRemoteAddress().c_str(),
						player->GetSession()->GetPlayer()->GetName().c_str(), player->GetSession()->GetPlayer()->GetGUID().GetCounter(),
						accountName, email.c_str());
				}
				break;
			case AccountOpResult::AOR_NAME_TOO_LONG:
				ChatHandler(player->GetSession()).SendSysMessage(LANG_ACCOUNT_NAME_TOO_LONG);
				ChatHandler(player->GetSession()).SetSentErrorMessage(true);
				Ker(player, item);
				break;
			case AccountOpResult::AOR_PASS_TOO_LONG:
				ChatHandler(player->GetSession()).SendSysMessage(LANG_ACCOUNT_PASS_TOO_LONG);
				ChatHandler(player->GetSession()).SetSentErrorMessage(true);
				Ker(player, item);
				break;
			case AccountOpResult::AOR_NAME_ALREADY_EXIST:
				ChatHandler(player->GetSession()).SendSysMessage(LANG_ACCOUNT_ALREADY_EXIST);
				ChatHandler(player->GetSession()).SetSentErrorMessage(true);
				Ker(player, item);
				break;
			case AccountOpResult::AOR_DB_INTERNAL_ERROR:
				ChatHandler(player->GetSession()).PSendSysMessage(LANG_ACCOUNT_NOT_CREATED_SQL_ERROR, accountName);
				ChatHandler(player->GetSession()).SetSentErrorMessage(true);
				Ker(player, item);
				break;
			default:
				ChatHandler(player->GetSession()).PSendSysMessage(LANG_ACCOUNT_NOT_CREATED, accountName);
				ChatHandler(player->GetSession()).SetSentErrorMessage(true);
				Ker(player, item);
				break;
			}

			return;
		}
		case 45:
		{

			char* x = strtok((char*)code, " ");
			char* y = strtok(nullptr, " ");
			char* z = strtok(nullptr, " ");
			char* m = strtok(nullptr, " ");
			float x2, y2, z2;
			uint32 m2;
			if (!x)
				Mer(player, item);
			x2 =(float)atof(x);
			if (!y)
				Mer(player, item);
			y2 = (float)atof(y);
			if (!z)
				Mer(player, item);
			z2 = (float)atof(z);
			if (!m)
				Mer(player, item);
			m2 = atol(m);
			player->TeleportTo(m2, x2, y2, z2, player->GetOrientation());
			Mer(player, item);
			break;
		}
		case 46:
		{
			if (!code)
			{
				Mer(player, item);
				player->GetSession()->SendNotification("bigbum please don cash");
			}
			float x = atof(code);
			player->TeleportTo(player->GetMapId(), player->GetPositionX() + x, player->GetPositionY(), player->GetPositionZ(), player->GetOrientation());
			Mer(player, item);
			break;

		}
		case 47:
		{
			float y = atof(code);
			player->TeleportTo(player->GetMapId(), player->GetPositionX(), player->GetPositionY() + y, player->GetPositionZ(), player->GetOrientation());
			Mer(player, item);
			break;
			
		}
		case 48:
		{
			float z = atof(code);
			player->TeleportTo(player->GetMapId(), player->GetPositionX(), player->GetPositionY(), player->GetPositionZ() + z, player->GetOrientation());
			Mer(player, item);
			break;

		}
		case 49:
		{
			uint32 entry = atol(code);
			GemPropertiesEntry const * Info = sGemPropertiesStore.LookupEntry(entry);
			if (!Info)
			{
				player->GetSession()->SendNotification("no entry");
				Der(player, item);
			}
			else
			{
				player->GetSession()->SendNotification("%u", Info->spellitemenchantement);
				Der(player, item);
			}
			break;
		}
		case 50:
		{
			//char z[1024], t[256];
			uint32 entry = atol(code);
			ItemDisplayInfoEntry const* info = sItemDisplayInfoStore.LookupEntry(entry);
			if (!info)
			{
				Der(player, item);
				player->GetSession()->SendNotification("No displayid");
			}
			else if (!info->inventoryIcon[0])
			{
				if (!info->inventoryIcon[1])
				{
					player->GetSession()->SendNotification("no icon2");
					Der(player, item);
				}
				else
				{
					player->GetSession()->SendNotification("no icon");
					Der(player, item);
				}
			}
			else
			{
				ostringstream oss;
				oss << "ID: " << info->ID << " Icon: " << info->inventoryIcon[0]<<" Icon2: "<<info->inventoryIcon[1];
				string test = oss.str();
				//snprintf(z, 1024, "%u\t %c", info->ID, info->inventoryIcon);
				ChatHandler(player->GetSession()).SendSysMessage(test.c_str());
				Der(player, item);
			}
			break;
		}
			
		}
		
	}
};

/*
class DBedit : public PlayerScript
{
public:
	class DBedit() : PlayerScript("dbedit")
	{
		 const char* sql =
			"CREATE TABLE IF NOT EXISTS `start` ("
			 "`guid` INT(10) NULL DEFAULT NULL,"
			"`Xsor` FLOAT(4, 0) UNSIGNED ZEROFILL NOT NULL,"
			"`Ysor` FLOAT(4, 0) NOT NULL,"
			"`item` INT(10) NULL DEFAULT NULL,"
		    "`spellcast` INT(10) NULL DEFAULT NULL"
			")"
			"COLLATE = 'utf8_general_ci'"
			"ENGINE = InnoDB;";
		 const char* sql2 =
			 "CREATE TABLE IF NOT EXISTS `teleport` ("
			 "`map` INT(11) NULL DEFAULT NULL,"
			 "`x` FLOAT NULL DEFAULT NULL,"
			 "`y` FLOAT NULL DEFAULT NULL,"
			 "`z` FLOAT NULL DEFAULT NULL,"
			 "`X2` FLOAT NULL DEFAULT NULL,"
			 "`Y2` FLOAT NULL DEFAULT NULL"
			 ")"
			 "COLLATE = 'latin1_swedish_ci'"
			 "ENGINE = InnoDB;";
		 const char* sql3 =
			 "CREATE TABLE `characters_gold_bank` ("
			 "`guid` INT(11) UNSIGNED NOT NULL,"
			 "`gold` INT(11) UNSIGNED NULL DEFAULT NULL,"
			 "UNIQUE INDEX `guid_2` (`guid`),"
			 "INDEX `guid` (`guid`)"
			 ")"
			 "COLLATE = 'utf8_general_ci'"
			 "ENGINE = InnoDB;";

		 CharacterDatabase.DirectExecute(sql);
		 CharacterDatabase.DirectExecute(sql2);
		 CharacterDatabase.DirectExecute(sql3);
	}
	void OnLogin(Player* player, bool firstLogin)
	{
		CharacterDatabase.PExecute("INSERT INTO `start` (guid, xsor, ysor, item, spellcast) VALUES(%u, 1, 1, 0, 0) ON DUPLICATE KEY UPDATE xsor = xsor;", player->GetGUID());
		CharacterDatabase.PExecute("INSERT INTO `teleport` (guid, map, `x`,`y`,z,X2,y2) VALUES(%u, 0, 0, 0,0,0,0) ON DUPLICATE KEY UPDATE `map` = `map`;", player->GetGUID());
		CharacterDatabase.PExecute("INSERT INTO characters_gold_bank (guid, gold) VALUES(%u, 0) ON DUPLICATE KEY UPDATE gold=gold;", player->GetGUID());
	}

};*/
void AddSC_PlayerHelper()
{
	new PlayerHelper();
}
