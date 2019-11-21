#include "ScriptPCH.h"
#include "Item.h"
#include "GossipDef.h"
#include "ScriptedGossip.h"
#include "DatabaseEnv.h"
#include "DBCStores.h"
#include "AccountMgr.h"
#include "WorldSession.h"


using namespace std;
void Second(Player* player, Item* item)
{
	QueryResult t = CharacterDatabase.PQuery("SELECT test FROM start WHERE guid = %u", player->GetGUID());
	Field*d = t->Fetch();
	uint32 entry = d[0].GetUInt32();
	LightEntry const* li = sLightStore.LookupEntry(entry);
	char infotest[1025];
	double coren = 17066.666;
	float coren2 = 36.0f;
	float realx = 17066.666 - li->Z / coren2;
	float realy = 17066.666 - li->X / coren2;
	float realz = li->Y / coren2;
	snprintf(infotest, 1025, "Entry: %u\nMap: %u\nx: %f \ny: %f, \nz: %f\nCoren: %f\nCoren2 %f\nPosX: %f\nPosY: %f\nPoxZ: %f", li->Id, li->MapId, li->X, li->Y, li->Z, coren, coren2, realx, realy, realz);
	AddGossipItemFor(player, 10, infotest, 1, 1, "", 0, true);
	AddGossipItemFor(player, 10, "Teleport", 1, 11);
	CharacterDatabase.PExecute("UPDATE teleport SET y = %f, x = %f WHERE guid = %u", realy, realx, player->GetGUID());
	AddGossipItemFor(player, 10, "<-Back", 1, 10);
	SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, item->GetGUID());
}
	void First(Player* player, Item* item, const char* code)
	{
		uint32 entry = atol(code);
		LightEntry const* li = sLightStore.LookupEntry(entry);
		char INFO[1045];
		double coren = 17066.666;
	    float coren2 = 36.0f;
		float realx = 17066.666 - li->Z / coren2;
		float realy = 17066.666 - li->X / coren2;
		float realz = li->Y / coren2;
		snprintf(INFO, 1045, "Entry: %u\nMap: %u\nx: %f \ny: %f, \nz: %f\nCoren: %f\nCoren2 %f\nPosX: %f\nPosY: %f\nPoxZ: %f", li->Id, li->MapId, li->X, li->Y, li->Z, coren, coren2, realx, realy, realz);
		AddGossipItemFor(player, 10, INFO, 1, 1, "", 0, true);
		AddGossipItemFor(player, 10, "Teleport", 1, 11);
		AddGossipItemFor(player, 10, "<-Back", 1, 10);
		CharacterDatabase.PExecute("UPDATE teleport SET y = %f, x = %f WHERE guid = %u", realy, realx, player->GetGUID());
		SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, item->GetGUID());
		
	}
	void ClassRaceSkillName(Player* player, Item* item, const char * code)
	{
		uint32 id = atol(code);
		SkillLineEntry const* sl = sSkillLineStore.LookupEntry(id);
		string skname = sl->name[0];
		ostringstream ss;
		ss << "SkillId: " << id << "\nSkillName: " << skname;
		AddGossipItemFor(player, 10, ss.str(), 1, 50);
		AddGossipItemFor(player, 10, "<-Back", 1, 10);
		SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, item->GetGUID());
	}

	void Testmenu(Player* player, Item* item)
	{
		AddGossipItemFor(player, 10, "Light.dbc", 1, 1, "", 0,true);
		//AddGossipItemFor(player, 10, "Testmenushow", 1, 2, "", 0, true);
		//AddGossipItemFor(player, 10, "Testmenushow2", 1, 12, "", 0, false);
		//AddGossipItemFor(player, 10, "Testmenushow3", 1, 3, "", 0, true);
	//	AddGossipItemFor(player, 10, "Testmenushow4", 1, 4, "", 0, true);
		AddGossipItemFor(player, 10, "SkilllineName", 1, 5, "", 0, true);
		//AddGossipItemFor(player, 10, "Testmenushow4", 1, 6, "", 0, true);
		SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, item->GetGUID());
	}
	
class example_ItemGossip : public ItemScript
{
public:
	example_ItemGossip() : ItemScript("GM3") { }

	bool OnUse(Player* player, Item* item, SpellCastTargets const& /*targets*/) override // Any hook here
	{
		ClearGossipMenuFor(player); // Clears old options
		Testmenu(player, item);
		return false; // Cast the spell on use normally
	}

	void OnGossipSelect(Player* player, Item* item, uint32 sender, uint32 action) override
	{
		ClearGossipMenuFor(player);

		switch (action)
		{
		case 10:
		{
			Testmenu(player, item);
			break;
		}
		case 11:
		{
			QueryResult re = CharacterDatabase.PQuery("SELECT x, y, z FROM teleport WHERE guid = %u", player->GetGUID());
			
			Field* f = re->Fetch();
			float posx, posy, posz;
			posx = f[0].GetFloat();
			posy = f[1].GetFloat();
			posz = f[2].GetFloat();
			player->TeleportTo(player->GetMapId(), posx, posy, posz, player->GetOrientation());
			Second(player, item);
			break;
		}
		case 12:
		{
			Second(player, item);
			break;
		}
		}
	}

	void OnGossipSelectCode(Player* player, Item* item, uint32 sender, uint32 action, const char* code) override
	{
		ClearGossipMenuFor(player);
		switch (action)
		{
		case 1:
		{
			uint32 entry = atol(code);
			LightEntry const* li = sLightStore.LookupEntry(entry);
			if (!li)
			{
				player->GetSession()->SendNotification("no entry found");
				Testmenu(player, item);
			}
			else
			{
				CharacterDatabase.PExecute("UPDATE start SET test = %u WHERE guid = %u", entry, player->GetGUID());
				First(player, item, code);
			}
			break;
		}
		case 2:
		{
			uint32 entry = atol(code);
			player->GetSession()->SendNotification("test add %u", entry);
			CharacterDatabase.PExecute("UPDATE start SET test = %u WHERE guid = %u", entry, player->GetGUID());
			Testmenu(player, item);
			break;
		}
		case 3:
		{
			uint32 entry = atol(code);
			CharacterDatabase.PExecute("UPDATE start SET test = %u WHERE guid = %u", entry, player->GetGUID());
			player->GetSession()->SendNotification("test add %u", entry);
			Testmenu(player, item);
			Second(player, item);
			break;
		}
		case 4:
		{
			int32 entry = atol(code);
			if (entry == -1)
			{
				player->GetSession()->SendNotification("-1");
				Testmenu(player, item);
			}
			else if (entry < -1)
			{
				player->GetSession()->SendNotification(">-1");
				Testmenu(player, item);
			}
			else
			{
				player->GetSession()->SendNotification("aleluq");
				Testmenu(player, item);
			}
			break;

		}
		case 5:
		{
			uint32 entry = atol(code);
			SkillLineEntry const* sle = sSkillLineStore.LookupEntry(entry);
			if (!sle)
			{
				player->GetSession()->SendNotification("testst");
				Testmenu(player, item);
			}
			else
			{
				ClassRaceSkillName(player, item, code);
			}
		}
		}
	}
};

void AddSC_DBCexplorer()
{
	new example_ItemGossip();
}
