#include "SharedDefines.h"
#include"ItemTemplate.h"
#include "ObjectMgr.h"
#include"Language.h"

#define NULL 0
using namespace std;

#define CREATE_NAMED_ENUM(VALUE) { VALUE, STRINGIZE(VALUE) }

#define NPCFLAG_COUNT   24
#define FLAGS_EXTRA_COUNT 19

auto flyspell = 200001;

enum RandomnNames
{
	itemset  = 1,
	randomp	=	2,
	randoms	=	3,
	spell = 4,
};
template<typename E, typename T = char const*>
struct EnumName
{
	E Value;
	T Name;
};
EnumName<NPCFlags, int32> const npcFlagTexts[NPCFLAG_COUNT] =
{
	{ UNIT_NPC_FLAG_AUCTIONEER,         LANG_NPCINFO_AUCTIONEER },
	{ UNIT_NPC_FLAG_BANKER,             LANG_NPCINFO_BANKER },
	{ UNIT_NPC_FLAG_BATTLEMASTER,       LANG_NPCINFO_BATTLEMASTER },
	{ UNIT_NPC_FLAG_FLIGHTMASTER,       LANG_NPCINFO_FLIGHTMASTER },
	{ UNIT_NPC_FLAG_GOSSIP,             LANG_NPCINFO_GOSSIP },
	{ UNIT_NPC_FLAG_GUILD_BANKER,       LANG_NPCINFO_GUILD_BANKER },
	{ UNIT_NPC_FLAG_INNKEEPER,          LANG_NPCINFO_INNKEEPER },
	{ UNIT_NPC_FLAG_PETITIONER,         LANG_NPCINFO_PETITIONER },
	{ UNIT_NPC_FLAG_PLAYER_VEHICLE,     LANG_NPCINFO_PLAYER_VEHICLE },
	{ UNIT_NPC_FLAG_QUESTGIVER,         LANG_NPCINFO_QUESTGIVER },
	{ UNIT_NPC_FLAG_REPAIR,             LANG_NPCINFO_REPAIR },
	{ UNIT_NPC_FLAG_SPELLCLICK,         LANG_NPCINFO_SPELLCLICK },
	{ UNIT_NPC_FLAG_SPIRITGUIDE,        LANG_NPCINFO_SPIRITGUIDE },
	{ UNIT_NPC_FLAG_SPIRITHEALER,       LANG_NPCINFO_SPIRITHEALER },
	{ UNIT_NPC_FLAG_STABLEMASTER,       LANG_NPCINFO_STABLEMASTER },
	{ UNIT_NPC_FLAG_TABARDDESIGNER,     LANG_NPCINFO_TABARDDESIGNER },
	{ UNIT_NPC_FLAG_TRAINER,            LANG_NPCINFO_TRAINER },
	{ UNIT_NPC_FLAG_TRAINER_CLASS,      LANG_NPCINFO_TRAINER_CLASS },
	{ UNIT_NPC_FLAG_TRAINER_PROFESSION, LANG_NPCINFO_TRAINER_PROFESSION },
	{ UNIT_NPC_FLAG_VENDOR,             LANG_NPCINFO_VENDOR },
	{ UNIT_NPC_FLAG_VENDOR_AMMO,        LANG_NPCINFO_VENDOR_AMMO },
	{ UNIT_NPC_FLAG_VENDOR_FOOD,        LANG_NPCINFO_VENDOR_FOOD },
	{ UNIT_NPC_FLAG_VENDOR_POISON,      LANG_NPCINFO_VENDOR_POISON },
	{ UNIT_NPC_FLAG_VENDOR_REAGENT,     LANG_NPCINFO_VENDOR_REAGENT }
};

EnumName<Mechanics> const mechanicImmunes[MAX_MECHANIC] =
{
	CREATE_NAMED_ENUM(MECHANIC_NONE),
	CREATE_NAMED_ENUM(MECHANIC_CHARM),
	CREATE_NAMED_ENUM(MECHANIC_DISORIENTED),
	CREATE_NAMED_ENUM(MECHANIC_DISARM),
	CREATE_NAMED_ENUM(MECHANIC_DISTRACT),
	CREATE_NAMED_ENUM(MECHANIC_FEAR),
	CREATE_NAMED_ENUM(MECHANIC_GRIP),
	CREATE_NAMED_ENUM(MECHANIC_ROOT),
	CREATE_NAMED_ENUM(MECHANIC_SLOW_ATTACK),
	CREATE_NAMED_ENUM(MECHANIC_SILENCE),
	CREATE_NAMED_ENUM(MECHANIC_SLEEP),
	CREATE_NAMED_ENUM(MECHANIC_SNARE),
	CREATE_NAMED_ENUM(MECHANIC_STUN),
	CREATE_NAMED_ENUM(MECHANIC_FREEZE),
	CREATE_NAMED_ENUM(MECHANIC_KNOCKOUT),
	CREATE_NAMED_ENUM(MECHANIC_BLEED),
	CREATE_NAMED_ENUM(MECHANIC_BANDAGE),
	CREATE_NAMED_ENUM(MECHANIC_POLYMORPH),
	CREATE_NAMED_ENUM(MECHANIC_BANISH),
	CREATE_NAMED_ENUM(MECHANIC_SHIELD),
	CREATE_NAMED_ENUM(MECHANIC_SHACKLE),
	CREATE_NAMED_ENUM(MECHANIC_MOUNT),
	CREATE_NAMED_ENUM(MECHANIC_INFECTED),
	CREATE_NAMED_ENUM(MECHANIC_TURN),
	CREATE_NAMED_ENUM(MECHANIC_HORROR),
	CREATE_NAMED_ENUM(MECHANIC_INVULNERABILITY),
	CREATE_NAMED_ENUM(MECHANIC_INTERRUPT),
	CREATE_NAMED_ENUM(MECHANIC_DAZE),
	CREATE_NAMED_ENUM(MECHANIC_DISCOVERY),
	CREATE_NAMED_ENUM(MECHANIC_IMMUNE_SHIELD),
	CREATE_NAMED_ENUM(MECHANIC_SAPPED),
	CREATE_NAMED_ENUM(MECHANIC_ENRAGED)
};

EnumName<UnitFlags> const unitFlags[MAX_UNIT_FLAGS] =
{
	CREATE_NAMED_ENUM(UNIT_FLAG_SERVER_CONTROLLED),
	CREATE_NAMED_ENUM(UNIT_FLAG_NON_ATTACKABLE),
	CREATE_NAMED_ENUM(UNIT_FLAG_REMOVE_CLIENT_CONTROL),
	CREATE_NAMED_ENUM(UNIT_FLAG_PVP_ATTACKABLE),
	CREATE_NAMED_ENUM(UNIT_FLAG_RENAME),
	CREATE_NAMED_ENUM(UNIT_FLAG_PREPARATION),
	CREATE_NAMED_ENUM(UNIT_FLAG_UNK_6),
	CREATE_NAMED_ENUM(UNIT_FLAG_NOT_ATTACKABLE_1),
	CREATE_NAMED_ENUM(UNIT_FLAG_IMMUNE_TO_PC),
	CREATE_NAMED_ENUM(UNIT_FLAG_IMMUNE_TO_NPC),
	CREATE_NAMED_ENUM(UNIT_FLAG_LOOTING),
	CREATE_NAMED_ENUM(UNIT_FLAG_PET_IN_COMBAT),
	CREATE_NAMED_ENUM(UNIT_FLAG_PVP),
	CREATE_NAMED_ENUM(UNIT_FLAG_SILENCED),
	CREATE_NAMED_ENUM(UNIT_FLAG_CANNOT_SWIM),
	CREATE_NAMED_ENUM(UNIT_FLAG_UNK_15),
	CREATE_NAMED_ENUM(UNIT_FLAG_UNK_16),
	CREATE_NAMED_ENUM(UNIT_FLAG_PACIFIED),
	CREATE_NAMED_ENUM(UNIT_FLAG_STUNNED),
	CREATE_NAMED_ENUM(UNIT_FLAG_IN_COMBAT),
	CREATE_NAMED_ENUM(UNIT_FLAG_TAXI_FLIGHT),
	CREATE_NAMED_ENUM(UNIT_FLAG_DISARMED),
	CREATE_NAMED_ENUM(UNIT_FLAG_CONFUSED),
	CREATE_NAMED_ENUM(UNIT_FLAG_FLEEING),
	CREATE_NAMED_ENUM(UNIT_FLAG_PLAYER_CONTROLLED),
	CREATE_NAMED_ENUM(UNIT_FLAG_NOT_SELECTABLE),
	CREATE_NAMED_ENUM(UNIT_FLAG_SKINNABLE),
	CREATE_NAMED_ENUM(UNIT_FLAG_MOUNT),
	CREATE_NAMED_ENUM(UNIT_FLAG_UNK_28),
	CREATE_NAMED_ENUM(UNIT_FLAG_UNK_29),
	CREATE_NAMED_ENUM(UNIT_FLAG_SHEATHE),
	CREATE_NAMED_ENUM(UNIT_FLAG_UNK_31)
};
std::string GetItemLink(uint32 item)
{
	const ItemTemplate* temp = sObjectMgr->GetItemTemplate(item);
	std::ostringstream ss;
	ss << "|c" << std::hex << ItemQualityColors[temp->Quality] << "|Hitem:" << std::dec << temp->ItemId << ":" << temp->socketBonus << ":0:0:0:0:0:0:" << (uint32)temp->ItemLevel << ":0|h[" << temp->Name1 << "]|h|r";
	return ss.str();
}
static const char* RaceId(uint8 id)
{
	switch (id)
	{
	case RACE_HUMAN:return"Human"; break;
	case RACE_ORC:return"Orc"; break;
	case RACE_DWARF:return"Dwarf"; break;
	case RACE_NIGHTELF:return"NightElf"; break;
	case RACE_UNDEAD_PLAYER:return"Undead"; break;
	case RACE_TAUREN:return"Tauren"; break;
	case RACE_GNOME:return"Gnome"; break;
	case RACE_TROLL:return"Troll"; break;
	case RACE_GOBLIN:return"Goblin"; break;
	case RACE_BLOODELF:return"BloodElf"; break;
	case RACE_DRAENEI:return"Draenei"; break;
	case RACE_FEL_ORC:return"Worgen"; break;
	case 13:return""; break;
	case 14:return""; break;
	case 15:return""; break;
	case 16:return""; break;
	case 17:return""; break;
	case 18:return""; break;
	case 19:return""; break;
	case 20:return""; break;
	case 21:return"Ice Troll"; break;
	case 22:return"Fel Orc"; break;
	case 23:return"Gilnean Human"; break;
	case 24:return"Pandarian"; break;
	case 25:return"Pandarian"; break;
	case 26:return"Pandarina"; break;
	default: return NULL;
	}
}
static const char * GetItemClass(uint32 ItemClass)
{
	switch (ItemClass)
	{
	case ITEM_CLASS_CONSUMABLE: return "[Consumable]"; break;
	case ITEM_CLASS_CONTAINER: return "[Container]"; break;
	case ITEM_CLASS_WEAPON: return "[Weapon]"; break;
	case ITEM_CLASS_GEM: return "[Gem]"; break;
	case ITEM_CLASS_ARMOR: return "[Armor]"; break;
	case ITEM_CLASS_REAGENT: return "[Reagent]"; break;
	case ITEM_CLASS_PROJECTILE: return "[Projectile]"; break;
	case ITEM_CLASS_TRADE_GOODS: return "[Trade Goods]"; break;
	case ITEM_CLASS_GENERIC: return "[Generic]"; break;
	case ITEM_CLASS_RECIPE: return "[Recipe]"; break;
	case ITEM_CLASS_MONEY: return "[Money]"; break;
	case ITEM_CLASS_QUIVER: return "[Quiver]"; break;
	case ITEM_CLASS_QUEST: return "[Quest]"; break;
	case ITEM_CLASS_KEY: return "[Key]"; break;
	case ITEM_CLASS_PERMANENT: return "[Permanent]"; break;
	case ITEM_CLASS_MISC: return "[Misc]"; break;
	case ITEM_CLASS_GLYPH: return "[Glyph]"; break;
	default: return NULL;
	}
}
static const char * GetQuality(uint8 quality)
{
	switch (quality)
	{
	case ITEM_QUALITY_POOR: return "|cff9d9d9d"; break;
	case ITEM_QUALITY_NORMAL: return "|cffffffff"; break;
	case ITEM_QUALITY_UNCOMMON: return "|cff1eff00"; break;
	case ITEM_QUALITY_RARE: return "|cff0070dd"; break;
	case ITEM_QUALITY_EPIC: return "|cffa335ee"; break;
	case ITEM_QUALITY_LEGENDARY: return "|cffff8000"; break;
	case ITEM_QUALITY_ARTIFACT: return "|cffFFFF80"; break;
	case ITEM_QUALITY_HEIRLOOM: return "|cffFFFF80"; break;
	default:return NULL;
	}
}
static string GetSheathe(uint8 Sheathe)
{
	switch (Sheathe)
	{
	case SHEATHETYPE_NONE: return "None"; break;
	case SHEATHETYPE_MAINHAND: return "Mainhand"; break;
	case SHEATHETYPE_OFFHAND: return "Offhand"; break;
	case SHEATHETYPE_LARGEWEAPONLEFT: return "LargeWeaponLeft"; break;
	case SHEATHETYPE_LARGEWEAPONRIGHT: return "LargeWeaponRight"; break;
	case SHEATHETYPE_HIPWEAPONLEFT: return "HipWeaponLeft"; break;
	case SHEATHETYPE_HIPWEAPONRIGHT: return "HipWeaponRight"; break;
	case SHEATHETYPE_SHIELD: return "Shield"; break;
	default:return NULL;
	}
}
static const char * GetGlyph(uint32 Glyph)
{
	switch (Glyph)
	{
	case ITEM_SUBCLASS_GLYPH_WARRIOR: return "Warrior"; break;
	case ITEM_SUBCLASS_GLYPH_PALADIN: return "Paladin"; break;
	case ITEM_SUBCLASS_GLYPH_HUNTER: return "Hunter"; break;
	case ITEM_SUBCLASS_GLYPH_ROGUE: return "Rouge"; break;
	case ITEM_SUBCLASS_GLYPH_PRIEST: return "Priest"; break;
	case ITEM_SUBCLASS_GLYPH_DEATH_KNIGHT: return "Death Knight"; break;
	case ITEM_SUBCLASS_GLYPH_SHAMAN: return "Shaman"; break;
	case ITEM_SUBCLASS_GLYPH_MAGE: return "Mage"; break;
	case ITEM_SUBCLASS_GLYPH_WARLOCK: return "Warlock"; break;
	case ITEM_SUBCLASS_GLYPH_DRUID: return "Druid"; break;
	default:return NULL;
	}
}
static const char * GetMisc(uint32 Misc)
{
	switch (Misc)
	{
	case ITEM_SUBCLASS_JUNK: return "Junk"; break;
	case ITEM_SUBCLASS_JUNK_REAGENT: return "Reagent"; break;
	case ITEM_SUBCLASS_JUNK_PET: return "Pet"; break;
	case ITEM_SUBCLASS_JUNK_HOLIDAY: return "Holyday"; break;
	case ITEM_SUBCLASS_JUNK_OTHER: return "Other"; break;
	case ITEM_SUBCLASS_JUNK_MOUNT: return "Mount"; break;
	default:return NULL;
	}
}
static const char * GetPermanent(uint32 Permanent)
{
	switch (Permanent)
	{
	case ITEM_SUBCLASS_PERMANENT: return "Permanent"; break;
	default:return NULL;
	}
}
static const char * GetKey(uint32 Key)
{
	switch (Key)
	{
	case ITEM_SUBCLASS_KEY: return "Key"; break;
	case ITEM_SUBCLASS_LOCKPICK: return "LockPick"; break;
	default:return NULL;
	}
}
static const char * GetQuest(uint32 Quest)
{
	switch (Quest)
	{
	case ITEM_SUBCLASS_QUEST: return "Quest"; break;
	default:return NULL;
	}
}
static const char * GetQuiver(uint32 Quiver)
{
	switch (Quiver)
	{
	case ITEM_SUBCLASS_QUIVER0: return "Quiver0"; break;
	case ITEM_SUBCLASS_QUIVER1: return "Quiver1"; break;
	case ITEM_SUBCLASS_QUIVER: return "Quiver"; break;
	case ITEM_SUBCLASS_AMMO_POUCH: return "Ammo Pouch"; break;
	default:return NULL;
	}
}
static const char * GetMoney(uint32 Money)
{
	switch (Money)
	{
	case ITEM_SUBCLASS_MONEY: return "Money"; break;
	default:return NULL;
	}
}
static const char * GetRecipe(uint32 Recipe)
{
	switch (Recipe)
	{
	case ITEM_SUBCLASS_BOOK: return "Book"; break;
	case ITEM_SUBCLASS_LEATHERWORKING_PATTERN: return "Leatherworking Pattern"; break;
	case ITEM_SUBCLASS_TAILORING_PATTERN: return "Tailoring Pattern"; break;
	case ITEM_SUBCLASS_ENGINEERING_SCHEMATIC: return "Engineering Schematic"; break;
	case ITEM_SUBCLASS_BLACKSMITHING: return "Blacksmithing"; break;
	case ITEM_SUBCLASS_COOKING_RECIPE: return "Cooking Recipe"; break;
	case ITEM_SUBCLASS_ALCHEMY_RECIPE: return "Alchemy Recipe"; break;
	case ITEM_SUBCLASS_FIRST_AID_MANUAL: return "First Aid Manuel"; break;
	case ITEM_SUBCLASS_ENCHANTING_FORMULA: return "Enchanting Formula"; break;
	case ITEM_SUBCLASS_FISHING_MANUAL: return "Fishing Manual"; break;
	case ITEM_SUBCLASS_JEWELCRAFTING_RECIPE: return "Jewekcrafting Recipe"; break;
	default:return NULL;
	}
}
static const char * GetGeneric(uint32 Generic)
{
	switch (Generic)
	{
	case ITEM_SUBCLASS_GENERIC: return "Generic"; break;
	default:return NULL;
	}
}
static const char * GetTradeGoods(uint32 TradeGoods)
{
	switch (TradeGoods)
	{
	case ITEM_SUBCLASS_TRADE_GOODS: return "Trade Goods"; break;
	case ITEM_SUBCLASS_PARTS: return "Parts"; break;
	case ITEM_SUBCLASS_EXPLOSIVES: return "Explosives"; break;
	case ITEM_SUBCLASS_DEVICES: return "Devices"; break;
	case ITEM_SUBCLASS_JEWELCRAFTING: return "Jewelcrafting"; break;
	case ITEM_SUBCLASS_CLOTH: return "Cloth"; break;
	case ITEM_SUBCLASS_LEATHER: return "Leather"; break;
	case ITEM_SUBCLASS_METAL_STONE: return "Metal Stone"; break;
	case ITEM_SUBCLASS_MEAT: return "Metal"; break;
	case ITEM_SUBCLASS_HERB: return "Herb"; break;
	case ITEM_SUBCLASS_ELEMENTAL: return "Elemental"; break;
	case ITEM_SUBCLASS_TRADE_GOODS_OTHER: return "Other(trade goods)"; break;
	case ITEM_SUBCLASS_ENCHANTING: return "Enchanting"; break;
	case ITEM_SUBCLASS_MATERIAL: return "Material"; break;
	case ITEM_SUBCLASS_ARMOR_ENCHANTMENT: return "Armor Enchant"; break;
	case ITEM_SUBCLASS_WEAPON_ENCHANTMENT: return "Weapon Enchant"; break;
	default:return NULL;
	}
}
static const char * GetProjectile(uint32 Projectile)
{
	switch (Projectile)
	{
	case ITEM_SUBCLASS_WAND: return "Wand"; break;
	case ITEM_SUBCLASS_BOLT: return "Bolt"; break;
	case ITEM_SUBCLASS_ARROW: return "Arrow"; break;
	case ITEM_SUBCLASS_BULLET: return "Bullet"; break;
	case ITEM_SUBCLASS_THROWN: return "Thrown"; break;
	default:return NULL;
	}
}
static const char * GetRegent(uint32 Regent)
{
	switch (Regent)
	{
	case ITEM_SUBCLASS_REAGENT: return "Regent"; break;
	default:return NULL;
	}
}
static const char * GetArmor(uint32 Armor)
{
	switch (Armor)
	{
	case ITEM_SUBCLASS_ARMOR_MISC: return "Misc"; break;
	case ITEM_SUBCLASS_ARMOR_CLOTH: return "Cloth"; break;
	case ITEM_SUBCLASS_ARMOR_LEATHER: return "Leather"; break;
	case ITEM_SUBCLASS_ARMOR_MAIL: return "Mail"; break;
	case ITEM_SUBCLASS_ARMOR_PLATE: return "Plate"; break;
	case ITEM_SUBCLASS_ARMOR_BUCKLER: return "Buckler"; break;
	case ITEM_SUBCLASS_ARMOR_SHIELD: return "Shield"; break;
	case ITEM_SUBCLASS_ARMOR_LIBRAM: return "Libram"; break;
	case ITEM_SUBCLASS_ARMOR_IDOL: return "Idol"; break;
	case ITEM_SUBCLASS_ARMOR_TOTEM: return "Totem"; break;
	case ITEM_SUBCLASS_ARMOR_SIGIL: return "Sigil"; break;
	default:return NULL;
	}
}
static const char * GetGem(uint32 Gem)
{
	switch (Gem)
	{
	case ITEM_SUBCLASS_GEM_RED: return "Red"; break;
	case ITEM_SUBCLASS_GEM_BLUE: return "Blue"; break;
	case ITEM_SUBCLASS_GEM_YELLOW: return "Yellow"; break;
	case ITEM_SUBCLASS_GEM_PURPLE: return "Purple"; break;
	case ITEM_SUBCLASS_GEM_GREEN: return "Green"; break;
	case ITEM_SUBCLASS_GEM_ORANGE: return "Orange"; break;
	case ITEM_SUBCLASS_GEM_META: return "Meta"; break;
	case ITEM_SUBCLASS_GEM_SIMPLE: return "Simple"; break;
	case ITEM_SUBCLASS_GEM_PRISMATIC: return "Prismatic"; break;
	case ITEM_SUBCLASS_GEM_HYDRAULIC: return "Hydraulic"; break;
	case ITEM_SUBCLASS_GEM_COGWHEEL: return "Cogwheel"; break;
	case ITEM_SUBCLASS_GEM_NEW: return "Unknown"; break;
	default:return NULL;
	}
}
static const char * GetWeapon(uint32 Weapon)
{
	switch (Weapon)
	{
	case ITEM_SUBCLASS_WEAPON_AXE: return "Axe"; break;
	case ITEM_SUBCLASS_WEAPON_AXE2: return "Axe 2h"; break;
	case ITEM_SUBCLASS_WEAPON_BOW: return "Bow"; break;
	case ITEM_SUBCLASS_WEAPON_GUN: return "Gun"; break;
	case ITEM_SUBCLASS_WEAPON_MACE: return "Mace"; break;
	case ITEM_SUBCLASS_WEAPON_MACE2: return "Mace 2h"; break;
	case ITEM_SUBCLASS_WEAPON_POLEARM: return "Polearm 2h"; break;
	case ITEM_SUBCLASS_WEAPON_SWORD: return "Sword"; break;
	case ITEM_SUBCLASS_WEAPON_SWORD2: return "Sword 2h"; break;
	case ITEM_SUBCLASS_WEAPON_obsolete: return "Obsolete"; break;
	case ITEM_SUBCLASS_WEAPON_STAFF: return "Staff 2h"; break;
	case ITEM_SUBCLASS_WEAPON_EXOTIC: return "Exotic"; break;
	case ITEM_SUBCLASS_WEAPON_EXOTIC2: return "Exotic 2h"; break;
	case ITEM_SUBCLASS_WEAPON_FIST: return "Fish"; break;
	case ITEM_SUBCLASS_WEAPON_MISC: return "Misc"; break;
	case ITEM_SUBCLASS_WEAPON_DAGGER: return "Dagger"; break;
	case ITEM_SUBCLASS_WEAPON_THROWN: return "Thrown"; break;
	case ITEM_SUBCLASS_WEAPON_SPEAR: return "Spear"; break;
	case ITEM_SUBCLASS_WEAPON_CROSSBOW: return "Crossbow"; break;
	case ITEM_SUBCLASS_WEAPON_WAND: return "Wand"; break;
	case ITEM_SUBCLASS_WEAPON_FISHING_POLE: return "Fishing Pole"; break;
	default: return NULL;
	}
}
static const char * GetConteiner(uint32 Conteiner)
{
	switch (Conteiner)
	{
	case ITEM_SUBCLASS_CONTAINER: return "Container"; break;
	case ITEM_SUBCLASS_SOUL_CONTAINER: return "Soul Container"; break;
	case ITEM_SUBCLASS_HERB_CONTAINER: return "Herb Container"; break;
	case ITEM_SUBCLASS_ENCHANTING_CONTAINER: return "Enchanting Container"; break;
	case ITEM_SUBCLASS_ENGINEERING_CONTAINER: return "Engineering Conteiner"; break;
	case ITEM_SUBCLASS_GEM_CONTAINER: return "Gem Container"; break;
	case ITEM_SUBCLASS_MINING_CONTAINER: return "Mining Container"; break;
	case ITEM_SUBCLASS_LEATHERWORKING_CONTAINER: return "LeatherWorking Container"; break;
	case ITEM_SUBCLASS_INSCRIPTION_CONTAINER: return "Inscription Container"; break;
	default:return NULL;
	}
}
static const char * GetConsummer(uint32 Consummer)
{
	switch (Consummer)
	{
	case ITEM_SUBCLASS_CONSUMABLE: return "Consumable"; break;
	case ITEM_SUBCLASS_POTION: return "Potion"; break;
	case ITEM_SUBCLASS_ELIXIR: return "Elixir"; break;
	case ITEM_SUBCLASS_FLASK: return "Flask"; break;
	case ITEM_SUBCLASS_SCROLL: return "Scroll"; break;
	case ITEM_SUBCLASS_FOOD: return "Food"; break;
	case ITEM_SUBCLASS_ITEM_ENHANCEMENT: return "Item Enchant"; break;
	case ITEM_SUBCLASS_BANDAGE: return "Bandage"; break;
	case ITEM_SUBCLASS_CONSUMABLE_OTHER: return "Other"; break;
	default:return NULL;
	}
}

static const char * GetItemInvetoryType(uint32 InventoryType)
{
	switch (InventoryType)
	{
	case INVTYPE_NON_EQUIP: return "No equp"; break;
	case INVTYPE_HEAD: return "Head"; break;
	case INVTYPE_NECK: return "Neck"; break;
	case INVTYPE_SHOULDERS: return "Shoulder"; break;
	case INVTYPE_BODY: return "Body"; break;
	case INVTYPE_CHEST: return "Chest"; break;
	case INVTYPE_WAIST: return "Waist"; break;
	case INVTYPE_LEGS: return "Legs"; break;
	case INVTYPE_FEET: return "Feet"; break;
	case INVTYPE_WRISTS: return "Wrists"; break;
	case INVTYPE_HANDS: return "Hands"; break;
	case INVTYPE_FINGER: return "Finger"; break;
	case INVTYPE_TRINKET: return "Trinket"; break;
	case INVTYPE_WEAPON: return "Weapon"; break;
	case INVTYPE_SHIELD: return "Shield"; break;
	case INVTYPE_RANGED: return "Ranged"; break;
	case INVTYPE_CLOAK: return "Cloak"; break;
	case INVTYPE_2HWEAPON: return "2HWeapon"; break;
	case INVTYPE_BAG: return "Bag"; break;
	case INVTYPE_TABARD: return "Tabard"; break;
	case INVTYPE_ROBE: return "Robe"; break;
	case INVTYPE_WEAPONMAINHAND: return "WeaponMainHand"; break;
	case INVTYPE_WEAPONOFFHAND: return "WeaponOffhand"; break;
	case INVTYPE_HOLDABLE: return "Holdable"; break;
	case INVTYPE_AMMO: return "Ammo"; break;
	case INVTYPE_THROWN: return "Thrown"; break;
	case INVTYPE_RANGEDRIGHT: return "Ranged"; break;
	case INVTYPE_QUIVER: return "Quiver"; break;
	case INVTYPE_RELIC: return "Relic"; break;
	default:return NULL;
	}

}

string GetItemSubclass(uint32 itemclass, uint32 itemsubclass)
{
	ostringstream stop;

	switch (itemclass)
	{
	case ITEM_CLASS_CONSUMABLE:{const char*test = GetConsummer(itemsubclass);stop << test;break;}
	case ITEM_CLASS_CONTAINER:{const char*test = GetConteiner(itemsubclass);stop << test;break;}
	case ITEM_CLASS_WEAPON:{const char*test = GetWeapon(itemsubclass);stop << test;break;}
	case ITEM_CLASS_GEM:{const char*test = GetGem(itemsubclass);stop << test;break;}
	case ITEM_CLASS_ARMOR:{const char*test = GetArmor(itemsubclass);stop << test;break;}
	case ITEM_CLASS_REAGENT: {const char*test = GetRegent(itemsubclass); stop << test; break; }
	case ITEM_CLASS_PROJECTILE:{const char*test = GetProjectile(itemsubclass);stop << test;break;}
	case ITEM_CLASS_TRADE_GOODS:{const char*test = GetTradeGoods(itemsubclass);stop << test;break;}
	case ITEM_CLASS_GENERIC:{const char*test = GetGeneric(itemsubclass);stop << test;break;}
	case ITEM_CLASS_RECIPE:{const char*test = GetRecipe(itemsubclass);stop << test;break;}
	case ITEM_CLASS_MONEY:{const char*test = GetMoney(itemsubclass);stop << test;break;}
	case ITEM_CLASS_QUIVER:{const char*test = GetQuiver(itemsubclass);stop << test;break;}
	case ITEM_CLASS_QUEST:{const char*test = GetQuest(itemsubclass);stop << test;break;}
	case ITEM_CLASS_KEY:{const char*test = GetKey(itemsubclass);stop << test;break;}
	case ITEM_CLASS_PERMANENT: {const char*test = GetPermanent(itemsubclass); stop << test; break; }
	case ITEM_CLASS_MISC: {const char*test = GetMisc(itemsubclass); stop << test; break; }
	case ITEM_CLASS_GLYPH:{const char*test = GetGlyph(itemsubclass);stop << test;break;}
	}
	return stop.str();
}
string ItemIcon(uint8 num, uint32 displayid)
{
	ostringstream os;
	ItemDisplayInfoEntry const * info = sItemDisplayInfoStore.LookupEntry(displayid);
	if (!info)
		os << "None";
	switch (num)
	{
	case 0:
		os << info->inventoryIcon[0];
		break;
	case 1:
		os << info->inventoryIcon[1];
		break;
	}
	return os.str();
}

string Money(uint32 incopper)
{
	uint32 gold, silver, copper;
	gold = incopper / GOLD;
	incopper -= gold * GOLD;
	silver = incopper / SILVER;
	incopper -= silver*SILVER;
	copper = incopper;
	ostringstream ss;
	if (gold)
		ss << gold<<"Gold";//<< "|TInterface\\MoneyFrame\\UI-GoldIcon:14:14|t";
	if (silver)
		ss << silver<<"Silver"; // "|TInterface\\MONEYFRAME\\UI-SilverIcon:14:14|t";
	if (copper)
		ss << copper<<"Copper"; //<< "|TInterface\\MoneyFrame\\UI-CopperIcon:14:14|t";
	if (!gold && !silver && !copper)
		ss << "NAH";
	return ss.str();
}

string SpellName(uint32 spellid)
{
	auto spell = sSpellStore.LookupEntry(spellid);
	if (!spell)
		return "SPELL_NOT_FOUND";
	std::ostringstream ss;
	ss << spell->Id << "-|cffffffff|Hspell:" << spell->Id << "|h[" << spell->SpellName << "]|h|r";
	return ss.str();
}

void ItemdisplayTemp(Player* player, Item* item, const char* code)
{
	uint32 entry = atol(code);
	ItemDisplayInfoEntry const * info = sItemDisplayInfoStore.LookupEntry(entry);
	ostringstream oss;
	uint32 id = info->ID;
	string all, model = info->modelname[0], model2 = info->modelname[1], modeltex = info->modeltexture[0], modeltex2 = info->modeltexture[1], icon = info->inventoryIcon[0], icon2 = info->inventoryIcon[1];
	if (model == "")
		model = "None";
	if (model2 == "")
		model2 = "None";
	if (modeltex == "")
		modeltex = "None";
	if (modeltex2 == "")
		modeltex2 = "None";
	if (icon == "")
		icon = "None";
	if (icon2 == "")
		icon2 = "None";
	oss << "Diplayid: " << id << " \nModel1: " << model << " \nModel2: " << model2 << " \nModeltex: " << modeltex << " \nModeltex2: " << modeltex2 << " \nIcon: " << icon << " \nIcon2: " << icon2;
	all = oss.str();
	AddGossipItemFor(player, 10, all.c_str(), 1, 81, "", 0, true);
	AddGossipItemFor(player, 10, "Back", 1, 3);
	SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, item->GetGUID());
}

string CreatureDIE(uint32 ExtraId)
{
	if (!ExtraId)
		return "None";
	CreatureDisplayInfoExtraEntry const *extraid = sCreatureDisplayInfoExtraStore.LookupEntry(ExtraId);
	if (extraid == NULL)
		return "No tex";
	ostringstream extra;
	extra << extraid->Texture;
	return extra.str();
}
string CreatureModelData(uint32 modelid)
{
	if (!modelid)
		return "None";
	CreatureModelDataEntry const *model = sCreatureModelDataStore.LookupEntry(modelid);
	ostringstream modelname;
	modelname << model->ModelPath;
	return modelname.str();
}
void CreatureDisplayExtra(Player* player, Item* item, const char* code)
{
	
	uint32 entry = atol(code);
	CreatureDisplayInfoExtraEntry const * info = sCreatureDisplayInfoExtraStore.LookupEntry(entry);
	uint32 id = info->Id, race = info->Race, gender = info->Gender, skincolor=info->SkinColor, facetype=info->FaceType, hairtype=info->HairType, hairstyle=info->HairStyle , helm = info->HelmDisplayId, shoulders = info->ShoulderDisplayId, shirt = info->ShirtDisplayId, chest = info->ChestDisplayId, belt = info->BeltDisplayId, legs = info->LegsDisplayId, boots = info->BootsDisplayId, wrist = info->WristDisplayId, gloves = info->GlovesDisplayId, tabard = info->TabardDisplayId, cloak = info->CloakDisplayId;
	ostringstream fax;
	if (info == NULL)
		fax << "sda" << "gvgg";
	else
		fax << "ExtraID: " << id << "\nRace: " << race <<"["<<RaceId(race)<<"]"<< "\nGender: " << gender<<"\nSkincolor: "<<skincolor<<"\nFaceType: "<<facetype<<"\nHairType: "<<hairtype<<"\nHairStyle: "<<hairstyle<< "\nHelm: " << helm << ItemIcon( 0,helm) << "\nShoulders: " << shoulders << ItemIcon( 0,shoulders) << "\nShirt: " << shirt << ItemIcon( 0,shirt) << "\nChest: " << chest << ItemIcon( 0,chest) << "\nBelt: " << belt << ItemIcon( 0,belt) << "\nLegs: " << legs << ItemIcon( 0,legs) << "\nBoots: " << boots << ItemIcon( 0,boots) << "\nWrist: " << wrist << ItemIcon( 0,wrist) << "\nGloves: " << gloves << ItemIcon( 0,gloves) << "\nTabard: " << tabard << ItemIcon( 0,tabard) << "\nCloak: " << cloak << ItemIcon( 0,cloak);
	string test = fax.str();
	AddGossipItemFor(player, 10, test, 1, 76, "", 0, true);
	AddGossipItemFor(player, 10, "back <=", 1, 3);
	SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, item->GetGUID());

}

string RandomDBCNames(char type, uint32 entry)
{
	ostringstream oss;

	switch(type)
	{
	case itemset:
	{
		ItemSetEntry const* info = sItemSetStore.LookupEntry(entry);
		if (info == NULL)
			return "None";
		oss << info->name[0];
		break;
	}
	case randomp:
	{
		ItemRandomPropertiesEntry const* info = sItemRandomPropertiesStore.LookupEntry(entry);
		if (info == NULL)
			return "None";
		oss << info->nameSuffix[0];
		break;
	}
	case randoms:
	{
		ItemRandomSuffixEntry const *info = sItemRandomSuffixStore.LookupEntry(entry);
		if (info == NULL)
			return"None";
		oss << info->nameSuffix[0];
		break;
	}
	case spell:
	{
		SpellEntry const*info = sSpellStore.LookupEntry(entry);
		if (info == NULL)
			return "none";
		oss << info->SpellName[0];
		break;
	}
	}
	return oss.str();
}
void CreaturesTran(Player* player, Item* item, const char* code)
{
	uint32 id = atol(code);
	CreatureTemplate const* info = sObjectMgr->GetCreatureTemplate(id);
	uint32 entry = info->Entry, md1=info->Modelid1, md2=info->Modelid2, md3 = info->Modelid3, md4=info->Modelid4,
		gosid=info->GossipMenuId, minlvl=info->mingold, maxlvl=info->maxlevel, exp=info->expansion, fact=info->faction,
		npcflag=info->npcflag, tratype=info->trainer_type, traspell=info->trainer_spell, traclass=info->trainer_class,
		trarace=info->trainer_race, crtype = info->type;
	string name = info->Name, title = info->Title, icon = info->IconName;
	ostringstream cre;
	cre << "Entry: " << entry << "\nName: " << name << "\nTitle: " << title << "\nIcon: " << icon << "\nModel1: " << md1 << "\nModel2: " << md2 << "\nModel3: "
		<< md3 << "\nModel4: " << md4 << "\nGossipId: " << gosid << "\nMinLvl: " << minlvl << "\nMaxLvl: " << maxlvl << "\nExpansion: " << exp << "\nFaction: " << fact
		<< "\nNpcflag: " << npcflag << "\nTrainerType: " << tratype << "\nTrainerSpell: " << traspell << "\nTrainerClass: " << traclass << "\nTrainerRace: " << trarace
		<< "\nCreatureType: " << crtype;
	AddGossipItemFor(player, 10, cre.str(), 1, 3);
	AddGossipItemFor(player, 10, "Creaturemodel", 1, 73, "", 0, true);
	AddGossipItemFor(player, 10, "Morph", GOSSIP_SENDER_MAIN, 19, "", 0, true);
	AddGossipItemFor(player, 10, "Back", 1, 3);
	SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, item->GetGUID());
}
void ItemTemplateMenu(Player* player, Item* item, const char* code)
{
	uint32 entry = atol(code);
	ItemTemplate const *info = sObjectMgr->GetItemTemplate(entry);
	uint32 id = info->ItemId, itemclass = info->Class, itemsubclass = info->SubClass,
		display = info->DisplayInfoID, quality = info->Quality, buycont = info->BuyCount, buyprice = info->BuyPrice, sellprice = info->SellPrice,
		invtype = info->InventoryType, itemlvl = info->ItemLevel, needlvl = info->RequiredLevel, contslot = info->ContainerSlots, material = info->Material, sheath = info->Sheath, itemsetid = info->ItemSet,
		randompop = info->RandomProperty, randomsurf = info->RandomSuffix, genprop = info->GemProperties, socketbon = info->socketBonus, sp1 = info->Spells[0].SpellId, sp2 = info->Spells[1].SpellId,
		sp3 = info->Spells[2].SpellId, sp4 = info->Spells[3].SpellId, sp5 = info->Spells[4].SpellId, scrid = info->ScriptId, fireres = info->FireRes, natres=info->NatureRes, frosres = info->FrostRes,
		shares=info->ShadowRes,arcres=info->ArcaneRes, delay = info->Delay,ammotype = info->AmmoType,bounding = info->Bonding, startqu = info->StartQuest ;
	int32 allowrace = info->AllowableRace, allowclass = info->AllowableClass;
	string name = "[" + info->Name1 + "]", scriptname = "["+sObjectMgr->GetScriptName(scrid)+"]", setname = RandomDBCNames(itemset, itemsetid), fax, fax2, icn = GetItemClass(itemclass), isn = GetItemSubclass(itemclass, itemsubclass),
		buy = Money(buyprice), sell = Money(sellprice), color = GetQuality(quality), type = GetItemInvetoryType(invtype) , desc = info->Description, shname = GetSheathe(sheath), spna = "[" + RandomDBCNames(spell, sp1) + "]"
		, spna2 = "[" + RandomDBCNames(spell, sp2) + "]", spna3 = "[" + RandomDBCNames(spell, sp3) + "]", spna4 = "[" + RandomDBCNames(spell, sp4) + "]", spna5 = "[" + RandomDBCNames(spell, sp5) + "]", itemic = "\n|TInterface\\icons\\"+ItemIcon(0,display)+".blp:28:28|t";
	float armor = info ->Armor, mindmg = info->Damage[0].DamageMin, maxdmg = info->Damage[0].DamageMax;
	ostringstream ss, ss2;
	if (itemic == "")
		itemic = "|TInterface\\icons\\Inv_misc_questionmark.blp:28:28|t";
	ss << "Item Entry: " << id << itemic << "Name: " << color << name << "|r" << "\nClass: " << itemclass << " " << icn <<
		"\nSubclass: " << itemsubclass << " " << isn << "\nDisplay: " << display << "\nBuycont: " << buycont << "\nBuyPrice: " << buy
		<< "\nSellPrice: " << sell << "\nItemLevel: " << itemlvl << "\nRequiredLevel: " << needlvl << "\nAllowableRace: " << allowrace
		<< "\nAllowableClass: " << allowclass << "\nArmor: " << armor << "\nInventoryType: " << invtype << " [" << type <<"]"<< "\nConteinerSlot: " << contslot
		<< "\nFireRes: " << fireres << "\nNatureRes: " << natres << "\nFrostRes: " << frosres << "\nShadowRes: " << shares << "\nArcaneRes: " << arcres <<
		"\nDelay: " << delay << "\nAmmoType: " << ammotype << "\nBounding: " << bounding << "\nDecription: " << desc << "\nStartQuest: " << startqu <<
		"\nSheath: " << sheath << shname << "\nRandomProperty: " << randompop << "\nRandomSuffix: " << randomsurf << "\nItemSet: " << itemsetid << "[" << setname << "]"
		<< "\nGenProperties: " << genprop << "\nSocketBonus: " << socketbon << "\nMaterial: " << material<<"\nScripId: "<<scrid<<scriptname<< "\nMinDmg: "<<mindmg<<"\nMaxDmg: "<<maxdmg;
	ss2 << "Spell: " << sp1 << spna << "\nSpell2: " << sp2 << spna2 << "\nSpell3: " << sp3 << spna3 << "\nSpell4: " << sp4 << spna4 << "\nSpell5: " << sp4 << spna5;

	ChatHandler(player->GetSession()).PSendSysMessage("ItemLink: %s", GetItemLink(id));
	fax = ss.str(), fax2 = ss2.str();
	AddGossipItemFor(player, 10, fax, 1, 82, "", 0, true);
	AddGossipItemFor(player, 10, fax2, 1, 3);
	AddGossipItemFor(player, 10, "AddTargetItem", 1, 72, "", 0, true);
	AddGossipItemFor(player, 10, "ItemDisplaytest", 1, 81, "", 0, true);
	AddGossipItemFor(player, 10, "Back", 1, 3);
	SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, item->GetGUID());
}
std::string CharClass(int32 entry)
{
	int32 warrior = entry - 1;
	entry -= warrior + 1;
	int32 paladin = entry - 2;
	entry -= paladin + 2;
	int32 hunter = entry - 4;
	entry -= hunter + 4;
	int32 rouge = entry - 8;
	entry = rouge + 8;
	int32 priest = entry - 16;
	entry -= priest + 16;
	int32 deathk = entry - 32;
	entry -= deathk + 32;
	int32 shaman = entry - 64;
	entry -= shaman + 64;
	int32 mage = entry - 128;
	entry -= mage + 128;
	int32 warlock = entry - 256;
	entry -= warlock + 256;
	int32 druid = entry - 1024;
	entry -= druid + 1024;

	std::ostringstream ss;
	if (entry == -1 && entry >= 262143)
		ss << "EVERYCLASS";
	if (warrior)
		ss << "Warrior";
	if (paladin)
		ss << "Paladin";
	if (hunter)
		ss << "Hunter";
	if (rouge)
		ss << "Rouge";
	if (priest)
		ss << "Priest";
	if (deathk)
		ss << "Death Knight";
	if (shaman)
		ss << "Shaman";
	if (mage)
		ss << "Mage";
	if (warlock)
		ss << "Warlock";
	if (druid)
		ss << "Druid\n";
	return ss.str();
}
std::string CharRace(int32 entry)
{
	int32 classr = entry;
	int32 worgen = classr - 2048;
	classr -= worgen + 2048;
	int32 draenei = classr - 1024;
	classr -= draenei + 1024;
	int32 belf = classr - 512;
	classr -= belf + 512;
	int32 goblin = classr - 256;
	classr -= goblin + 256;
	int32 troll = classr - 128;
	classr -= troll + 128;
	int32 gnom = classr - 64;
	classr -= gnom + 64;
	int32 tauren = classr - 32;
	classr -= tauren + 32;
	int32 undead = classr - 16;
	classr -= undead + 16;
	int32 nielf = classr - 8;
	classr = nielf + 8;
	int32 dwarf = classr - 4;
	classr -= dwarf + 4;
	int32 orc = classr - 2;
	classr -= orc + 2;
	int32 human = classr;

	std::ostringstream ss;

		if (human)
			ss << "Human,\n";
		if (orc)
			ss << "Orc\n";
		if (dwarf)
			ss << "Dwarf,\n";
		if (nielf)
			ss << "NightElf,\n";
		if (undead)
			ss << "Undead,\n";
		if (tauren)
			ss << "Tauren,\n";
		if (gnom)
			ss << "Gnome,\n";
		if (troll)
			ss << "Troll,\n";
		if (goblin)
			ss << "Goblin,\n";
		if (belf)
			ss << "Blood Elf,\n";
		if (draenei)
			ss << "Draenei,\n";
		if (worgen)
			ss << "Worgen";

		if (classr == -1 && classr >= 4095)
			ss << "EVERYCLASS";
		if (!worgen && !draenei && !belf)
			ss << "test";
	return ss.str();
}
static const char * GameObjType(uint32 type)
{
	switch (type)
	{
	case GAMEOBJECT_TYPE_DOOR: {return"DOOR"; break; }
	case GAMEOBJECT_TYPE_TRANSPORT: {return"TRANSPORT"; break; }
	case GAMEOBJECT_TYPE_FLAGSTAND: {return"FLAGSTAND"; break; }
	case GAMEOBJECT_TYPE_DUEL_ARBITER: {return"DUEL_ARBITER"; break; }
	case GAMEOBJECT_TYPE_GOOBER: {return"GOOBER"; break; }
	case GAMEOBJECT_TYPE_MO_TRANSPORT: {return"MO_TRANSPORT"; break; }
	case GAMEOBJECT_TYPE_AREADAMAGE: {return"AREADAMAGE"; break; }
	case GAMEOBJECT_TYPE_BUTTON: {return"BUTTON"; break; }
	case GAMEOBJECT_TYPE_MAP_OBJECT: {return"MAP_OBJECT"; break; }
	case GAMEOBJECT_TYPE_GUARDPOST: {return"GUARDPOST"; break; }
	case GAMEOBJECT_TYPE_QUESTGIVER: {return"QUESTGIVER"; break; }
	case GAMEOBJECT_TYPE_FISHINGNODE: {return"FISHINGNODE"; break; }
	case GAMEOBJECT_TYPE_CHEST: {return"CHEST"; break; }
	case GAMEOBJECT_TYPE_MAILBOX: {return"MAILBOX"; break; }
	case GAMEOBJECT_TYPE_MEETINGSTONE: {return"MEETINGSTONE"; break; }
	case GAMEOBJECT_TYPE_DO_NOT_USE: {return"DO_NOT_USE"; break; }
	case GAMEOBJECT_TYPE_SUMMONING_RITUAL: {return"SUMMONING_RITUAL"; break; }
	case GAMEOBJECT_TYPE_SPELLCASTER: {return"SPELLCASTER"; break; }
	case GAMEOBJECT_TYPE_CAMERA: {return"CAMERA"; break; }
	case GAMEOBJECT_TYPE_DO_NOT_USE_2: {return"DO_NOT_USE_2"; break; }
	case GAMEOBJECT_TYPE_FISHINGHOLE: {return"FISHINGHOLE"; break; }
	case GAMEOBJECT_TYPE_BARBER_CHAIR: {return"BARBER_CHAIR"; break; }
	case GAMEOBJECT_TYPE_MINI_GAME: {return"MINI_GAME"; break; }
	case GAMEOBJECT_TYPE_DUNGEON_DIFFICULTY: {return"DUNGEON_DIFFICULTY"; break; }
	case GAMEOBJECT_TYPE_CAPTURE_POINT: {return"CAPTURE_POINT"; break; }
	case GAMEOBJECT_TYPE_FLAGDROP: {return"FLAGDROP"; break; }
	case GAMEOBJECT_TYPE_AURA_GENERATOR: {return"AURA_GENERATOR"; break; }
	case GAMEOBJECT_TYPE_TRAP: {return"TRAP"; break; }
	case GAMEOBJECT_TYPE_BINDER: {return"BINDER"; break; }
	case GAMEOBJECT_TYPE_DESTRUCTIBLE_BUILDING: {return"DESTRUCTIBLE_BUILDING"; break; }
	case GAMEOBJECT_TYPE_TEXT: {return"TEXT"; break; }
	case GAMEOBJECT_TYPE_TRAPDOOR: {return"TRAPDOOR"; break; }
	case GAMEOBJECT_TYPE_SPELL_FOCUS: {return"SPELL_FOCUS"; break; }
	case GAMEOBJECT_TYPE_GENERIC: {return"GENERIC"; break; }
	case GAMEOBJECT_TYPE_GUILD_BANK: {return"GUILD_BANK"; break; }
	case GAMEOBJECT_TYPE_CHAIR: {return"CHAIR"; break; }
	default: return NULL;
	}
}
/*
std::string GetItemLink2(Item* item)
{
	const ItemTemplate* temp = item->GetTemplate();
	std::ostringstream ss;
	ss << "|c" << std::hex << ItemQualityColors[temp->Quality] << "|Hitem:" << std::dec << item->GetEntry() << ":" << item->GetEnchantmentId(PERM_ENCHANTMENT_SLOT) << ":0:0:0:0:0:0:" << (uint32)item->GetOwner()->getLevel() << ":0|h[" << temp->Name1 << "]|h|r";
	return ss.str();
}
*/
