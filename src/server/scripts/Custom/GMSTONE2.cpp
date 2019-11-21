#include"ScriptPCH.h"
#include"Language.h"
#include"Guild.h"
#include"ItemTemplate.h"
#include"WeatherMgr.h"
#include "Chat.h"
#include "ObjectMgr.h"
#include"Player.h"
#include "DBCStores.h"
#include "GossipDef.h"
#include "Define.h"
#include "Item.h"
#include "Player.h"
#include "ScriptedGossip.h"
#include "ScriptMgr.h"
#include "Spell.h"
#include "DatabaseEnv.h"
#include "WorldSession.h"
#include "Log.h"
#include "World.h"
#include "SpellMgr.h"
#include "Weather.h"
#include "AuctionHouseMgr.h"
#include "GMSTONE2.h"




static const char * GetSpellAuras(uint32 auraid)
{
	switch (auraid)
	{
		case SPELL_AURA_NONE: return "NONE"; break;
		case SPELL_AURA_BIND_SIGHT: return "BIND_SIGHT"; break;
		case SPELL_AURA_MOD_POSSESS: return "MOD_POSSESS"; break;
		case SPELL_AURA_PERIODIC_DAMAGE: return "PERIODIC_DAMAGE"; break;
			case SPELL_AURA_DUMMY: return "DUMMY"; break;
			case SPELL_AURA_MOD_CONFUSE: return "MOD_CONFUSE"; break;
			case SPELL_AURA_MOD_CHARM: return "MOD_CHARM"; break;
			case SPELL_AURA_MOD_FEAR: return "MOD_FEAR"; break;
			case SPELL_AURA_PERIODIC_HEAL: return "PERIODIC_HEAL"; break;
			case SPELL_AURA_MOD_ATTACKSPEED: return "MOD_ATTACKSPEED"; break;
			case SPELL_AURA_MOD_THREAT: return "MOD_THREAT"; break;
			case SPELL_AURA_MOD_TAUNT: return "MOD_TAUNT"; break;
			case SPELL_AURA_MOD_STUN: return "MOD_STUN"; break;
			case SPELL_AURA_MOD_DAMAGE_DONE: return "MOD_DAMAGE_DONE"; break;
			case SPELL_AURA_MOD_DAMAGE_TAKEN: return "MOD_DAMAGE_TAKEN"; break;
			case SPELL_AURA_DAMAGE_SHIELD: return "DAMAGE_SHIELD"; break;
			case SPELL_AURA_MOD_STEALTH: return "MOD_STEALTH"; break;
			case SPELL_AURA_MOD_STEALTH_DETECT: return "MOD_STEALTH_DETECT"; break;
			case SPELL_AURA_MOD_INVISIBILITY: return "MOD_INVISIBILITY"; break;
			case SPELL_AURA_MOD_INVISIBILITY_DETECT: return "MOD_INVISIBILITY_DETECT"; break;
			case SPELL_AURA_OBS_MOD_HEALTH: return "OBS_MOD_HEALTH"; break;   // 20"; break; 21 unofficial
			case SPELL_AURA_OBS_MOD_POWER: return "OBS_MOD_POWER"; break;
			case SPELL_AURA_MOD_RESISTANCE: return "MOD_RESISTANCE"; break;
			case SPELL_AURA_PERIODIC_TRIGGER_SPELL: return "PERIODIC_TRIGGER_SPELL"; break;
			case SPELL_AURA_PERIODIC_ENERGIZE: return "PERIODIC_ENERGIZE"; break;
			case SPELL_AURA_MOD_PACIFY: return "MOD_PACIFY"; break;
			case SPELL_AURA_MOD_ROOT: return "MOD_ROOT"; break;
			case SPELL_AURA_MOD_SILENCE: return "MOD_SILENCE"; break;
			case SPELL_AURA_REFLECT_SPELLS: return "REFLECT_SPELLS"; break;
			case SPELL_AURA_MOD_STAT: return "MOD_STAT"; break;
			case SPELL_AURA_MOD_SKILL: return "MOD_SKILL"; break;
			case SPELL_AURA_MOD_INCREASE_SPEED: return "MOD_INCREASE_SPEED"; break;
			case SPELL_AURA_MOD_INCREASE_MOUNTED_SPEED: return "MOD_INCREASE_MOUNTED_SPEED"; break;
			case SPELL_AURA_MOD_DECREASE_SPEED: return "MOD_DECREASE_SPEED"; break;
			case SPELL_AURA_MOD_INCREASE_HEALTH: return "MOD_INCREASE_HEALTH"; break;
			case SPELL_AURA_MOD_INCREASE_ENERGY: return "MOD_INCREASE_ENERGY"; break;
			case SPELL_AURA_MOD_SHAPESHIFT: return "MOD_SHAPESHIFT"; break;
			case SPELL_AURA_EFFECT_IMMUNITY: return "EFFECT_IMMUNITY"; break;
			case SPELL_AURA_STATE_IMMUNITY: return "STATE_IMMUNITY"; break;
			case SPELL_AURA_SCHOOL_IMMUNITY: return "SCHOOL_IMMUNITY"; break;
			case SPELL_AURA_DAMAGE_IMMUNITY: return "DAMAGE_IMMUNITY"; break;
			case SPELL_AURA_DISPEL_IMMUNITY: return "DISPEL_IMMUNITY"; break;
			case SPELL_AURA_PROC_TRIGGER_SPELL: return "PROC_TRIGGER_SPELL"; break;
			case SPELL_AURA_PROC_TRIGGER_DAMAGE: return "PROC_TRIGGER_DAMAGE"; break;
			case SPELL_AURA_TRACK_CREATURES: return "TRACK_CREATURES"; break;
			case SPELL_AURA_TRACK_RESOURCES: return "TRACK_RESOURCES"; break;
			case SPELL_AURA_46: return "46"; break;   // Ignore all Gear test spells
			case SPELL_AURA_MOD_PARRY_PERCENT: return "MOD_PARRY_PERCENT"; break;
			case SPELL_AURA_48: return "48"; break;   // One periodic spell
			case SPELL_AURA_MOD_DODGE_PERCENT: return "MOD_DODGE_PERCENT"; break;
			case SPELL_AURA_MOD_CRITICAL_HEALING_AMOUNT: return "MOD_CRITICAL_HEALING_AMOUNT"; break;
			case SPELL_AURA_MOD_BLOCK_PERCENT: return "MOD_BLOCK_PERCENT"; break;
			case SPELL_AURA_MOD_WEAPON_CRIT_PERCENT: return "MOD_WEAPON_CRIT_PERCENT"; break;
			case SPELL_AURA_PERIODIC_LEECH: return "PERIODIC_LEECH"; break;
			case SPELL_AURA_MOD_HIT_CHANCE: return "MOD_HIT_CHANCE"; break;
			case SPELL_AURA_MOD_SPELL_HIT_CHANCE: return "MOD_SPELL_HIT_CHANCE"; break;
			case SPELL_AURA_TRANSFORM: return "TRANSFORM"; break;
			case SPELL_AURA_MOD_SPELL_CRIT_CHANCE: return "MOD_SPELL_CRIT_CHANCE"; break;
			case SPELL_AURA_MOD_INCREASE_SWIM_SPEED: return "MOD_INCREASE_SWIM_SPEED"; break;
			case SPELL_AURA_MOD_DAMAGE_DONE_CREATURE: return "MOD_DAMAGE_DONE_CREATURE"; break;
			case SPELL_AURA_MOD_PACIFY_SILENCE: return "MOD_PACIFY_SILENCE"; break;
			case SPELL_AURA_MOD_SCALE: return "MOD_SCALE"; break;
			case SPELL_AURA_PERIODIC_HEALTH_FUNNEL: return "PERIODIC_HEALTH_FUNNEL"; break;
			case SPELL_AURA_63: return "63"; break;   // old case SPELL_AURA_PERIODIC_MANA_FUNNEL
			case SPELL_AURA_PERIODIC_MANA_LEECH: return "PERIODIC_MANA_LEECH"; break;
			case SPELL_AURA_MOD_CASTING_SPEED_NOT_STACK: return "MOD_CASTING_SPEED_NOT_STACK"; break;
			case SPELL_AURA_FEIGN_DEATH: return "FEIGN_DEATH"; break;
			case SPELL_AURA_MOD_DISARM: return "MOD_DISARM"; break;
			case SPELL_AURA_MOD_STALKED: return "MOD_STALKED"; break;
			case SPELL_AURA_SCHOOL_ABSORB: return "SCHOOL_ABSORB"; break;
			case SPELL_AURA_EXTRA_ATTACKS: return "EXTRA_ATTACKS"; break;
			case SPELL_AURA_MOD_SPELL_CRIT_CHANCE_SCHOOL: return "SPELL_CRIT_CHANCE_SCHOOL"; break;
			case SPELL_AURA_MOD_POWER_COST_SCHOOL_PCT: return "POWER_COST_SCHOOL_PCT"; break;
			case SPELL_AURA_MOD_POWER_COST_SCHOOL: return "POWER_COST_SCHOOL"; break;
			case SPELL_AURA_REFLECT_SPELLS_SCHOOL: return "REFLECT_SPELLS_SCHOOL"; break;
			case SPELL_AURA_MOD_LANGUAGE: return "LANGUAGE"; break;
			case SPELL_AURA_FAR_SIGHT: return "FAR_SIGHT"; break;
			case SPELL_AURA_MECHANIC_IMMUNITY: return "MECHANIC_IMMUNITY"; break;
			case SPELL_AURA_MOUNTED: return "MOUNTED"; break;
			case SPELL_AURA_MOD_DAMAGE_PERCENT_DONE: return "DAMAGE_PERCENT_DONE"; break;
			case SPELL_AURA_MOD_PERCENT_STAT: return "PERCENT_STAT"; break;
			case SPELL_AURA_SPLIT_DAMAGE_PCT: return "SPLIT_DAMAGE_PCT"; break;
			case SPELL_AURA_WATER_BREATHING: return "WATER_BREATHING"; break;
			case SPELL_AURA_MOD_BASE_RESISTANCE: return "BASE_RESISTANCE"; break;
			case SPELL_AURA_MOD_REGEN: return "REGEN"; break;
			case SPELL_AURA_MOD_POWER_REGEN: return "POWER_REGEN"; break;
			case SPELL_AURA_CHANNEL_DEATH_ITEM: return "CHANNEL_DEATH_ITEM"; break;
			case SPELL_AURA_MOD_DAMAGE_PERCENT_TAKEN: return "DAMAGE_PERCENT_TAKEN"; break;
			case SPELL_AURA_MOD_HEALTH_REGEN_PERCENT: return "HEALTH_REGEN_PERCENT"; break;
			case SPELL_AURA_PERIODIC_DAMAGE_PERCENT: return "PERIODIC_DAMAGE_PERCENT"; break;
			case SPELL_AURA_90: return "90"; break;   // old case SPELL_AURA_MOD_RESIST_CHANCE
			case SPELL_AURA_MOD_DETECT_RANGE: return "DETECT_RANGE"; break;
			case SPELL_AURA_PREVENTS_FLEEING: return "PREVENTS_FLEEING"; break;
			case SPELL_AURA_MOD_UNATTACKABLE: return "UNATTACKABLE"; break;
			case SPELL_AURA_INTERRUPT_REGEN: return "INTERRUPT_REGEN"; break;
			case SPELL_AURA_GHOST: return "GHOST"; break;
			case SPELL_AURA_SPELL_MAGNET: return "SPELL_MAGNET"; break;
			case SPELL_AURA_MANA_SHIELD: return "MANA_SHIELD"; break;
			case SPELL_AURA_MOD_SKILL_TALENT: return "SKILL_TALENT"; break;
			case SPELL_AURA_MOD_ATTACK_POWER: return "ATTACK_POWER"; break;
			case SPELL_AURA_AURAS_VISIBLE: return "AURAS_VISIBLE"; break;
			case SPELL_AURA_MOD_RESISTANCE_PCT: return "RESISTANCE_PCT"; break;
			case SPELL_AURA_MOD_MELEE_ATTACK_POWER_VERSUS: return "MELEE_ATTACK_POWER_VERSUS"; break;
			case SPELL_AURA_MOD_TOTAL_THREAT: return "TOTAL_THREA"; break;
			case SPELL_AURA_WATER_WALK: return "WATER_WALK"; break;
			case SPELL_AURA_FEATHER_FALL: return "FEATHER_FALL"; break;
			case SPELL_AURA_HOVER: return "HOVER"; break;
			case SPELL_AURA_ADD_FLAT_MODIFIER: return "FLAT_MODIFIER"; break;
			case SPELL_AURA_ADD_PCT_MODIFIER: return "ADD_PCT_MODIFIER"; break;
			case SPELL_AURA_ADD_TARGET_TRIGGER: return "TARGET_TRIGGER"; break;
			case SPELL_AURA_MOD_POWER_REGEN_PERCENT: return "POWER_REGEN_PERCENT"; break;
			case SPELL_AURA_ADD_CASTER_HIT_TRIGGER: return "CASTER_HIT_TRIGGER"; break;
			case SPELL_AURA_OVERRIDE_CLASS_SCRIPTS: return "OVERRIDE_CLASS_SCRIPTS"; break;
			case SPELL_AURA_MOD_RANGED_DAMAGE_TAKEN: return "RANGED_DAMAGE_TAKEN"; break;
			case SPELL_AURA_MOD_RANGED_DAMAGE_TAKEN_PCT: return "RANGED_DAMAGE_TAKEN_PCT"; break;
			case SPELL_AURA_MOD_HEALING: return "HEALING"; break;
			case SPELL_AURA_MOD_REGEN_DURING_COMBAT: return "REGEN_DURING_COMBAT"; break;
			case SPELL_AURA_MOD_MECHANIC_RESISTANCE: return "MECHANIC_RESISTANCE"; break;
			case SPELL_AURA_MOD_HEALING_PCT: return "HEALING_PCT"; break;
			case SPELL_AURA_119: return "119"; break;  // old case SPELL_AURA_SHARE_PET_TRACKING
			case SPELL_AURA_UNTRACKABLE: return "UNTRACKABLE"; break;
			case SPELL_AURA_EMPATHY: return "EMPATHY"; break;
			case SPELL_AURA_MOD_OFFHAND_DAMAGE_PCT: return "OFFHAND_DAMAGE_PCT"; break;
			case SPELL_AURA_MOD_TARGET_RESISTANCE: return "TARGET_RESISTANCE"; break;
			case SPELL_AURA_MOD_RANGED_ATTACK_POWER: return "RANGED_ATTACK_POWER"; break;
			case SPELL_AURA_MOD_MELEE_DAMAGE_TAKEN: return "MELEE_DAMAGE_TAKEN"; break;
			case SPELL_AURA_MOD_MELEE_DAMAGE_TAKEN_PCT: return "MELEE_DAMAGE_TAKEN_PCT"; break;
			case SPELL_AURA_RANGED_ATTACK_POWER_ATTACKER_BONUS: return "RANGED_ATTACK_POWER_ATTACKER_BONUS"; break;
			case SPELL_AURA_MOD_POSSESS_PET: return "POSSESS_PET"; break;
			case SPELL_AURA_MOD_SPEED_ALWAYS: return "SPEED_ALWAYS"; break;
			case SPELL_AURA_MOD_MOUNTED_SPEED_ALWAYS: return "MOD_MOUNTED_SPEED_ALWAYS"; break;
			case SPELL_AURA_MOD_RANGED_ATTACK_POWER_VERSUS: return "RANGED_ATTACK_POWER_VERSUS"; break;
			case SPELL_AURA_MOD_INCREASE_ENERGY_PERCENT: return "INCREASE_ENERGY_PERCENT"; break;
			case SPELL_AURA_MOD_INCREASE_HEALTH_PERCENT: return "INCREASE_HEALTH_PERCENT"; break;
			case SPELL_AURA_MOD_MANA_REGEN_INTERRUPT: return "MANA_REGEN_INTERRUPT"; break;
			case SPELL_AURA_MOD_HEALING_DONE: return "HEALING_DONE"; break;
			case SPELL_AURA_MOD_HEALING_DONE_PERCENT: return "HEALING_DONE_PERCENT"; break;
			case SPELL_AURA_MOD_TOTAL_STAT_PERCENTAGE: return "TOTAL_STAT_PERCENTAGE"; break;
			case SPELL_AURA_MOD_MELEE_HASTE: return "MELEE_HASTE"; break;
			case SPELL_AURA_FORCE_REACTION: return "FORCE_REACTION"; break;
			case SPELL_AURA_MOD_RANGED_HASTE: return "RANGED_HASTE"; break;
			case SPELL_AURA_MOD_RANGED_AMMO_HASTE: return "RANGED_AMMO_HASTE"; break;
			case SPELL_AURA_MOD_BASE_RESISTANCE_PCT: return "BASE_RESISTANCE_PCT"; break;
			case SPELL_AURA_MOD_RESISTANCE_EXCLUSIVE: return "RESISTANCE_EXCLUSIVE"; break;
			case SPELL_AURA_SAFE_FALL: return "SAFE_FALL"; break;
			case SPELL_AURA_MOD_PET_TALENT_POINTS: return "PET_TALENT_POINTS"; break;
			case SPELL_AURA_ALLOW_TAME_PET_TYPE: return "ALLOW_TAME_PET_TYPE"; break;
			case SPELL_AURA_MECHANIC_IMMUNITY_MASK: return "MECHANIC_IMMUNITY_MASK"; break;
			case SPELL_AURA_RETAIN_COMBO_POINTS: return "RETAIN_COMBO_POINTS"; break;
			case SPELL_AURA_REDUCE_PUSHBACK: return "AURA_REDUCE_PUSHBACK"; break;  //    Reduce Pushback
			case SPELL_AURA_MOD_SHIELD_BLOCKVALUE_PCT: return "MOD_SHIELD_BLOCKVALUE_PCT"; break;
			case SPELL_AURA_TRACK_STEALTHED: return "TRACK_STEALTHED"; break;  //    Track Stealthed
			case SPELL_AURA_MOD_DETECTED_RANGE: return "DETECTED_RANGE"; break;  //    Mod Detected Range
			case SPELL_AURA_SPLIT_DAMAGE_FLAT: return "SPLIT_DAMAGE_FLAT"; break;  //    Split Damage Flat
			case SPELL_AURA_MOD_STEALTH_LEVEL: return "STEALTH_LEVEL"; break;  //    Stealth Level Modifier
			case SPELL_AURA_MOD_WATER_BREATHING: return "WATER_BREATHING"; break;  //    Mod Water Breathing
			case SPELL_AURA_MOD_REPUTATION_GAIN: return "REPUTATION_GAIN"; break;  //    Mod Reputation Gain
			case SPELL_AURA_PET_DAMAGE_MULTI: return "PET_DAMAGE_MULTI"; break;  //    Mod Pet Damage
			case SPELL_AURA_MOD_SHIELD_BLOCKVALUE: return "SHIELD_BLOCKVALUE"; break;
			case SPELL_AURA_NO_PVP_CREDIT: return "NO_PVP_CREDIT"; break;
			case SPELL_AURA_MOD_AOE_AVOIDANCE: return "AOE_AVOIDANCE"; break;
			case SPELL_AURA_MOD_HEALTH_REGEN_IN_COMBAT: return "HEALTH_REGEN_IN_COMBAT"; break;
			case SPELL_AURA_POWER_BURN: return "POWER_BURN"; break;
			case SPELL_AURA_MOD_CRIT_DAMAGE_BONUS: return "CRIT_DAMAGE_BONUS"; break;
			case SPELL_AURA_164: return "164"; break;
			case SPELL_AURA_MELEE_ATTACK_POWER_ATTACKER_BONUS: return "MELEE_ATTACK_POWER_ATTACKER_BONUS"; break;
			case SPELL_AURA_MOD_ATTACK_POWER_PCT: return "ATTACK_POWER_PCT"; break;
			case SPELL_AURA_MOD_RANGED_ATTACK_POWER_PCT: return "RANGED_ATTACK_POWER_PCT"; break;
			case SPELL_AURA_MOD_DAMAGE_DONE_VERSUS: return "DAMAGE_DONE_VERSUS"; break;
			case SPELL_AURA_MOD_CRIT_PERCENT_VERSUS: return "CRIT_PERCENT_VERSUS"; break;
			case SPELL_AURA_DETECT_AMORE: return "DETECT_AMORE"; break;
			case SPELL_AURA_MOD_SPEED_NOT_STACK: return "SPEED_NOT_STACK"; break;
			case SPELL_AURA_MOD_MOUNTED_SPEED_NOT_STACK: return "MOUNTED_SPEED_NOT_STACK"; break;
			case SPELL_AURA_173: return "173"; break;  // old case SPELL_AURA_ALLOW_CHAMPION_SPELLS
			case SPELL_AURA_MOD_SPELL_DAMAGE_OF_STAT_PERCENT: return "SPELL_DAMAGE_OF_STAT_PERCENT"; break;  // by defeult intelect"; break; dependent from case SPELL_AURA_MOD_SPELL_HEALING_OF_STAT_PERCENT
			case SPELL_AURA_MOD_SPELL_HEALING_OF_STAT_PERCENT: return "SPELL_HEALING_OF_STAT_PERCENT"; break;
			case SPELL_AURA_SPIRIT_OF_REDEMPTION: return "SPIRIT_OF_REDEMPTION"; break;
			case SPELL_AURA_AOE_CHARM: return "AOE_CHARM"; break;
			case SPELL_AURA_MOD_DEBUFF_RESISTANCE: return "DEBUFF_RESISTANCE"; break;
			case SPELL_AURA_MOD_ATTACKER_SPELL_CRIT_CHANCE: return "ATTACKER_SPELL_CRIT_CHANCE"; break;
			case SPELL_AURA_MOD_FLAT_SPELL_DAMAGE_VERSUS: return "FLAT_SPELL_DAMAGE_VERSUS"; break;
			case SPELL_AURA_181: return "181"; break;  // old case SPELL_AURA_MOD_FLAT_SPELL_CRIT_DAMAGE_VERSUS - possible flat spell crit damage versus
			case SPELL_AURA_MOD_RESISTANCE_OF_STAT_PERCENT: return "RESISTANCE_OF_STAT_PERCENT"; break;
			case SPELL_AURA_MOD_CRITICAL_THREAT: return "CRITICAL_THREAT"; break;
			case SPELL_AURA_MOD_ATTACKER_MELEE_HIT_CHANCE: return "ATTACKER_MELEE_HIT_CHANCE"; break;
			case SPELL_AURA_MOD_ATTACKER_RANGED_HIT_CHANCE: return "ATTACKER_RANGED_HIT_CHANCE"; break;
			case SPELL_AURA_MOD_ATTACKER_SPELL_HIT_CHANCE: return "ATTACKER_SPELL_HIT_CHANCE"; break;
			case SPELL_AURA_MOD_ATTACKER_MELEE_CRIT_CHANCE: return "ATTACKER_MELEE_CRIT_CHANCE"; break;
			case SPELL_AURA_MOD_ATTACKER_RANGED_CRIT_CHANCE: return "ATTACKER_RANGED_CRIT_CHANCE"; break;
			case SPELL_AURA_MOD_RATING: return "MOD_RATING"; break;
			case SPELL_AURA_MOD_FACTION_REPUTATION_GAIN: return "FACTION_REPUTATION_GAIN"; break;
			case SPELL_AURA_USE_NORMAL_MOVEMENT_SPEED: return "USE_NORMAL_MOVEMENT_SPEED"; break;
			case SPELL_AURA_MOD_MELEE_RANGED_HASTE: return "MELEE_RANGED_HASTE"; break;
			case SPELL_AURA_MELEE_SLOW: return "MELEE_SLOW"; break;
			case SPELL_AURA_MOD_TARGET_ABSORB_SCHOOL: return "TARGET_ABSORB_SCHOOL"; break;
			case SPELL_AURA_MOD_TARGET_ABILITY_ABSORB_SCHOOL: return "ABILITY_ABSORB_SCHOOL"; break;
			case SPELL_AURA_MOD_COOLDOWN: return "MOD_COOLDOWN"; break;  // only 24818 Noxious Breath
			case SPELL_AURA_MOD_ATTACKER_SPELL_AND_WEAPON_CRIT_CHANCE: return "ATTACKER_SPELL_AND_WEAPON_CRIT_CHANCE"; break;
			case SPELL_AURA_198: return "198"; break;  // old case SPELL_AURA_MOD_ALL_WEAPON_SKILLS
			case SPELL_AURA_MOD_INCREASES_SPELL_PCT_TO_HIT: return "INCREASES_SPELL_PCT_TO_HIT"; break;
			case SPELL_AURA_MOD_XP_PCT: return "MOD_XP_PCT"; break;
			case SPELL_AURA_FLY: return "AURA_FLY"; break;
			case SPELL_AURA_IGNORE_COMBAT_RESULT: return "IGNORE_COMBAT_RESULT"; break;
			case SPELL_AURA_MOD_ATTACKER_MELEE_CRIT_DAMAGE: return "ATTACKER_MELEE_CRIT_DAMAGE"; break;
			case SPELL_AURA_MOD_ATTACKER_RANGED_CRIT_DAMAGE: return "ATTACKER_RANGED_CRIT_DAMAGE"; break;
			case SPELL_AURA_MOD_SCHOOL_CRIT_DMG_TAKEN: return "SCHOOL_CRIT_DMG_TAKEN"; break;
			case SPELL_AURA_MOD_INCREASE_VEHICLE_FLIGHT_SPEED: return "VEHICLE_FLIGHT_SPEED"; break;
			case SPELL_AURA_MOD_INCREASE_MOUNTED_FLIGHT_SPEED: return "MOUNTED_FLIGHT_SPEED"; break;
			case SPELL_AURA_MOD_INCREASE_FLIGHT_SPEED: return "INCREASE_FLIGHT_SPEED"; break;
			case SPELL_AURA_MOD_MOUNTED_FLIGHT_SPEED_ALWAYS: return "MOUNTED_FLIGHT_SPEED_ALWAYS:"; break;
			case SPELL_AURA_MOD_VEHICLE_SPEED_ALWAYS: return "VEHICLE_SPEED_ALWAYS"; break;
			case SPELL_AURA_MOD_FLIGHT_SPEED_NOT_STACK: return "FLIGHT_SPEED_NOT_STACK"; break;
			case SPELL_AURA_MOD_RANGED_ATTACK_POWER_OF_STAT_PERCENT: return "RANGED_ATTACK_POWER_OF_STAT_PERCENT"; break;
			case SPELL_AURA_MOD_RAGE_FROM_DAMAGE_DEALT: return "RAGE_FROM_DAMAGE_DEALT"; break;
			case SPELL_AURA_214: return "214"; break;
			case SPELL_AURA_ARENA_PREPARATION: return "ARENA_PREPARATION"; break;
			case SPELL_AURA_HASTE_SPELLS: return "HASTE_SPELLS"; break;
			case SPELL_AURA_MOD_MELEE_HASTE_2: return "MOD_MELEE_HASTE_2"; break; // NYI
			case SPELL_AURA_HASTE_RANGED: return "HASTE_RANGED"; break;
			case SPELL_AURA_MOD_MANA_REGEN_FROM_STAT: return "MANA_REGEN_FROM_STAT"; break;
			case SPELL_AURA_MOD_RATING_FROM_STAT: return "RATING_FROM_STAT"; break;
			case SPELL_AURA_MOD_DETAUNT: return "DETAUNT"; break;
			case SPELL_AURA_222: return "222"; break;
			case SPELL_AURA_RAID_PROC_FROM_CHARGE: return "RAID_PROC_FROM_CHARGE"; break;
			case SPELL_AURA_224: return "224"; break;
			case SPELL_AURA_RAID_PROC_FROM_CHARGE_WITH_VALUE: return "RAID_PROC_FROM_CHARGE_WITH_VALUE"; break;
			case SPELL_AURA_PERIODIC_DUMMY: return "PERIODIC_DUMMY"; break;
			case SPELL_AURA_PERIODIC_TRIGGER_SPELL_WITH_VALUE: return "PERIODIC_TRIGGER_SPELL_WITH_VALUE"; break;
			case SPELL_AURA_DETECT_STEALTH: return "DETECT_STEALTH"; break;
			case SPELL_AURA_MOD_AOE_DAMAGE_AVOIDANCE: return "AOE_DAMAGE_AVOIDANCE"; break;
			case SPELL_AURA_230: return "230"; break;
			case SPELL_AURA_PROC_TRIGGER_SPELL_WITH_VALUE: return "PROC_TRIGGER_SPELL_WITH_VALUE"; break;
			case SPELL_AURA_MECHANIC_DURATION_MOD: return "MECHANIC_DURATION_MOD"; break;
			case SPELL_AURA_CHANGE_MODEL_FOR_ALL_HUMANOIDS: return "CHANGE_MODEL_FOR_ALL_HUMANOIDS"; break;  // client-side only
			case SPELL_AURA_MECHANIC_DURATION_MOD_NOT_STACK: return "MECHANIC_DURATION_MOD_NOT_STACK"; break;
			case SPELL_AURA_MOD_DISPEL_RESIST: return "MOD_DISPEL_RESIST"; break;
			case SPELL_AURA_CONTROL_VEHICLE: return "CONTROL_VEHICLE"; break;
			case SPELL_AURA_MOD_SPELL_DAMAGE_OF_ATTACK_POWER: return "SPELL_DAMAGE_OF_ATTACK_POWER"; break;
			case SPELL_AURA_MOD_SPELL_HEALING_OF_ATTACK_POWER: return "SPELL_HEALING_OF_ATTACK_POWER"; break;
			case SPELL_AURA_MOD_SCALE_2: return "SCALE_2"; break;
			case SPELL_AURA_MOD_EXPERTISE: return "EXPERTISE"; break;
			case SPELL_AURA_FORCE_MOVE_FORWARD: return "FORCE_MOVE_FORWARD"; break;
			case SPELL_AURA_MOD_SPELL_DAMAGE_FROM_HEALING: return "SPELL_DAMAGE_FROM_HEALING"; break;
			case SPELL_AURA_MOD_FACTION: return "MOD_FACTION"; break;
			case SPELL_AURA_COMPREHEND_LANGUAGE: return "COMPREHEND_LANGUAGE"; break;
			case SPELL_AURA_MOD_AURA_DURATION_BY_DISPEL: return "AURA_DURATION_BY_DISPEL"; break;
			case SPELL_AURA_MOD_AURA_DURATION_BY_DISPEL_NOT_STACK: return "AURA_DURATION_BY_DISPEL_NOT_STACK"; break;
			case SPELL_AURA_CLONE_CASTER: return "CLONE_CASTER"; break;
			case SPELL_AURA_MOD_COMBAT_RESULT_CHANCE: return "COMBAT_RESULT_CHANCE"; break;
			case SPELL_AURA_CONVERT_RUNE: return "CONVERT_RUNE"; break;
			case SPELL_AURA_MOD_INCREASE_HEALTH_2: return "MOD_INCREASE_HEALTH_2"; break;
			case SPELL_AURA_MOD_ENEMY_DODGE: return "MOD_ENEMY_DODGE"; break;
			case SPELL_AURA_MOD_SPEED_SLOW_ALL: return "MOD_SPEED_SLOW_ALL"; break;
			case SPELL_AURA_MOD_BLOCK_CRIT_CHANCE: return "MOD_BLOCK_CRIT_CHANCE"; break;
			case SPELL_AURA_MOD_DISARM_OFFHAND: return "MOD_DISARM_OFFHAND"; break;
			case SPELL_AURA_MOD_MECHANIC_DAMAGE_TAKEN_PERCENT: return "MECHANIC_DAMAGE_TAKEN_PERCENT"; break;
			case SPELL_AURA_NO_REAGENT_USE: return "NO_REAGENT_USE"; break;
			case SPELL_AURA_MOD_TARGET_RESIST_BY_SPELL_CLASS: return "MOD_TARGET_RESIST_BY_SPELL_CLASS"; break;
			case SPELL_AURA_258: return "258"; break;
			case SPELL_AURA_MOD_HOT_PCT: return "MOD_HOT_PCT"; break;
			case SPELL_AURA_SCREEN_EFFECT: return "SCREEN_EFFECT"; break;
			case SPELL_AURA_PHASE: return "PHASE"; break;
			case SPELL_AURA_ABILITY_IGNORE_AURASTATE: return "ABILITY_IGNORE_AURASTATE"; break;
			case SPELL_AURA_ALLOW_ONLY_ABILITY: return "ALLOW_ONLY_ABILITY"; break;
			case SPELL_AURA_264: return "264"; break;
			case SPELL_AURA_265: return "265"; break;
			case SPELL_AURA_266: return "266"; break;
			case SPELL_AURA_MOD_IMMUNE_AURA_APPLY_SCHOOL: return "IMMUNE_AURA_APPLY_SCHOOL"; break;
			case SPELL_AURA_MOD_ATTACK_POWER_OF_STAT_PERCENT: return "ATTACK_POWER_OF_STAT_PERCENT"; break;
			case SPELL_AURA_MOD_IGNORE_TARGET_RESIST: return "IGNORE_TARGET_RESIST"; break;
			case SPELL_AURA_MOD_ABILITY_IGNORE_TARGET_RESIST: return "ABILITY_IGNORE_TARGET_RESIST"; break;  // Possibly need swap vs 195 aura used only in 1 spell Chaos Bolt Passive
			case SPELL_AURA_MOD_DAMAGE_FROM_CASTER: return "DAMAGE_FROM_CASTER"; break;
			case SPELL_AURA_IGNORE_MELEE_RESET: return "IGNORE_MELEE_RESET"; break;
			case SPELL_AURA_X_RAY: return "X_RAY"; break;
			case SPELL_AURA_ABILITY_CONSUME_NO_AMMO: return "ABILITY_CONSUME_NO_AMMO"; break;
			case SPELL_AURA_MOD_IGNORE_SHAPESHIFT: return "MOD_IGNORE_SHAPESHIFT"; break;
			case SPELL_AURA_MOD_DAMAGE_DONE_FOR_MECHANIC: return "DAMAGE_DONE_FOR_MECHANIC"; break;  // NYI
			case SPELL_AURA_MOD_MAX_AFFECTED_TARGETS: return "MAX_AFFECTED_TARGETS"; break;
			case SPELL_AURA_MOD_DISARM_RANGED: return "DISARM_RANGED"; break;
			case SPELL_AURA_INITIALIZE_IMAGES: return "INITIALIZE_IMAGES"; break;
			case SPELL_AURA_MOD_ARMOR_PENETRATION_PCT: return "ARMOR_PENETRATION_PCT"; break;
			case SPELL_AURA_MOD_HONOR_GAIN_PCT: return "MOD_HONOR_GAIN_PCT"; break;
			case SPELL_AURA_MOD_BASE_HEALTH_PCT: return "MOD_BASE_HEALTH_PCT"; break;
			case SPELL_AURA_MOD_HEALING_RECEIVED: return "MOD_HEALING_RECEIVED"; break;  // Possibly only for some spell family class spells
			case SPELL_AURA_LINKED: return "LINKED"; break;
			case SPELL_AURA_MOD_ATTACK_POWER_OF_ARMOR: return "MOD_ATTACK_POWER_OF_ARMOR"; break;
			case SPELL_AURA_ABILITY_PERIODIC_CRIT: return "ABILITY_PERIODIC_CRIT"; break;
			case SPELL_AURA_DEFLECT_SPELLS: return "DEFLECT_SPELLS"; break;
			case SPELL_AURA_IGNORE_HIT_DIRECTION: return "IGNORE_HIT_DIRECTION"; break;
			case SPELL_AURA_PREVENT_DURABILITY_LOSS: return "PREVENT_DURABILITY_LOSS"; break;
			case SPELL_AURA_MOD_CRIT_PCT: return "MOD_CRIT_PCT"; break;
			case SPELL_AURA_MOD_XP_QUEST_PCT: return "MOD_XP_QUEST_PCT"; break;
			case SPELL_AURA_OPEN_STABLE: return "OPEN_STABLE"; break;
			case SPELL_AURA_OVERRIDE_SPELLS: return "OVERRIDE_SPELLS"; break;
			case SPELL_AURA_PREVENT_REGENERATE_POWER: return "PREVENT_REGENERATE_POWER"; break;
			case SPELL_AURA_295: return "295"; break;
			case SPELL_AURA_SET_VEHICLE_ID: return "SET_VEHICLE_ID"; break;
			case SPELL_AURA_BLOCK_SPELL_FAMILY: return "BLOCK_SPELL_FAMILY"; break;
			case SPELL_AURA_STRANGULATE: return "STRANGULATE"; break;
			case SPELL_AURA_299: return "299"; break;
			case SPELL_AURA_SHARE_DAMAGE_PCT: return "SHARE_DAMAGE_PCT"; break;
			case SPELL_AURA_SCHOOL_HEAL_ABSORB: return "SCHOOL_HEAL_ABSORB"; break;
			case SPELL_AURA_302: return "302"; break;
			case SPELL_AURA_MOD_DAMAGE_DONE_VERSUS_AURASTATE: return "DAMAGE_DONE_VERSUS_AURASTATE"; break;
			case SPELL_AURA_MOD_FAKE_INEBRIATE: return "MOD_FAKE_INEBRIATE"; break;
			case SPELL_AURA_MOD_MINIMUM_SPEED: return "MOD_MINIMUM_SPEED"; break;
			case SPELL_AURA_306: return "306"; break;
			case SPELL_AURA_HEAL_ABSORB_TEST: return "HEAL_ABSORB_TEST"; break;
			case SPELL_AURA_MOD_CRIT_CHANCE_FOR_CASTER: return "CRIT_CHANCE_FOR_CASTER"; break;
			case SPELL_AURA_309: return "309"; break;
			case SPELL_AURA_MOD_CREATURE_AOE_DAMAGE_AVOIDANCE: return "CREATURE_AOE_DAMAGE_AVOIDANCE"; break;
			case SPELL_AURA_311: return "311"; break;
			case SPELL_AURA_312: return "312"; break;
			case SPELL_AURA_313: return "313"; break;
			case SPELL_AURA_PREVENT_RESURRECTION: return "AURA_PREVENT_RESURRECTION"; break;
			case SPELL_AURA_UNDERWATER_WALKING: return "AURA_UNDERWATER_WALKING"; break;
			case SPELL_AURA_PERIODIC_HASTE: return "PERIODIC_HASTE"; break;
			default: return "None";
	}
}
static const char * GetSpellEffect(uint32 spelleff)
{
	switch (spelleff)
	{
	        case 0: return "NO EFFECT"; break;
		    case SPELL_EFFECT_INSTAKILL : return "EFFECT_INSTAKILL" ; break;
			case SPELL_EFFECT_SCHOOL_DAMAGE : return "SCHOOL_DAMAGE" ; break;
			case SPELL_EFFECT_DUMMY : return "DUMMY" ; break;
			case SPELL_EFFECT_PORTAL_TELEPORT : return "PORTAL_TELEPORT" ; break;
			case SPELL_EFFECT_TELEPORT_UNITS : return "TELEPORT_UNITS" ; break;
			case SPELL_EFFECT_APPLY_AURA : return "APPLY_AURA" ; break;
			case SPELL_EFFECT_ENVIRONMENTAL_DAMAGE : return "ENVIRONMENTAL_DAMAGE" ; break;
			case SPELL_EFFECT_POWER_DRAIN : return "POWER_DRAIN" ; break;
			case SPELL_EFFECT_HEALTH_LEECH : return "HEALTH_LEECH" ; break;
			case SPELL_EFFECT_HEAL : return "HEAL" ; break;
			case SPELL_EFFECT_BIND : return "BIND" ; break;
			case SPELL_EFFECT_PORTAL : return "PORTAL" ; break;
			case SPELL_EFFECT_RITUAL_BASE : return "RITUAL_BASE" ; break;
			case SPELL_EFFECT_RITUAL_SPECIALIZE : return "RITUAL_SPECIALIZE" ; break;
			case SPELL_EFFECT_RITUAL_ACTIVATE_PORTAL : return "RITUAL_ACTIVATE_PORTAL" ; break;
			case SPELL_EFFECT_QUEST_COMPLETE : return "QUEST_COMPLETE" ; break;
			case SPELL_EFFECT_WEAPON_DAMAGE_NOSCHOOL : return "WEAPON_DAMAGE_NOSCHOOL" ; break;
			case SPELL_EFFECT_RESURRECT : return "RESURRECT" ; break;
			case SPELL_EFFECT_ADD_EXTRA_ATTACKS : return "ADD_EXTRA_ATTACKS" ; break;
			case SPELL_EFFECT_DODGE : return "DODGE" ; break;
			case SPELL_EFFECT_EVADE : return "EVADE" ; break;
			case SPELL_EFFECT_PARRY : return "PARRY" ; break;
			case SPELL_EFFECT_BLOCK : return "BLOCK" ; break;
			case SPELL_EFFECT_CREATE_ITEM : return "CREATE_ITEM" ; break;
			case SPELL_EFFECT_WEAPON : return "WEAPON" ; break;
			case SPELL_EFFECT_DEFENSE : return "DEFENSE" ; break;
			case SPELL_EFFECT_PERSISTENT_AREA_AURA : return "PERSISTENT_AREA_AURA" ; break;
			case SPELL_EFFECT_SUMMON : return "SUMMON" ; break;
			case SPELL_EFFECT_LEAP : return "LEAP" ; break;
			case SPELL_EFFECT_ENERGIZE : return "ENERGIZE" ; break;
			case SPELL_EFFECT_WEAPON_PERCENT_DAMAGE : return "WEAPON_PERCENT_DAMAGE" ; break;
			case SPELL_EFFECT_TRIGGER_MISSILE : return "TRIGGER_MISSILE" ; break;
			case SPELL_EFFECT_OPEN_LOCK : return "OPEN_LOCK" ; break;
			case SPELL_EFFECT_SUMMON_CHANGE_ITEM : return "SUMMON_CHANGE_ITEM" ; break;
			case SPELL_EFFECT_APPLY_AREA_AURA_PARTY : return "APPLY_AREA_AURA_PARTY" ; break;
			case SPELL_EFFECT_LEARN_SPELL : return "LEARN_SPELL" ; break;
			case SPELL_EFFECT_SPELL_DEFENSE : return "SPELL_DEFENSE" ; break;
			case SPELL_EFFECT_DISPEL : return "DISPEL" ; break;
			case SPELL_EFFECT_LANGUAGE : return "LANGUAGE" ; break;
			case SPELL_EFFECT_DUAL_WIELD : return " 40" ; break;
			case SPELL_EFFECT_JUMP : return "DUAL_WIELD" ; break;
			case SPELL_EFFECT_JUMP_DEST : return "JUMP_DEST" ; break;
			case SPELL_EFFECT_TELEPORT_UNITS_FACE_CASTER : return "TELEPORT_UNITS_FACE_CASTER" ; break;
			case SPELL_EFFECT_SKILL_STEP : return "SKILL_STEP" ; break;
			case SPELL_EFFECT_ADD_HONOR : return "ADD_HONOR" ; break;
			case SPELL_EFFECT_SPAWN : return "SPAWN" ; break;
			case SPELL_EFFECT_TRADE_SKILL : return "TRADE_SKILL" ; break;
			case SPELL_EFFECT_STEALTH : return "STEALTH" ; break;
			case SPELL_EFFECT_DETECT : return "DETECT" ; break;
			case SPELL_EFFECT_TRANS_DOOR : return "TRANS_DOOR" ; break;
			case SPELL_EFFECT_FORCE_CRITICAL_HIT : return "FORCE_CRITICAL_HIT" ; break;
			case SPELL_EFFECT_GUARANTEE_HIT : return "GUARANTEE_HIT" ; break;
			case SPELL_EFFECT_ENCHANT_ITEM : return "ENCHANT_ITEM" ; break;
			case SPELL_EFFECT_ENCHANT_ITEM_TEMPORARY : return "ENCHANT_ITEM_TEMPORARY" ; break;
			case SPELL_EFFECT_TAMECREATURE : return "TAMECREATURE" ; break;
			case SPELL_EFFECT_SUMMON_PET : return "SUMMON_PET" ; break;
			case SPELL_EFFECT_LEARN_PET_SPELL : return "LEARN_PET_SPELL" ; break;
			case SPELL_EFFECT_WEAPON_DAMAGE : return "WEAPON_DAMAGE" ; break;
			case SPELL_EFFECT_CREATE_RANDOM_ITEM : return "CREATE_RANDOM_ITEM" ; break;
			case SPELL_EFFECT_PROFICIENCY : return "PROFICIENCY" ; break;
			case SPELL_EFFECT_SEND_EVENT : return "SEND_EVENT" ; break;
			case SPELL_EFFECT_POWER_BURN : return "POWER_BURN" ; break;
			case SPELL_EFFECT_THREAT : return "THREAT" ; break;
			case SPELL_EFFECT_TRIGGER_SPELL : return "TRIGGER_SPELL" ; break;
			case SPELL_EFFECT_APPLY_AREA_AURA_RAID : return "APPLY_AREA_AURA_RAID" ; break;
			case SPELL_EFFECT_CREATE_MANA_GEM : return "CREATE_MANA_GEM" ; break;
			case SPELL_EFFECT_HEAL_MAX_HEALTH : return "HEAL_MAX_HEALTH" ; break;
			case SPELL_EFFECT_INTERRUPT_CAST : return "INTERRUPT_CAST" ; break;
			case SPELL_EFFECT_DISTRACT : return "DISTRACT" ; break;
			case SPELL_EFFECT_PULL : return "PULL" ; break;
			case SPELL_EFFECT_PICKPOCKET : return "PICKPOCKET" ; break;
			case SPELL_EFFECT_ADD_FARSIGHT : return "ADD_FARSIGHT" ; break;
			case SPELL_EFFECT_UNTRAIN_TALENTS : return "UNTRAIN_TALENTS" ; break;
			case SPELL_EFFECT_APPLY_GLYPH : return "APPLY_GLYPH" ; break;
			case SPELL_EFFECT_HEAL_MECHANICAL : return "HEAL_MECHANICAL" ; break;
			case SPELL_EFFECT_SUMMON_OBJECT_WILD : return "SUMMON_OBJECT_WILD" ; break;
			case SPELL_EFFECT_SCRIPT_EFFECT : return "SCRIPT_EFFECT" ; break;
			case SPELL_EFFECT_ATTACK : return "SCRIPT_EFFECT" ; break;
			case SPELL_EFFECT_SANCTUARY : return "SANCTUARY" ; break;
			case SPELL_EFFECT_ADD_COMBO_POINTS : return "ADD_COMBO_POINTS" ; break;
			case SPELL_EFFECT_CREATE_HOUSE : return "CREATE_HOUSE" ; break;
			case SPELL_EFFECT_BIND_SIGHT : return "BIND_SIGHT" ; break;
			case SPELL_EFFECT_DUEL : return "DUEL" ; break;
			case SPELL_EFFECT_STUCK : return "STUCK" ; break;
			case SPELL_EFFECT_SUMMON_PLAYER : return "SUMMON_PLAYER" ; break;
			case SPELL_EFFECT_ACTIVATE_OBJECT : return "ACTIVATE_OBJECT" ; break;
			case SPELL_EFFECT_GAMEOBJECT_DAMAGE : return "GAMEOBJECT_DAMAGE" ; break;
			case SPELL_EFFECT_GAMEOBJECT_REPAIR : return "GAMEOBJECT_REPAIR" ; break;
			case SPELL_EFFECT_GAMEOBJECT_SET_DESTRUCTION_STATE : return "GAMEOBJECT_SET_DE" ; break;
			case SPELL_EFFECT_KILL_CREDIT : return "KILL_CREDIT" ; break;
			case SPELL_EFFECT_THREAT_ALL : return "THREAT_ALL" ; break;
			case SPELL_EFFECT_ENCHANT_HELD_ITEM : return "ENCHANT_HELD_ITEM" ; break;
			case SPELL_EFFECT_FORCE_DESELECT : return "FORCE_DESELECT" ; break;
			case SPELL_EFFECT_SELF_RESURRECT : return "SELF_RESURRECT" ; break;
			case SPELL_EFFECT_SKINNING : return "SKINNING" ; break;
			case SPELL_EFFECT_CHARGE : return "CHARGE" ; break;
			case SPELL_EFFECT_CAST_BUTTON : return "CAST_BUTTON" ; break;
			case SPELL_EFFECT_KNOCK_BACK : return "KNOCK_BACK" ; break;
			case SPELL_EFFECT_DISENCHANT : return "DISENCHANT" ; break;
			case SPELL_EFFECT_INEBRIATE : return "INEBRIATE" ; break;
			case SPELL_EFFECT_FEED_PET : return "FEED_PET" ; break;
			case SPELL_EFFECT_DISMISS_PET : return "DISMISS_PET" ; break;
			case SPELL_EFFECT_REPUTATION : return "REPUTATION" ; break;
			case SPELL_EFFECT_SUMMON_OBJECT_SLOT1 : return "SUMMON_OBJECT_SLOT1" ; break;
			case SPELL_EFFECT_SUMMON_OBJECT_SLOT2 : return "SUMMON_OBJECT_SLOT2" ; break;
			case SPELL_EFFECT_SUMMON_OBJECT_SLOT3 : return "SUMMON_OBJECT_SLOT3" ; break;
			case SPELL_EFFECT_SUMMON_OBJECT_SLOT4 : return "SUMMON_OBJECT_SLOT4" ; break;
			case SPELL_EFFECT_DISPEL_MECHANIC : return "DISPEL_MECHANIC" ; break;
			case SPELL_EFFECT_RESURRECT_PET : return "RESURRECT_PET" ; break;
			case SPELL_EFFECT_DESTROY_ALL_TOTEMS : return "DESTROY_ALL_TOTEMS" ; break;
			case SPELL_EFFECT_DURABILITY_DAMAGE : return "DURABILITY_DAMAGE" ; break;
			case SPELL_EFFECT_112 : return " 112" ; break;
			case SPELL_EFFECT_RESURRECT_NEW : return "RESURRECT_NEW" ; break;
			case SPELL_EFFECT_ATTACK_ME : return "ATTACK_ME" ; break;
			case SPELL_EFFECT_DURABILITY_DAMAGE_PCT : return "DURABILITY_DAMAGE_PCT" ; break;
			case SPELL_EFFECT_SKIN_PLAYER_CORPSE : return "SKIN_PLAYER_CORPSE" ; break;
			case SPELL_EFFECT_SPIRIT_HEAL : return "SPIRIT_HEAL" ; break;
			case SPELL_EFFECT_SKILL : return "SKILL" ; break;
			case SPELL_EFFECT_APPLY_AREA_AURA_PET : return "APPLY_AREA_AURA_PET" ; break;
			case SPELL_EFFECT_TELEPORT_GRAVEYARD : return "TELEPORT_GRAVEYARD" ; break;
			case SPELL_EFFECT_NORMALIZED_WEAPON_DMG : return "NORMALIZED_WEAPON_DMG" ; break;
			case SPELL_EFFECT_122 : return " 122" ; break;
			case SPELL_EFFECT_SEND_TAXI : return "SEND_TAXI" ; break;
			case SPELL_EFFECT_PULL_TOWARDS : return "PULL_TOWARDS" ; break;
			case SPELL_EFFECT_MODIFY_THREAT_PERCENT : return "MODIFY_THREAT_PERCENT" ; break;
			case SPELL_EFFECT_STEAL_BENEFICIAL_BUFF : return "STEAL_BENEFICIAL_BUFF" ; break;
			case SPELL_EFFECT_PROSPECTING : return "PROSPECTING" ; break;
			case SPELL_EFFECT_APPLY_AREA_AURA_FRIEND : return "APPLY_AREA_AURA_FRIEND" ; break;
			case SPELL_EFFECT_APPLY_AREA_AURA_ENEMY : return "APPLY_AREA_AURA_ENEMY" ; break;
			case SPELL_EFFECT_REDIRECT_THREAT : return "REDIRECT_THREAT" ; break;
			case SPELL_EFFECT_PLAY_SOUND : return "PLAY_SOUND" ; break;
			case SPELL_EFFECT_PLAY_MUSIC : return "PLAY_MUSIC" ; break;
			case SPELL_EFFECT_UNLEARN_SPECIALIZATION : return "UNLEARN_SPECIALIZATION" ; break;
			case SPELL_EFFECT_KILL_CREDIT2 : return "KILL_CREDIT2" ; break;
			case SPELL_EFFECT_CALL_PET : return "CALL_PET" ; break;
			case SPELL_EFFECT_HEAL_PCT : return "HEAL_PCT" ; break;
			case SPELL_EFFECT_ENERGIZE_PCT : return "ENERGIZE_PCT" ; break;
			case SPELL_EFFECT_LEAP_BACK : return "LEAP_BACK" ; break;
			case SPELL_EFFECT_CLEAR_QUEST : return "CLEAR_QUEST" ; break;
			case SPELL_EFFECT_FORCE_CAST : return "FORCE_CAST" ; break;
			case SPELL_EFFECT_FORCE_CAST_WITH_VALUE : return "FORCE_CAST_WITH_VALUE" ; break;
			case SPELL_EFFECT_TRIGGER_SPELL_WITH_VALUE : return "TRIGGER_SPELL_WITH_VALUE" ; break;
			case SPELL_EFFECT_APPLY_AREA_AURA_OWNER : return "APPLY_AREA_AURA_OWNER" ; break;
			case SPELL_EFFECT_KNOCK_BACK_DEST : return "KNOCK_BACK_DEST" ; break;
			case SPELL_EFFECT_PULL_TOWARDS_DEST : return "PULL_TOWARDS_DEST" ; break;
			case SPELL_EFFECT_ACTIVATE_RUNE : return "ACTIVATE_RUNE" ; break;
			case SPELL_EFFECT_QUEST_FAIL : return "QUEST_FAIL" ; break;
			case SPELL_EFFECT_TRIGGER_MISSILE_SPELL_WITH_VALUE : return "TRIGGER_MISSILE_SPELL_WITH_VALUE" ; break;
			case SPELL_EFFECT_CHARGE_DEST : return "CHARGE_DEST" ; break;
			case SPELL_EFFECT_QUEST_START : return "QUEST_START" ; break;
			case SPELL_EFFECT_TRIGGER_SPELL_2 : return "TRIGGER_SPELL_2" ; break;
			case SPELL_EFFECT_SUMMON_RAF_FRIEND : return "SUMMON_RAF_FRIEND" ; break;
			case SPELL_EFFECT_CREATE_TAMED_PET : return "CREATE_TAMED_PET" ; break;
			case SPELL_EFFECT_DISCOVER_TAXI : return "DISCOVER_TAXI" ; break;
			case SPELL_EFFECT_TITAN_GRIP : return "TITAN_GRIP" ; break;
			case SPELL_EFFECT_ENCHANT_ITEM_PRISMATIC : return "ENCHANT_ITEM_PRISMATIC" ; break;
			case SPELL_EFFECT_CREATE_ITEM_2 : return "CREATE_ITEM_2" ; break;
			case SPELL_EFFECT_MILLING : return "MILLING" ; break;
			case SPELL_EFFECT_ALLOW_RENAME_PET : return "ALLOW_RENAME_PET" ; break;
			case SPELL_EFFECT_FORCE_CAST_2 : return "FORCE_CAST_2" ; break;
			case SPELL_EFFECT_TALENT_SPEC_COUNT : return "TALENT_SPEC_COUNT" ; break;
			case SPELL_EFFECT_TALENT_SPEC_SELECT : return "TALENT_SPEC_SELECT" ; break;
			case SPELL_EFFECT_163 : return " 163" ; break;
			case SPELL_EFFECT_REMOVE_AURA : return "REMOVE_AURA" ; break;
			default: return NULL;
	}
}




using namespace std;
string red = "|cffFF0000";
string green = "|cff1eff00";
string grey = "|cff9d9d9d";
string blue = "|cff0070dd";
string yellow = "|cffFFFF80";
string purple = "|cffa335ee";
string white = "|cffffffff";
string orange = "|cffff8000";

class ADDGMTOOLS : public PlayerScript
{
   public:
	ADDGMTOOLS() : PlayerScript("GMTOOLS") {}

	void OnLogin(Player* player, bool firstlogin)
	{
		if (player->GetSession()->GetSecurity() > SEC_PLAYER)
		{
			if (!player->HasItemCount(60001, 1, true) && !player->HasItemCount(60002, 1, true) && !player->HasItemCount(60003,1,true))
			{
				player->AddItem(60001, 1);
				player->AddItem(60002, 1);
				player->AddItem(60003, 1);
			}
			else
			{
				ChatHandler(player->GetSession()).PSendSysMessage("UTEST");
			}
		}
	}
};
class GMSTONE2 : public ItemScript
{
public:
	GMSTONE2() : ItemScript("GM2") {}

	string Ras(uint32 entrytest)
	{
		GameObjectTemplate const * info = sObjectMgr->GetGameObjectTemplate(entrytest);
		ostringstream tres;
		switch (info->type)
		{
		case GAMEOBJECT_TYPE_DOOR: {tres << "startOpen:" << info->door.startOpen << "\nlockId:" << info->door.lockId << "\nautoCloseTime:" << info->door.autoCloseTime; break; }
		case GAMEOBJECT_TYPE_BUTTON: {tres << "startOpen:" << info->button.startOpen; break; }
		case GAMEOBJECT_TYPE_QUESTGIVER: {tres << "openTextID:" << info->questgiver.openTextID; break; }
		case GAMEOBJECT_TYPE_CHEST: {tres << "openTextID:" << info->chest.openTextID; break; }
		case GAMEOBJECT_TYPE_BINDER: {tres << "4"; break; }
		case GAMEOBJECT_TYPE_GENERIC: {tres << "conditionID1:" << info->_generic.conditionID1; break; }
		case GAMEOBJECT_TYPE_TRAP: {tres << "closeTextID:" << info->trap.closeTextID; break; }
		case GAMEOBJECT_TYPE_CHAIR: {tres << "conditionID1:" << info->chair.conditionID1; break; }
		case GAMEOBJECT_TYPE_SPELL_FOCUS: {tres << "8"; break; }
		case GAMEOBJECT_TYPE_TEXT: {tres << "pageID:" << info->text.pageID; break; }
		case GAMEOBJECT_TYPE_GOOBER: {tres << "openTextID:" << info->goober.openTextID; break; }
		case GAMEOBJECT_TYPE_TRANSPORT: {tres << "startOpen:" << info->transport.startOpen << "\nPause:" << info->transport.pause << "\npause1EventID:" << info->transport.pause1EventID << "\npause2EventID:" << info->transport.pause2EventID << "\nautoCloseTime:" << info->transport.autoCloseTime << "\nmapID:" << info->transport.mapID; break; }
		case GAMEOBJECT_TYPE_AREADAMAGE: {tres << "openTextID:" << info->areadamage.openTextID; break; }
		case GAMEOBJECT_TYPE_CAMERA: {tres << "openTextID:" << info->camera.openTextID; break; }
		case GAMEOBJECT_TYPE_MAP_OBJECT: {tres << "14"; break; }
		case GAMEOBJECT_TYPE_MO_TRANSPORT: {tres << "mapID:" << info->moTransport.mapID; break; }
		case GAMEOBJECT_TYPE_DUEL_ARBITER: {tres << "16"; break; }
		case GAMEOBJECT_TYPE_FISHINGNODE: {tres << "17"; break; }
		case GAMEOBJECT_TYPE_SUMMONING_RITUAL: {tres << "spellId:" << info->summoningRitual.spellId; break; }
		case GAMEOBJECT_TYPE_MAILBOX: {tres << "conditionID1:" << info->mailbox.conditionID1; break; }
		case GAMEOBJECT_TYPE_DO_NOT_USE: {tres << "20"; break; }
		case GAMEOBJECT_TYPE_GUARDPOST: {tres << "21" << info->guardpost.creatureID; break; }
		case GAMEOBJECT_TYPE_SPELLCASTER: {tres << "spellId:" << info->spellcaster.spellId; break; }
		case GAMEOBJECT_TYPE_MEETINGSTONE: {tres << "23" << info->meetingstone.areaID; break; }
		case GAMEOBJECT_TYPE_FLAGSTAND: {tres << "openTextID:" << info->flagstand.openTextID; break; }
		case GAMEOBJECT_TYPE_FISHINGHOLE: {tres << "lockId:" << info->fishinghole.lockId; break; }
		case GAMEOBJECT_TYPE_FLAGDROP: {tres << "openTextID:" << info->flagdrop.openTextID; break; }
		case GAMEOBJECT_TYPE_MINI_GAME: {tres << "gameType:" << info->miniGame.gameType; break; }
		case GAMEOBJECT_TYPE_DO_NOT_USE_2: {tres << "28"; break; }
		case GAMEOBJECT_TYPE_CAPTURE_POINT: {tres << "radius:" << info->capturePoint.radius; break; }
		case GAMEOBJECT_TYPE_AURA_GENERATOR: {tres << "radius:" << info->auraGenerator.radius; break; }
		case GAMEOBJECT_TYPE_DUNGEON_DIFFICULTY: {tres << "mapID:" << info->dungeonDifficulty.mapID; break; }
		case GAMEOBJECT_TYPE_BARBER_CHAIR: {tres << "chairheight:" << info->barberChair.chairheight; break; }
		case GAMEOBJECT_TYPE_DESTRUCTIBLE_BUILDING: {tres << "33"; break; }
		case GAMEOBJECT_TYPE_GUILD_BANK: {tres << "conditionID1:" << info->guildbank.conditionID1; break; }
		case GAMEOBJECT_TYPE_TRAPDOOR: {tres << "startOpen:" << info->trapDoor.startOpen; break; }
		}
		return tres.str();
	}
	
	string SpellTest(uint32 spellid2)
	{
		if (!spellid2)
			return "None";
		SpellEntry const *spellinfo = sSpellStore.LookupEntry(spellid2);
		if (!spellinfo)
			return "None";
		int locale = 0;
		ostringstream spelltest;
		spelltest << spellinfo->SpellName[locale];
		return spelltest.str();
	}
	string TestAura(uint32 effect, uint32 info)
	{
		ostringstream stop2;
		switch (effect)
		{
		case SPELL_EFFECT_INSTAKILL: {stop2 << "None"; break; }
		case SPELL_EFFECT_SCHOOL_DAMAGE: {stop2 << "None"; break; }
		case SPELL_EFFECT_DUMMY: {stop2 << "None"; break; }
		case SPELL_EFFECT_PORTAL_TELEPORT: {stop2 << "None"; break; }
		case SPELL_EFFECT_TELEPORT_UNITS: {stop2 << "None"; break; }
		case SPELL_EFFECT_APPLY_AURA: {const char* test = GetSpellAuras(info); stop2 << test; break; }
		case SPELL_EFFECT_ENVIRONMENTAL_DAMAGE: {stop2 << "None"; break; }
		case SPELL_EFFECT_POWER_DRAIN: {stop2 << "None"; break; }
		case SPELL_EFFECT_HEALTH_LEECH: {stop2 << "None"; break; }
		case SPELL_EFFECT_HEAL: {stop2 << "None"; break; }
		case SPELL_EFFECT_BIND: {stop2 << "None"; break; }
		case SPELL_EFFECT_PORTAL: {stop2 << "None"; break; }
		case SPELL_EFFECT_RITUAL_BASE: {stop2 << "None"; break; }
		case SPELL_EFFECT_RITUAL_SPECIALIZE: {stop2 << "None"; break; }
		case SPELL_EFFECT_RITUAL_ACTIVATE_PORTAL: {stop2 << "None"; break; }
		case SPELL_EFFECT_QUEST_COMPLETE: {stop2 << "None"; break; }
		case SPELL_EFFECT_WEAPON_DAMAGE_NOSCHOOL: {stop2 << "None"; break; }
		case SPELL_EFFECT_RESURRECT: {stop2 << "None"; break; }
		case SPELL_EFFECT_ADD_EXTRA_ATTACKS: {stop2 << "None"; break; }
		case SPELL_EFFECT_DODGE: {stop2 << "None"; break; }
		case SPELL_EFFECT_EVADE: {stop2 << "None"; break; }
		case SPELL_EFFECT_PARRY: {stop2 << "None"; break; }
		case SPELL_EFFECT_BLOCK: {stop2 << "None"; break; }
		case SPELL_EFFECT_CREATE_ITEM: {stop2 << "None"; break; }
		case SPELL_EFFECT_WEAPON: {stop2 << "None"; break; }
		case SPELL_EFFECT_DEFENSE: {stop2 << "None"; break; }
		case SPELL_EFFECT_PERSISTENT_AREA_AURA: {stop2 << "None"; break; }
		case SPELL_EFFECT_SUMMON: {stop2 << "None"; break; }
		case SPELL_EFFECT_LEAP: {stop2 << "None"; break; }
		case SPELL_EFFECT_ENERGIZE: {stop2 << "None"; break; }
		case SPELL_EFFECT_WEAPON_PERCENT_DAMAGE: {stop2 << "None"; break; }
		case SPELL_EFFECT_TRIGGER_MISSILE: {stop2 << "None"; break; }
		case SPELL_EFFECT_OPEN_LOCK: {stop2 << "None"; break; }
		case SPELL_EFFECT_SUMMON_CHANGE_ITEM: {stop2 << "None"; break; }
		case SPELL_EFFECT_APPLY_AREA_AURA_PARTY: {stop2 << "None"; break; }
		case SPELL_EFFECT_LEARN_SPELL: {stop2 << "None"; break; }
		case SPELL_EFFECT_SPELL_DEFENSE: {stop2 << "None"; break; }
		case SPELL_EFFECT_DISPEL: {stop2 << "None"; break; }
		case SPELL_EFFECT_LANGUAGE: {stop2 << "None"; break; }
		case SPELL_EFFECT_DUAL_WIELD: {stop2 << "None"; break; }
		case SPELL_EFFECT_JUMP: {stop2 << "None"; break; }
		case SPELL_EFFECT_JUMP_DEST: {stop2 << "None"; break; }
		case SPELL_EFFECT_TELEPORT_UNITS_FACE_CASTER: {stop2 << "None"; break; }
		case SPELL_EFFECT_SKILL_STEP: {stop2 << "None"; break; }
		case SPELL_EFFECT_ADD_HONOR: {stop2 << "None"; break; }
		case SPELL_EFFECT_SPAWN: {stop2 << "None"; break; }
		case SPELL_EFFECT_TRADE_SKILL: {stop2 << "None"; break; }
		case SPELL_EFFECT_STEALTH: {stop2 << "None"; break; }
		case SPELL_EFFECT_DETECT: {stop2 << "None"; break; }
		case SPELL_EFFECT_TRANS_DOOR: {stop2 << "None"; break; }
		case SPELL_EFFECT_FORCE_CRITICAL_HIT: {stop2 << "None"; break; }
		case SPELL_EFFECT_GUARANTEE_HIT: {stop2 << "None"; break; }
		case SPELL_EFFECT_ENCHANT_ITEM: {stop2 << "None"; break; }
		case SPELL_EFFECT_ENCHANT_ITEM_TEMPORARY: {stop2 << "None"; break; }
		case SPELL_EFFECT_TAMECREATURE: {stop2 << "None"; break; }
		case SPELL_EFFECT_SUMMON_PET: {stop2 << "None"; break; }
		case SPELL_EFFECT_LEARN_PET_SPELL: {stop2 << "None"; break; }
		case SPELL_EFFECT_WEAPON_DAMAGE: {stop2 << "None"; break; }
		case SPELL_EFFECT_CREATE_RANDOM_ITEM: {stop2 << "None"; break; }
		case SPELL_EFFECT_PROFICIENCY: {stop2 << "None"; break; }
		case SPELL_EFFECT_SEND_EVENT: {stop2 << "None"; break; }
		case SPELL_EFFECT_POWER_BURN: {stop2 << "None"; break; }
		case SPELL_EFFECT_THREAT: {stop2 << "None"; break; }
		case SPELL_EFFECT_TRIGGER_SPELL: {stop2 << "None"; break; }
		case SPELL_EFFECT_APPLY_AREA_AURA_RAID: {stop2 << "None"; break; }
		case SPELL_EFFECT_CREATE_MANA_GEM: {stop2 << "None"; break; }
		case SPELL_EFFECT_HEAL_MAX_HEALTH: {stop2 << "None"; break; }
		case SPELL_EFFECT_INTERRUPT_CAST: {stop2 << "None"; break; }
		case SPELL_EFFECT_DISTRACT: {stop2 << "None"; break; }
		case SPELL_EFFECT_PULL: {stop2 << "None"; break; }
		case SPELL_EFFECT_PICKPOCKET: {stop2 << "None"; break; }
		case SPELL_EFFECT_ADD_FARSIGHT: {stop2 << "None"; break; }
		case SPELL_EFFECT_UNTRAIN_TALENTS: {stop2 << "None"; break; }
		case SPELL_EFFECT_APPLY_GLYPH: {stop2 << "None"; break; }
		case SPELL_EFFECT_HEAL_MECHANICAL: {stop2 << "None"; break; }
		case SPELL_EFFECT_SUMMON_OBJECT_WILD: {stop2 << "None"; break; }
		case SPELL_EFFECT_SCRIPT_EFFECT: {stop2 << "None"; break; }
		case SPELL_EFFECT_ATTACK: {stop2 << "None"; break; }
		case SPELL_EFFECT_SANCTUARY: {stop2 << "None"; break; }
		case SPELL_EFFECT_ADD_COMBO_POINTS: {stop2 << "None"; break; }
		case SPELL_EFFECT_CREATE_HOUSE: {stop2 << "None"; break; }
		case SPELL_EFFECT_BIND_SIGHT: {stop2 << "None"; break; }
		case SPELL_EFFECT_DUEL: {stop2 << "None"; break; }
		case SPELL_EFFECT_STUCK: {stop2 << "None"; break; }
		case SPELL_EFFECT_SUMMON_PLAYER: {stop2 << "None"; break; }
		case SPELL_EFFECT_ACTIVATE_OBJECT: {stop2 << "None"; break; }
		case SPELL_EFFECT_GAMEOBJECT_DAMAGE: {stop2 << "None"; break; }
		case SPELL_EFFECT_GAMEOBJECT_REPAIR: {stop2 << "None"; break; }
		case SPELL_EFFECT_GAMEOBJECT_SET_DESTRUCTION_STATE: {stop2 << "None"; break; }
		case SPELL_EFFECT_KILL_CREDIT: {stop2 << "None"; break; }
		case SPELL_EFFECT_THREAT_ALL: {stop2 << "None"; break; }
		case SPELL_EFFECT_ENCHANT_HELD_ITEM: {stop2 << "None"; break; }
		case SPELL_EFFECT_FORCE_DESELECT: {stop2 << "None"; break; }
		case SPELL_EFFECT_SELF_RESURRECT: {stop2 << "None"; break; }
		case SPELL_EFFECT_SKINNING: {stop2 << "None"; break; }
		case SPELL_EFFECT_CHARGE: {stop2 << "None"; break; }
		case SPELL_EFFECT_CAST_BUTTON: {stop2 << "None"; break; }
		case SPELL_EFFECT_KNOCK_BACK: {stop2 << "None"; break; }
		case SPELL_EFFECT_DISENCHANT: {stop2 << "None"; break; }
		case SPELL_EFFECT_INEBRIATE: {stop2 << "None"; break; }
		case SPELL_EFFECT_FEED_PET: {stop2 << "None"; break; }
		case SPELL_EFFECT_DISMISS_PET: {stop2 << "None"; break; }
		case SPELL_EFFECT_REPUTATION: {stop2 << "None"; break; }
		case SPELL_EFFECT_SUMMON_OBJECT_SLOT1: {stop2 << "None"; break; }
		case SPELL_EFFECT_SUMMON_OBJECT_SLOT2: {stop2 << "None"; break; }
		case SPELL_EFFECT_SUMMON_OBJECT_SLOT3: {stop2 << "None"; break; }
		case SPELL_EFFECT_SUMMON_OBJECT_SLOT4: {stop2 << "None"; break; }
		case SPELL_EFFECT_DISPEL_MECHANIC: {stop2 << "None"; break; }
		case SPELL_EFFECT_RESURRECT_PET: {stop2 << "None"; break; }
		case SPELL_EFFECT_DESTROY_ALL_TOTEMS: {stop2 << "None"; break; }
		case SPELL_EFFECT_DURABILITY_DAMAGE: {stop2 << "None"; break; }
		case SPELL_EFFECT_112: {stop2 << "None"; break; }
		case SPELL_EFFECT_RESURRECT_NEW: {stop2 << "None"; break; }
		case SPELL_EFFECT_ATTACK_ME: {stop2 << "None"; break; }
		case SPELL_EFFECT_DURABILITY_DAMAGE_PCT: {stop2 << "None"; break; }
		case SPELL_EFFECT_SKIN_PLAYER_CORPSE: {stop2 << "None"; break; }
		case SPELL_EFFECT_SPIRIT_HEAL: {stop2 << "None"; break; }
		case SPELL_EFFECT_SKILL: {stop2 << "None"; break; }
		case SPELL_EFFECT_APPLY_AREA_AURA_PET: {stop2 << "None"; break; }
		case SPELL_EFFECT_TELEPORT_GRAVEYARD: {stop2 << "None"; break; }
		case SPELL_EFFECT_NORMALIZED_WEAPON_DMG: {stop2 << "None"; break; }
		case SPELL_EFFECT_122: {stop2 << "None"; break; }
		case SPELL_EFFECT_SEND_TAXI: {stop2 << "None"; break; }
		case SPELL_EFFECT_PULL_TOWARDS: {stop2 << "None"; break; }
		case SPELL_EFFECT_MODIFY_THREAT_PERCENT: {stop2 << "None"; break; }
		case SPELL_EFFECT_STEAL_BENEFICIAL_BUFF: {stop2 << "None"; break; }
		case SPELL_EFFECT_PROSPECTING: {stop2 << "None"; break; }
		case SPELL_EFFECT_APPLY_AREA_AURA_FRIEND: {stop2 << "None"; break; }
		case SPELL_EFFECT_APPLY_AREA_AURA_ENEMY: {stop2 << "None"; break; }
		case SPELL_EFFECT_REDIRECT_THREAT: {stop2 << "None"; break; }
		case SPELL_EFFECT_PLAY_SOUND: {stop2 << "None"; break; }
		case SPELL_EFFECT_PLAY_MUSIC: {stop2 << "None"; break; }
		case SPELL_EFFECT_UNLEARN_SPECIALIZATION: {stop2 << "None"; break; }
		case SPELL_EFFECT_KILL_CREDIT2: {stop2 << "None"; break; }
		case SPELL_EFFECT_CALL_PET: {stop2 << "None"; break; }
		case SPELL_EFFECT_HEAL_PCT: {stop2 << "None"; break; }
		case SPELL_EFFECT_ENERGIZE_PCT: {stop2 << "None"; break; }
		case SPELL_EFFECT_LEAP_BACK: {stop2 << "None"; break; }
		case SPELL_EFFECT_CLEAR_QUEST: {stop2 << "None"; break; }
		case SPELL_EFFECT_FORCE_CAST: {stop2 << "None"; break; }
		case SPELL_EFFECT_FORCE_CAST_WITH_VALUE: {stop2 << "None"; break; }
		case SPELL_EFFECT_TRIGGER_SPELL_WITH_VALUE: {stop2 << "None"; break; }
		case SPELL_EFFECT_APPLY_AREA_AURA_OWNER: {stop2 << "None"; break; }
		case SPELL_EFFECT_KNOCK_BACK_DEST: {stop2 << "None"; break; }
		case SPELL_EFFECT_PULL_TOWARDS_DEST: {stop2 << "None"; break; }
		case SPELL_EFFECT_ACTIVATE_RUNE: {stop2 << "None"; break; }
		case SPELL_EFFECT_QUEST_FAIL: {stop2 << "None"; break; }
		case SPELL_EFFECT_TRIGGER_MISSILE_SPELL_WITH_VALUE: {stop2 << "None"; break; }
		case SPELL_EFFECT_CHARGE_DEST: {stop2 << "None"; break; }
		case SPELL_EFFECT_QUEST_START: {stop2 << "None"; break; }
		case SPELL_EFFECT_TRIGGER_SPELL_2: {stop2 << "None"; break; }
		case SPELL_EFFECT_SUMMON_RAF_FRIEND: {stop2 << "None"; break; }
		case SPELL_EFFECT_CREATE_TAMED_PET: {stop2 << "None"; break; }
		case SPELL_EFFECT_DISCOVER_TAXI: {stop2 << "None"; break; }
		case SPELL_EFFECT_TITAN_GRIP: {stop2 << "None"; break; }
		case SPELL_EFFECT_ENCHANT_ITEM_PRISMATIC: {stop2 << "None"; break; }
		case SPELL_EFFECT_CREATE_ITEM_2: {stop2 << "None"; break; }
		case SPELL_EFFECT_MILLING: {stop2 << "None"; break; }
		case SPELL_EFFECT_ALLOW_RENAME_PET: {stop2 << "None"; break; }
		case SPELL_EFFECT_FORCE_CAST_2: {stop2 << "None"; break; }
		case SPELL_EFFECT_TALENT_SPEC_COUNT: {stop2 << "None"; break; }
		case SPELL_EFFECT_TALENT_SPEC_SELECT: {stop2 << "None"; break; }
		case SPELL_EFFECT_163: {stop2 << "None"; break; }
		case SPELL_EFFECT_REMOVE_AURA: {stop2 << "None"; break; }
		}
		return stop2.str();
	}
	
	void First(Player* player, Item*item)  // main
	{
		QueryResult result = CharacterDatabase.PQuery("SELECT spellcast FROM start WHERE guid = %u", player->GetGUID());
		player->PlayerTalkClass->ClearMenus();
		if (player->HasAura(15007))
			player->RemoveAura(15007);
		char speed[256];
		char xp[256];
		char spellcastname[256], removespell[256];
		Field *fields = result->Fetch();
		uint32 n1 = fields[0].GetUInt32();
		if (player->GetSpeed(MOVE_RUN) > 1.0f)
			sprintf(speed, "Speed %f", player->GetSpeedRate(MOVE_RUN));
		else if (player->GetSpeed(MOVE_RUN) == 1.0f)
			sprintf(speed, "Modify Speed 1-50");
		sprintf(xp, "PlayerXP: %u\nNextLevelXP: %u\nNeededXP: %u", player->GetUInt32Value(PLAYER_XP), player->GetUInt32Value(PLAYER_NEXT_LEVEL_XP), (player->GetUInt32Value(PLAYER_NEXT_LEVEL_XP) - player->GetUInt32Value(PLAYER_XP)));
		if (n1 > 0)
		{
			sprintf(spellcastname, "Cast: %u [%s]", n1, RandomDBCNames(spell, n1).c_str());
			sprintf(removespell, "Remove Aura: %u[%s]", n1, RandomDBCNames(spell, n1).c_str());
		}
		else
		{
			sprintf(spellcastname, "Cast: None");
			sprintf(removespell, "Remove: None");
		}

		Unit* unit = player->GetSelectedUnit();
		AddGossipItemFor(player, 1, "Page->", GOSSIP_SENDER_MAIN, 2);
		AddGossipItemFor(player, 10, "Learn Spell", GOSSIP_SENDER_MAIN, 10, "", 0, true);
		AddGossipItemFor(player, 10, "Unlearn Spell", GOSSIP_SENDER_MAIN, 11, "", 0, true);
		AddGossipItemFor(player, 10, "Add Aura", GOSSIP_SENDER_MAIN, 12, "", 0, true);
		AddGossipItemFor(player, 10, "Add Item", GOSSIP_SENDER_MAIN, 16, "", 0, true);
		AddGossipItemFor(player, 10, "Add Item +10", GOSSIP_SENDER_MAIN, 17, "", 0, true);
		AddGossipItemFor(player, 10, "Set Level 1-255", GOSSIP_SENDER_MAIN, 13, "", 0, true);
		AddGossipItemFor(player, 10, "Temporery Summon Creature", GOSSIP_SENDER_MAIN, 14, "", 0, true);
		//AddGossipItemFor(player,10, "Item Destroy", GOSSIP_SENDER_MAIN, 18, "", 0, true);
		AddGossipItemFor(player, 10, "Play Sound", GOSSIP_SENDER_MAIN, 16, "", 0, true);
		if (player->GetDisplayId() == player->GetNativeDisplayId())
		{
			AddGossipItemFor(player, 10, "Morph", GOSSIP_SENDER_MAIN, 19, "", 0, true);
			if (unit)
				AddGossipItemFor(player, 10, "GetTargetDisplayId", GOSSIP_SENDER_MAIN, 62, "", 0, false);
		}
		else
		{
			AddGossipItemFor(player, 10, "Morph", GOSSIP_SENDER_MAIN, 19, "", 0, true);
			AddGossipItemFor(player, 10, "GetTargetDisplayId", GOSSIP_SENDER_MAIN, 62, "", 0, false);
			AddGossipItemFor(player, 10, "Demorph", GOSSIP_SENDER_MAIN, 25);
		}
		AddGossipItemFor(player, 10, speed, GOSSIP_SENDER_MAIN, 20, "", 0, true);
		AddGossipItemFor(player, 10, "All maps explore", GOSSIP_SENDER_MAIN, 21, "", 0, false);
		//AddGossipItemFor(player,10, "Remove Resurection sickness", GOSSIP_SENDER_MAIN, 30, "", 0, false);
		AddGossipItemFor(player, 10, "Skill Update", GOSSIP_SENDER_MAIN, 22, "", 0, true);
		AddGossipItemFor(player, 10, "Summontele", GOSSIP_SENDER_MAIN, 23, "", 0, true);
		AddGossipItemFor(player, 10, spellcastname, GOSSIP_SENDER_MAIN, 66);
		AddGossipItemFor(player, 10, "CastSpell", GOSSIP_SENDER_MAIN, 29, "", 0, true);
		AddGossipItemFor(player, 10, "Gold Mine", GOSSIP_SENDER_MAIN, 24, "", 0, true);
		AddGossipItemFor(player, 10, "Arena points", GOSSIP_SENDER_MAIN, 26, "", 0, true);
		AddGossipItemFor(player, 10, "Add Titles with Id", GOSSIP_SENDER_MAIN, 27, "", 0, true);
		AddGossipItemFor(player, 10, removespell, GOSSIP_SENDER_MAIN, 28);
		AddGossipItemFor(player, 10, xp, GOSSIP_SENDER_MAIN, 610, "", 0, true);
		SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, item->GetGUID());
	}
	void Second(Player* player, Item*item) // 
	{
		char mask[256],chphase[256];
		sprintf(mask, "CharMask: %u", player->getRaceMask());
		snprintf(chphase, 256, "PlayerPhase: %i", player->GetPhaseMask());
		Unit*unit = player->GetSession()->GetPlayer();
		AddGossipItemFor(player, 10, "<=Back", 1, 1);
		AddGossipItemFor(player, 10, "Next=>", 1, 3);
		AddGossipItemFor(player, 10, "Global Anonnce", 1, 32, "", 0, true);
		AddGossipItemFor(player, 10, "Annonce", 1, 31, "", 0, true);
		if(player->GetCommandStatus(CHEAT_GOD) == 1)
			AddGossipItemFor(player, 10, "God Cheat: " + green + "On|r", 1, 37, "", 0, false);
		else
			AddGossipItemFor(player, 10, "God Cheat: " + red + "Off|r", 1, 370, "", 0, false);
		if(player->GetCommandStatus(CHEAT_CASTTIME) == 1)
			AddGossipItemFor(player, 10, "Casttine Cheat: " + green + "On|r", 1, 38, "", 0, false);
		else
			AddGossipItemFor(player, 10, "Casttine Cheat: " + red + "Off|r", 1, 380, "", 0, false);
		if (player->GetCommandStatus(CHEAT_WATERWALK) == 1)
			AddGossipItemFor(player, 10, "Waterwalk Cheat:" + green + " On|r", 1, 40, "", 0, false);
		else
			AddGossipItemFor(player, 10, "Waterwalk Cheat:" + red + " Off|r", 1, 400, "", 0, false);
		if(player->GetCommandStatus(CHEAT_POWER) == 1)
			AddGossipItemFor(player, 10, "Power Cheat:" + green + " On|r", 1, 39, "", 0, false);
		else
			AddGossipItemFor(player, 10, "Power Cheat:" + red + " Off|r", 1, 390, "", 0, false); 
		if (player->GetCommandStatus(CHEAT_COOLDOWN) == 1)
			AddGossipItemFor(player, 10, "Cooldown Cheat:" + green + " On", 1, 41, "", 0, false);
		else
			AddGossipItemFor(player, 10, "Cooldown Cheat:" + red + " Off", 1, 410, "", 0, false);
		if(player->isTaxiCheater())
			AddGossipItemFor(player, 10, "Taxi Cheat:" + green + " On", 1, 420, "", 0, false);
		else
			AddGossipItemFor(player, 10, "Taxi Cheat:" + red + " Off", 1, 42, "", 0, false);
		if (player->CanFly())
			AddGossipItemFor(player, 10, "gmfly"+green+" on|r", 1, 960, "", 0, false);
		else
			AddGossipItemFor(player, 10, "gmfly"+red+" off|r", 1, 96, "", 0, false);
		if (!player->IsGameMaster())
			AddGossipItemFor(player, 10, "GM: " + red + "Off|r", 1, 64);
		else
			AddGossipItemFor(player, 10, "GM: " + green + "On|r", 1, 65);
		if(player->isGMChat())
			AddGossipItemFor(player, 10, "GMchat Badge:"+green+" On", 1, 43, "", 0, false);
		else
			AddGossipItemFor(player, 10, "GMchat Badge:"+red+" Off", 1, 430, "", 0, false);
		AddGossipItemFor(player, 10, "Honor Giver", 1, 45, "", 0, true);
		AddGossipItemFor(player, 10, mask, 1, 2);
		AddGossipItemFor(player, 10, chphase, 1, 201, "", 1*GOLD, true);
		AddGossipItemFor(player, 10, "Masslearn test", 1, 34);
		//AddGossipItemFor(player, 10, "Remove all auras", 1, 35);
		SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, item->GetGUID());
	}
	void Third(Player* player, Item*item)
	{
		Unit* unit = player->GetSelectedUnit();
		char model[256], extraid[256], unitentry[256];
		if (!unit)
		{
			unit = player;
			sprintf(model, "CreatureDisplayInfo: %u", unit->GetDisplayId());
			sprintf(extraid, "CeatureExtra");
			sprintf(unitentry, "CreatureEntry");
		}
		else if (unit)
		{
			sprintf(model, "CreatureDisplayInfo: %u", unit->GetDisplayId());
			CreatureDisplayInfoEntry const *info = sCreatureDisplayInfoStore.LookupEntry(unit->GetDisplayId());
			sprintf(extraid, "CeatureExtra: %u", info->ExtraId);
			sprintf(unitentry, "CreatureEntry: %u", unit->GetEntry());
		}
		else
		{
			sprintf(model, "CreatureDisplayInfo");
			sprintf(extraid, "CeatureExtra");
			sprintf(unitentry, "CreatureEntry");
		}
		AddGossipItemFor(player,10, "<=Back", 1, 2);
		AddGossipItemFor(player, 10, "Modify", 1, 11);
		AddGossipItemFor(player, 10, "Reload", 1, 4);
		AddGossipItemFor(player, 10, "Weather", 1, 6);
		AddGossipItemFor(player,10, "Bank", 1, 47);
		AddGossipItemFor(player,10, "Mailbox", 1, 48);
		AddGossipItemFor(player,10, "Stabel", 1, 49);
		AddGossipItemFor(player,10, "Tabar vend test", 1, 50);
		AddGossipItemFor(player,10, "UnitInfo", 1, 55);
		//AddGossipItemFor(player,10, "Tabar vend test", 1, 61);
		AddGossipItemFor(player,10, "ItemDisplayId", 1, 81, "", 0, true);
		AddGossipItemFor(player, 10, "ItemTemaplateInfo", 1, 82, "", 0, true);
		AddGossipItemFor(player, 10, "Npc move", 1, 83, "", 0, true);
		AddGossipItemFor(player, 10, unitentry, 1, 77, "", 0, true);
		AddGossipItemFor(player,10, model, 1, 73, "", 0, true);
		AddGossipItemFor(player,10, extraid, 1, 76, "", 0, true);
		AddGossipItemFor(player,10, "GameObjectInfo", 1, 75, "", 0, true);
		AddGossipItemFor(player,10, "GobNear", 1, 63);
		AddGossipItemFor(player,10, "SpellInfo", 1, 74, "", 0, true);
		AddGossipItemFor(player,10, "AddItemset", 1, 36, "", 0, true);
		AddGossipItemFor(player,10, "lookup item", 1, 46, "", 0, true);
		AddGossipItemFor(player,10, "lookup quest", 1, 47, "", 0, true);
		AddGossipItemFor(player,10, "lookup spell", 1, 48, "", 0, true);
		AddGossipItemFor(player, 10, "lookup title", 1, 49, "", 0, true);
		AddGossipItemFor(player, 10, "learn mounts", 1, 69, "", 0, false);
		SendGossipMenuFor(player,DEFAULT_GOSSIP_MESSAGE, item->GetGUID());
	}
	void Fourth(Player* player, Item*item)
	{
		AddGossipItemFor(player,0, "<=Back", 1, 3);
		AddGossipItemFor(player, 1, " " + purple + "Reload Point Of Interest|r", 2, 51, "do you want to reload this template", 0, false);
		AddGossipItemFor(player, 1, " " + purple + "Reload Gossip Menu Option|r", 2, 54, "do you want to reload this template", 0, false);
		AddGossipItemFor(player, 1, " " + blue + "Reload npc_vendor|r", 2, 90, "do you want to reload this template", 0, false);
		AddGossipItemFor(player, 1, " " + red + "Reload npc_trainer|r", 2, 91, "do you want to reload this template", 0, false);
		AddGossipItemFor(player,1, "|cff808080Reload Item Template|r", 2, 52, "do you want to reload this template", 0, false);
		AddGossipItemFor(player,1, "|cffFF0000Reload Creature Templates|r", 2, 61, "do you want to reload this template", 0, false);
		AddGossipItemFor(player,1, "|cff808000Reload Gameobjects_Template|r", 2, 53, "do you want to reload this template", 0, false);
		AddGossipItemFor(player,1, "|cff808000Reload Creature Template|r", 2, 60, "do you want to reload this template", 0, true);
		AddGossipItemFor(player, 10, "Reload Weather (Test)", 1, 80, "", 0, false);
		SendGossipMenuFor(player,DEFAULT_GOSSIP_MESSAGE, item->GetGUID());
	}
	void Fifth(Player* player, Item*item)
	{
		QueryResult result = CharacterDatabase.Query("SELECT guid, gold FROM characters_gold_bank ORDER BY gold DESC LIMIT 10");

		if (!result)
			return;
		Field*fields = NULL;
		AddGossipItemFor(player, 10, "Goldbank top10", 1, 0);
		do
		{
			fields = result->Fetch();
			uint32 guid, gold;
			guid = fields[0].GetUInt32();
			gold = (fields[1].GetUInt32()*GOLD);
			char tar[256];
			snprintf(tar, 256, "Char Guid: %u GoldBank: %s \n", guid, Money(gold).c_str());
			AddGossipItemFor(player, 10, tar, 1, 3);
		} while (result->NextRow());

		SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, item->GetGUID());
	}
	void Sixth(Player* player, Item*item)
	{
		Weather* weather = WeatherMgr::FindWeather(player->GetZoneId());
		if (!weather)
		{
			AddGossipItemFor(player, 10, "WeatherInfo: None", 1, 6);
			AddGossipItemFor(player, 10, "Add ZoneWeather", 1, 80, "", 0, true);
			AddGossipItemFor(player, 10, "Back", 1, 3);
		}
		else
		{
			char zone[256];
			string zonename = "None";
			uint32 zoneid = player->GetZoneId();
			if (AreaTableEntry const * das = sAreaTableStore.LookupEntry(zoneid))
			{
				zonename = das->area_name[player->GetSession()->GetSessionDbcLocale()];
			}
			sprintf(zone, "ZoneId: %u[%s]", zoneid, zonename.c_str());
			AddGossipItemFor(player, 10, zone, 1, 6);
			AddGossipItemFor(player, 10, "Fine", 1, 68);
			AddGossipItemFor(player, 10, "Mist", 1, 10);
			AddGossipItemFor(player, 10, "Rain", 1, 7);
			AddGossipItemFor(player, 10, "Snow", 1, 8);
			AddGossipItemFor(player, 10, "Sand Storm", 1, 9);
		}
		SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, item->GetGUID());
	}
	void Seven(Player* player, Item* item, const char *code) // svobodno za izpolzwane
	{
		
	}
	void Lookup(Player* player, Item* item)
	{
		QueryResult result = CharacterDatabase.PQuery("SELECT item FROM start where guid = %u", player->GetGUID());
		Field *field = result->Fetch();
		uint32 entry = field[0].GetUInt32();
		ItemTemplate const* iteminfo = sObjectMgr->GetItemTemplate(entry);
		string namePart = iteminfo->Name1;

	}
	void CreatureDi(Player* player, Item* item, const char* code)
	{
		uint32 entry = atol(code);
		CreatureDisplayInfoEntry const* Info = sCreatureDisplayInfoStore.LookupEntry(entry);
		uint32 id = Info->Displayid;
		uint32 model = Info->ModelId;
		string modelname = CreatureModelData(model);
		uint32 sound = 0;//Info->m_soundID;
		uint32 ExtraId = Info->ExtraId;
		float scale = Info->scale;
		
		int i = 0, i1 = 1, i2 = 2;
		//int32 size = Info->m_sizeClass;
		//int32 blood = Info->m_bloodID;
		//uint32 npcsound = Info->m_NPCSoundID;
		//uint32 particleColor = Info->m_particleColorID;
		//uint32 Geoset = Info->m_creatureGeosetData;
		//uint32 EffectPackage = Info->m_objectEffectPackageID;
		char tervel[1025];
		char modeln[256];
		string tex1 = "None";
		string extraid = CreatureDIE(ExtraId);
		sprintf(modeln, "%s", modelname.c_str());
		snprintf(tervel, 1025, "DisplayId: %u\nModelId: %u\nSound: %u\nExtraId: %u[%s]\nScale: %f\n[%s]", id, model, sound, ExtraId,extraid.c_str(), scale, tex1.c_str());
		//snprintf(INFO, 1025, "Entry: %u\nModelId: %u\nSound: %u\nExtraId: %u\nScale: %f\nCreatureAlpfaId: %u\ntex1: %s\ntex2: %s\ntex3: %s\ntex4: %s\nsizeClass: %u\nbloodID: %u\nNPCSoundID: %u\nparticleColorID: %u\ncreatureGeosetData: %u\nEffectPackageID: %u", id, model, sound, ExtraId, scale, creaturealfaid, tex0.c_str(), tex1.c_str(), tex2.c_str(), tex4.c_str(), size, blood, npcsound, particleColor, Geoset, EffectPackage);
		AddGossipItemFor(player,10, tervel, 1, 73, "", 0, true);
		AddGossipItemFor(player,10, modeln, 1, 3);
		AddGossipItemFor(player, 10, "CeatureExtra", 1, 76, "", 0, true);
		//AddGossipItemFor(player,10, "TEST2", 1, 3);
		AddGossipItemFor(player,10, "Back", 1, 3);
		ChatHandler(player->GetSession()).PSendSysMessage(modelname.c_str());
		SendGossipMenuFor(player,DEFAULT_GOSSIP_MESSAGE, item->GetGUID());
	}
	void SpellInfoadmin(Player* player, Item* item, const char* code)
	{

		uint32 spell, spellentry, Effect, Effect1, Effect2, ApplyAuraName, ApplyAuraName1, ApplyAuraName2, MiscValue, MiscValue1, MiscValue2, MiscValueB, MiscValueB1, MiscValueB2, display1, display2, TriggerSpell, TriggerSpell1, TriggerSpell2, SpellIconID;
		int32 BasePoints, BasePoints1, BasePoints2, EffectDieSides, EffectDieSides1, EffectDieSides2;
		float RealPointsPerLevel, RealPointsPerLevel1, RealPointsPerLevel2;
		string namespell, spelldisc = "none" , spelltooltip="none", Effect0name, Effect1name, Effect2name, name, name1, name2;
		char fax[1025];
		int i = 0, i1 = 1, i2 = 2, i3 = 3, i4 = 4;
		spell = atol(code);
		SpellEntry const *spelli = sSpellStore.LookupEntry(spell);
		spellentry = spelli->Id;
		namespell = spelli->SpellName[i];
		//spelldisc = spelli->Description[i];
		//spelltooltip = spelli->ToolTip[i];
		Effect = spelli->Effect[i];
		Effect1 = spelli->Effect[i1];
		Effect2 = spelli->Effect[i2];
		Effect0name = "None";
		Effect1name = "None";
		Effect2name = "None";
		if (SpellEntry const *etr = sSpellStore.LookupEntry(spell))
		{
		    Effect0name = GetSpellEffect(Effect);
			Effect1name = GetSpellEffect(Effect1);
			Effect2name = GetSpellEffect(Effect2);
		}
		RealPointsPerLevel = spelli->EffectRealPointsPerLevel[i];
		RealPointsPerLevel1 = spelli->EffectRealPointsPerLevel[i1];
		RealPointsPerLevel2 = spelli->EffectRealPointsPerLevel[i2];
		BasePoints = spelli->EffectBasePoints[i];
		BasePoints1 = spelli->EffectBasePoints[i1];
		BasePoints2 = spelli->EffectBasePoints[i2];
	    ApplyAuraName = spelli->EffectApplyAuraName[i];
		ApplyAuraName1 = spelli->EffectApplyAuraName[i1];
		ApplyAuraName2 = spelli->EffectApplyAuraName[i2];
		MiscValue = spelli->EffectMiscValue[i];
		MiscValue1 = spelli->EffectMiscValue[i1];
	    MiscValue2 = spelli->EffectMiscValue[i2];
		MiscValueB = spelli->EffectMiscValueB[i];
	    MiscValueB1 = spelli->EffectMiscValueB[i1];
		MiscValueB2 = spelli->EffectMiscValueB[i2];
		display1 = spelli->SpellVisual[i];
		display2 = spelli->SpellVisual[i1];
		name = TestAura(spelli->Effect[i], ApplyAuraName);
	    name1 = TestAura(spelli->Effect[i1], ApplyAuraName1);
		name2 = TestAura(spelli->Effect[i2], ApplyAuraName2);
		EffectDieSides = spelli->EffectDieSides[i];
		EffectDieSides1 = spelli->EffectDieSides[i1];
		EffectDieSides2 = spelli->EffectDieSides[i2];
		TriggerSpell = spelli->EffectTriggerSpell[i];
		TriggerSpell1 = spelli->EffectTriggerSpell[i1];
		TriggerSpell2 = spelli->EffectTriggerSpell[i2];
		SpellIconID = spelli->SpellIconID;
		//snprintf(spellmenu, 1025, "SpellId: %u\nSpellName: %s\nDesc: %s\nTooltip: %s\nEffect: %u[%s]\nEffect1: %u[%s]\nEffect2: %u[%s]\nRealPPLevel: %f\nRealPPLevel1: %f\nRealPPLevel2: %f\nBasePoints: %i\nBasePoints1: %i\nBasePoints2: %i\nApplyAura: %u[%s]\nApplyAura1: %u[%s]\nApplyAura2: %u[%s]\nSpellVisual: %u\nSpellVisual2: %u\nDieside: %i\nDieside1: %i\nDieside2: %i\nMiscValueA: %u\nMiscValueA1: %u\nMiscValueA2: %u\nTriggerSpell: %u\nTriggerSpell1: %u\nTriggerSpell2: %u\nSpellIconID: %u", spellentry, namespell.c_str(), spelldisc.c_str(), spelltooltip.c_str(), Effect, Effect0name.c_str(), Effect1, Effect1name.c_str(), Effect2, Effect2name.c_str(), RealPointsPerLevel, RealPointsPerLevel1, RealPointsPerLevel2, BasePoints, BasePoints1, BasePoints2, ApplyAuraName, name.c_str(), ApplyAuraName1, name1.c_str(), ApplyAuraName2, name2.c_str(), display1, display2, EffectDieSides, EffectDieSides1, EffectDieSides2, MiscValue, MiscValue1, MiscValue2, TriggerSpell, TriggerSpell1, TriggerSpell2, SpellIconID);
		snprintf(fax, 1025, "SpellId: %u\nSpellName: %s\nDesc: %s\nTooltip: %s\nEffect: %u[%s]\nRealPPLevel: %f\nBasePoints: %i\nApplyAura: %u[%s]\nDieside: %i\nTriggerSpell: %u\nMiscValueA: %u\nMiscValueB: %u\nEffect1: %u[%s]\nRealPPLevel1: %f\nBasePoints1: %i\nApplyAura1: %u[%s]\nDieside1: %i\nTriggerSpell1: %u\nMiscValueA1: %u\nMiscValueB1: %u\nEffect2: %u[%s]\nRealPPLevel2: %f\nBasePoints2: %i\nApplyAura2: %u[%s]\nDieside2: %i\nTriggerSpell2: %u\nMiscValueA2: %u\nMiscValueB2: %u\nSpellVisual: %u\nSpellVisual1: %u\nSpellIcon: %u", spellentry, namespell.c_str(), spelldisc.c_str(), spelltooltip.c_str(), Effect, Effect0name.c_str(), RealPointsPerLevel, BasePoints, ApplyAuraName, name.c_str(), EffectDieSides, TriggerSpell, MiscValue, MiscValueB, Effect1, Effect1name.c_str(), RealPointsPerLevel1, BasePoints1, ApplyAuraName1, name1.c_str(), EffectDieSides1, TriggerSpell1, MiscValue1, MiscValueB1, Effect2, Effect2name.c_str(), RealPointsPerLevel2, BasePoints2, ApplyAuraName2, name2.c_str(), EffectDieSides2, TriggerSpell2, MiscValue2, MiscValueB2, display1, display2, SpellIconID);
		//AddGossipItemFor(player,10, spellmenu, 1, 74, "", 0, true);
		AddGossipItemFor(player,10, fax, 1, 74, "", 0, true);
		AddGossipItemFor(player, 10, "CreatureTemp", 1, 77, "", 0, true);
		AddGossipItemFor(player,10, "Back", 1, 3);
		SendGossipMenuFor(player,DEFAULT_GOSSIP_MESSAGE, item->GetGUID());
	}
	void GObjInfo(Player* player, Item* item, const char *code)
	{
		uint32 entry = atol(code);
		GameObjectTemplate const* Info = sObjectMgr->GetGameObjectTemplate(entry);
		uint32 entryid, modelid, objtype;
		string name2, icon, castbar, unknown, nametype, ModelName;
		float size;
		entryid = Info->entry;
		modelid = Info->displayId;
		objtype = Info->type;
		name2 = Info->name;
		icon = Info->IconName;
		castbar = Info->castBarCaption;
		unknown = Info->unk1;
		size = Info->size;
		nametype = GameObjType(objtype);
		ModelName = "None";
		if (GameObjectDisplayInfoEntry const* name = sGameObjectDisplayInfoStore.LookupEntry(modelid))
		{
			ModelName = name->filename;
		}
		char ginfo[1025];
		char name[256];
		char rens[256];
		snprintf(ginfo, 1025, "Entry: %u\nType: %u[%s]\nDisplayId: %u\nName: %s\nIcon: %s\nCastBar: %s\nUnk1: %s\nSize: %f", entryid, objtype, nametype.c_str(), modelid, name2.c_str(), icon.c_str(), castbar.c_str(), unknown.c_str(), size);
		sprintf(name, "%s", ModelName.c_str());
		sprintf(rens, "%s", Ras(entryid).c_str());
		AddGossipItemFor(player,10, ginfo, 1, 75, "", 0, true);
		AddGossipItemFor(player,10, name, 1, 3);
		AddGossipItemFor(player,10, rens, 1, 3);
		ChatHandler(player->GetSession()).PSendSysMessage(ModelName.c_str());
		AddGossipItemFor(player,10, "Back", 1, 3);
		SendGossipMenuFor(player,DEFAULT_GOSSIP_MESSAGE, item->GetGUID());
	}
	
	void CreatureTempEntry(Player * player, Item* item, const char* code)
	{
		uint32 entry = atol(code);
		char send[1025];
		CreatureTemplate const *info = sObjectMgr->GetCreatureTemplate(entry);
		uint32 i = info->Entry, i1 = info->expansion, i2 = info->Modelid1, i3 = info->Modelid2, i4 = info->Modelid3, i5 = info->Modelid4, i6 = info->minlevel, i7 = info->maxlevel;
		string s = info->Name, s1= info->Title, s2= info->IconName, s3 = sObjectMgr->GetScriptName(info->ScriptID);
		snprintf(send, 1025, "Entry: %u\nExp: %u\nModel1: %u\nModel2: %u\nModel3: %u\nModel4: %u\nName: %s\nSubName: %s\nIconname: %s\nMinlvl: %u\nMaxlvl: %u\nScriptName: %s",i, i1,i2,i3,i4,i5,s.c_str(), s1.c_str(),s2.c_str(),i6, i7,s3.c_str());
		AddGossipItemFor(player, 10, send, 0, 3);
		AddGossipItemFor(player, 10, "Creaturemodel", 1, 73, "", 0, true);
		AddGossipItemFor(player, 10, "Morph", GOSSIP_SENDER_MAIN, 19, "", 0, true);
		AddGossipItemFor(player, 10, "Back <=", 0, 3);
		SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, item->GetGUID());
	}
	void ModifyMenuE(Player*player, Item*item)
	{
		AddGossipItemFor(player, 10, "Back <=", 1, 3);
		AddGossipItemFor(player, 10, "HP Modify", 1, 79, "", 0, true);
		AddGossipItemFor(player, 10, "TESTAUCTION", 1, 67);
		AddGossipItemFor(player, 10, "TalentModify", 1, 78, "", 0, true);
		AddGossipItemFor(player, 10, "SerRestart", 1, 200, "", 0, true);
		AddGossipItemFor(player, 10, "TESTER", 1, 97);
		SendGossipMenuFor(player, 100, item->GetGUID());
	}
	bool OnUse(Player* player, Item* item, SpellCastTargets const& targets) override
	{
		ClearGossipMenuFor(player);
		First(player, item);
		return true;
	}
	void OnGossipSelect(Player* player, Item* item, uint32 sender, uint32 action)
	{
		ClearGossipMenuFor(player);
		switch (action)
		{
		case 1:
			First(player, item);
			break;
		case 2:
			Second(player, item);
			break;
		case 3:
			Third(player, item);
			break;
		case 4:
			Fourth(player, item);
			break;
		case 5:
			Fifth(player, item);
			break;
		case 6:
			Sixth(player, item);
			break;
		case 7:
		{
			uint32 type = 1;
			float grade = 1;
			uint32 zone = player->GetZoneId();
			Weather *weather = WeatherMgr::FindWeather(zone);
			weather->SetWeather(WeatherType(type), grade);
			player->GetSession()->SendNotification("Weather Changed to Rain Enjoy");


			Third(player, item);
			break;
		}
		case 8:
		{
			uint32 type = 2;
			float grade = 1;
			uint32 zone = player->GetZoneId();
			Weather *weather = WeatherMgr::FindWeather(zone);
			weather->SetWeather(WeatherType(type), grade);
			player->GetSession()->SendNotification("Weather Changed to Snow Enjoy");
			Third(player, item);
			break;
		}
		case 9:
		{
			uint32 type = 3;
			float grade = 1;
			uint32 zone = player->GetZoneId();
			Weather *weather = WeatherMgr::FindWeather(zone);
			weather->SetWeather(WeatherType(type), grade);
			player->GetSession()->SendNotification("Weather Changed to Sand Storm Enjoy");
			Third(player, item);
			break;
		}
		case 10:
		{
			uint32 type = 0;
			float grade = 1;
			uint32 zone = player->GetZoneId();
			Weather *weather = WeatherMgr::FindWeather(zone);
			player->GetSession()->SendNotification("Weather Changed to Mist Enjoy");
			weather->SetWeather(WeatherType(type), grade);
			Third(player, item);
			break;
		}
		case 11:
		{
			ModifyMenuE(player, item);
			break;
		}
		case 25:
		{
			player->DeMorph();
			First(player, item);
			break;
		}
		case 28:
		{
			QueryResult result = CharacterDatabase.PQuery("SELECT spellcast FROM start WHERE guid = %u", player->GetGUID());
			Field *f = result->Fetch();
			uint32 removeaura = f[0].GetUInt32();
			player->RemoveAura(removeaura);
			First(player, item);
			break;
		}
		case 30:
		{
			Player* target = player->GetSelectedPlayer();
			if (!target)
				target = player;
			if (target->HasAura(15007))
			{
				target->RemoveAura(15007);
				First(player, item);
			}
			else
				player->GetSession()->SendNotification("do noting");
			First(player, item);
			break;
		}
		case 33:
		{
			const char* enabled = "enabled";
			const char* disabled = "disabled";

			ChatHandler(player->GetSession()).SendSysMessage(LANG_COMMAND_CHEAT_STATUS);
			ChatHandler(player->GetSession()).PSendSysMessage(LANG_COMMAND_CHEAT_GOD, player->GetCommandStatus(CHEAT_GOD) ? enabled : disabled);
			ChatHandler(player->GetSession()).PSendSysMessage(LANG_COMMAND_CHEAT_CD, player->GetCommandStatus(CHEAT_COOLDOWN) ? enabled : disabled);
			ChatHandler(player->GetSession()).PSendSysMessage(LANG_COMMAND_CHEAT_CT, player->GetCommandStatus(CHEAT_CASTTIME) ? enabled : disabled);
			ChatHandler(player->GetSession()).PSendSysMessage(LANG_COMMAND_CHEAT_POWER, player->GetCommandStatus(CHEAT_POWER) ? enabled : disabled);
			ChatHandler(player->GetSession()).PSendSysMessage(LANG_COMMAND_CHEAT_WW, player->GetCommandStatus(CHEAT_WATERWALK) ? enabled : disabled);
			First(player, item);
			break;
		}
		case 34:
		{
			player->LearnSpell(265, false); //Area Death (TEST,true)
			player->LearnSpell(39258, false); //Automation Root Spell
			player->LearnSpell(35182, false); //Banish
			player->LearnSpell(25565, false); //ClearAll
			player->LearnSpell(26368, false); //ClearAllo
			player->LearnSpell(5, false); //Death Touch
			player->LearnSpell(36356, false); //Internal Knowledge Grandmaster 
			player->LearnSpell(6560, false); //LeCraft Test Spell Rank 1 
			player->LearnSpell(35912, false); //Master Buff (Magic,true)
			player->LearnSpell(35874, false); //Master Buff (Melee,true)
			player->LearnSpell(38734, false); //Master Ranged Buff
			player->LearnSpell(38505, false); //Shackle
			player->LearnSpell(23789, false); //Stoneclaw Totem TEST
			player->LearnSpell(18209, false); //Test Grow
			player->LearnSpell(18210, false); //Test Shrink
			player->LearnSpell(1908, false); //Uber Heal Over Time
			player->LearnSpell(35886, false); //Windfury Weapon
			player->LearnSpell(11, false); //Frostbolt of Ages
			player->LearnSpell(10032, false); //Uber Stealth
			player->LearnSpell(32453, false); //Mana Potion
			player->LearnSpell(23452, false); //Invisibility
			player->LearnSpell(33686, false); //Shockwave
			player->LearnSpell(1609, false); //Ashbringer Buzzsaw
			player->LearnSpell(31984, false); //Finger Of Death
			player->LearnSpell(6963, false); //Shadow Bolt Vortex
			player->LearnSpell(2583, false); //Debug Spell Reflection
			player->LearnSpell(36841, false); //Sonic Boom
			player->LearnSpell(40946, false); //Rain of Chaos
			player->LearnSpell(39029, false); //Virulent Poison
			player->LearnSpell(34821, false); //Arcane Flurry
			player->LearnSpell(40251, false); //Shadow Hand
			player->LearnSpell(29973, false); //Arcane Explosion
			player->LearnSpell(24910, false); //Curruption of the Earth
			player->LearnSpell(2602, false); //Fire Shield IV
			player->LearnSpell(38917, false); //Hell Rain
			player->LearnSpell(41276, false); //Meteor
			player->LearnSpell(41431, false); //Rune Shield
			player->LearnSpell(25840, false); //Full Heal
			player->LearnSpell(25947, false); //Infatuation
			player->LearnSpell(26170, false); //Oracular Heal
			player->LearnSpell(26339, false); //Saurfang's Rage
			player->LearnSpell(26540, false); //Starfall
			player->LearnSpell(1302, false); //Damage Immunity Test
			player->LearnSpell(33329, false); //Murmur's Wrath
			player->LearnSpell(40251, false); //Shadow of Death
			Second(player, item);
			break;

		}
		case 35:
		{
			player->RemoveAllAuras();
			Second(player, item);
			break;
		}
		case 47:
		{
			player->GetSession()->SendShowBank(player->GetGUID());
			break;
		}
		case 48:
		{
			player->GetSession()->SendShowMailBox(player->GetGUID());
			break;
		}
		case 49:
		{
			player->GetSession()->SendStablePet(player->GetGUID());
			break;
		}
		case 50:
		{
			player->GetSession()->SendTabardVendorActivate(player->GetGUID());
			break;
		}
		case 51:
		{
			TC_LOG_INFO("misc", "Re-Loading PointOfInterest...");
			sObjectMgr->LoadPointsOfInterest();
			ChatHandler(player->GetSession()).SendGlobalGMSysMessage("DB table `PointOfInterest` reloaded.");
			Third(player, item);
			break;
		}
		case 52:
		{

			TC_LOG_INFO("misc", "Re-Loading Item_Template...");
			sObjectMgr->LoadItemTemplates();
			ChatHandler(player->GetSession()).SendGlobalGMSysMessage("DB table `Item_template` reloaded.");
			Third(player, item);
			break;
		}
		case 53:
		{
			TC_LOG_INFO("misc", "Re-Loading GameObjects...");
			sObjectMgr->LoadGameObjectTemplate();
			ChatHandler(player->GetSession()).SendGlobalGMSysMessage("DB table `GameObjectTemplate` reloaded.");
			Third(player, item);
			break;
		}
		case 54:
		{
			TC_LOG_INFO("misc", "Re-Loading gossip_menu_option...");
			sObjectMgr->LoadGossipMenuItems();
			ChatHandler(player->GetSession()).SendGlobalGMSysMessage("DB table `Gossip_menu_option` reloaded.");
			Third(player, item);
			break;
		}
		case 80:
		{
			TC_LOG_INFO("misc", "Re-Loading game_weather");
			WeatherMgr::LoadWeatherData();
			ChatHandler(player->GetSession()).SendGlobalGMSysMessage("DB table `game_weather` reloaded");
			Third(player, item);
			break;
		}
		case 55:
		{
			Unit* target = player->GetSelectedUnit();

			if (!target)
			{
				ChatHandler(player->GetSession()).SendSysMessage(LANG_SELECT_CREATURE);
				ChatHandler(player->GetSession()).SetSentErrorMessage(true);
				Third(player, item);
				return;
			}

			uint32 faction = target->GetFaction();
			uint32 npcflags = target->GetUInt32Value(UNIT_NPC_FLAGS);
			uint32 displayid = target->GetDisplayId();
			uint32 nativeid = target->GetNativeDisplayId();

			uint32 Entry = target->GetEntry();
			uint32 Test = 0;

			CreatureTemplate const* cInfo = sObjectMgr->GetCreatureTemplate(Entry);
			uint32 mechanicImmuneMask = cInfo->MechanicImmuneMask;
			ChatHandler(player->GetSession()).PSendSysMessage(LANG_NPCINFO_CHAR, Test, target->GetGUID().GetCounter(), faction, npcflags, Entry, displayid, nativeid);


			ChatHandler(player->GetSession()).PSendSysMessage(LANG_NPCINFO_LEVEL, target->getLevel());
			ChatHandler(player->GetSession()).PSendSysMessage(LANG_NPCINFO_HEALTH, target->GetCreateHealth(), target->GetMaxHealth(), target->GetHealth());
			ChatHandler(player->GetSession()).PSendSysMessage(LANG_NPCINFO_UNIT_FIELD_FLAGS, target->GetUInt32Value(UNIT_FIELD_FLAGS));
			ChatHandler(player->GetSession()).PSendSysMessage(LANG_NPCINFO_FLAGS, target->GetUInt32Value(UNIT_FIELD_FLAGS_2), target->GetUInt32Value(UNIT_DYNAMIC_FLAGS), target->GetFaction());
			ChatHandler(player->GetSession()).PSendSysMessage(LANG_NPCINFO_DUNGEON_ID, target->GetInstanceId());
			ChatHandler(player->GetSession()).PSendSysMessage(LANG_NPCINFO_PHASEMASK, target->GetPhaseMask());
			ChatHandler(player->GetSession()).PSendSysMessage(LANG_NPCINFO_ARMOR, target->GetArmor());
			ChatHandler(player->GetSession()).PSendSysMessage(LANG_NPCINFO_POSITION, target->GetPositionX(), target->GetPositionY(), target->GetPositionZ());
			ChatHandler(player->GetSession()).PSendSysMessage(LANG_NPCINFO_INHABIT_TYPE, cInfo->InhabitType);
			ChatHandler(player->GetSession()).PSendSysMessage(LANG_NPCINFO_UNIT_FIELD_FLAGS, target->GetUInt32Value(UNIT_FIELD_FLAGS));
			for (uint8 i = 0; i < MAX_UNIT_FLAGS; ++i)
				if (target->GetUInt32Value(UNIT_FIELD_FLAGS) & unitFlags[i].Value)
					ChatHandler(player->GetSession()).PSendSysMessage("%s (0x%X)", unitFlags[i].Name, unitFlags[i].Value);
			for (uint8 i = 0; i < NPCFLAG_COUNT; i++)
				if (npcflags & npcFlagTexts[i].Value)
					ChatHandler(player->GetSession()).PSendSysMessage(npcFlagTexts[i].Name, npcFlagTexts[i].Value);
			ChatHandler(player->GetSession()).PSendSysMessage(LANG_NPCINFO_MECHANIC_IMMUNE, mechanicImmuneMask);
			for (uint8 i = 1; i < MAX_MECHANIC; ++i)
				if (mechanicImmuneMask & (1 << (mechanicImmunes[i].Value - 1)))
					ChatHandler(player->GetSession()).PSendSysMessage("%s (0x%X)", mechanicImmunes[i].Name, mechanicImmunes[i].Value);
			Third(player, item);
			return;
			break;
		}
		case 62:
		{
			Unit *unit = player->GetSelectedUnit();
			if (!unit)
				First(player, item);
			if (unit)
			{
				uint32 display = unit->GetDisplayId();
				player->SetDisplayId(display);
				First(player, item);
			}
			break;
		}
		case 63:
		{
			float distance = 10.0f;
			uint32 count = 0;

			PreparedStatement* stmt = WorldDatabase.GetPreparedStatement(WORLD_SEL_GAMEOBJECT_NEAREST);
			stmt->setFloat(0, player->GetPositionX());
			stmt->setFloat(1, player->GetPositionY());
			stmt->setFloat(2, player->GetPositionZ());
			stmt->setUInt32(3, player->GetMapId());
			stmt->setFloat(4, player->GetPositionX());
			stmt->setFloat(5, player->GetPositionY());
			stmt->setFloat(6, player->GetPositionZ());
			stmt->setFloat(7, distance * distance);
			PreparedQueryResult result = WorldDatabase.Query(stmt);

			if (result)
			{
				do
				{
					Field* fields = result->Fetch();
					ObjectGuid::LowType guid = fields[0].GetUInt32();
					uint32 entry = fields[1].GetUInt32();
					float x = fields[2].GetFloat();
					float y = fields[3].GetFloat();
					float z = fields[4].GetFloat();
					uint16 mapId = fields[5].GetUInt16();

					GameObjectTemplate const* gameObjectInfo = sObjectMgr->GetGameObjectTemplate(entry);

					if (!gameObjectInfo)
						continue;
					ostringstream gameobjectlist;
					gameobjectlist << "[Guid: " << guid << "][Entry: " << entry << "][Guid: " << guid << "][Name: " << gameObjectInfo->name.c_str() << "][X: " << x << "][Y: " << y << "][Z: " << z << "][MapId: " << mapId<<"]";
					ChatHandler(player->GetSession()).PSendSysMessage("%s",gameobjectlist.str());
					++count;
				} while (result->NextRow());
			}

			ChatHandler(player->GetSession()).PSendSysMessage(LANG_COMMAND_NEAROBJMESSAGE, distance, count);
			Third(player, item);
			break;
		}
		case 64:
		{
			player->SetGameMaster(true);
			player->UpdateTriggerVisibility();
			player->GetSession()->SendNotification(LANG_GM_ON);
#ifdef _DEBUG_VMAPS
			VMAP::IVMapManager* vMapManager = VMAP::VMapFactory::createOrGetVMapManager();
			vMapManager->processCommand("startlog");
#endif
			Second(player, item);
			break;
		}
		case 65:
		{
			player->SetGameMaster(false);
			player->UpdateTriggerVisibility();
			player->GetSession()->SendNotification(LANG_GM_OFF);
#ifdef _DEBUG_VMAPS
			VMAP::IVMapManager* vMapManager = VMAP::VMapFactory::createOrGetVMapManager();
			vMapManager->processCommand("startlog");
#endif
			Second(player, item);
			break;
		}
		case 66:
		{
			QueryResult result = CharacterDatabase.PQuery("SELECT spellcast FROM start WHERE guid = %u", player->GetGUID());
			Field*fields = result->Fetch();
			uint32 spellcast = fields[0].GetUInt32();
			player->CastSpell(player, spellcast);
			First(player, item);
			break;
		}
		case 67:
		{

			player->GetSession()->SendAuctionHello(player->GetGUID(), ChatHandler(player->GetSession()).getSelectedCreature());
			break;


		}
		case 68:
		{

			uint32 type = 1;
			float grade = 0;
			uint32 zone = player->GetZoneId();
			Weather *weather = WeatherMgr::FindWeather(zone);
			weather->SetWeather(WeatherType(type), grade);
			player->GetSession()->SendNotification("Weather Changed to Fine Enjoy");
			Third(player, item);
			break;
		}
		case 69:
		{
			player->LearnSpell(48778, false);     //Acherus Deathcharger
			player->LearnSpell(60025, false);     //Albino Drake
			player->LearnSpell(127180, false);     //Albino Riding Crane
			player->LearnSpell(98204, false);     //Amani Battle Bear
			player->LearnSpell(96503, false);     //Amani Dragonhawk
			player->LearnSpell(43688, false);     //Amani War Bear
			player->LearnSpell(138424, false);     //Amber Primordial Direhorn
			player->LearnSpell(123886, false);     //Amber Scorpion
			player->LearnSpell(16056, false);     //Ancient Frostsaber
			player->LearnSpell(171618, false);     //Ancient Leatherhide
			player->LearnSpell(16081, false);     //Arctic Wolf
			player->LearnSpell(66906, false);     //Argent Charger
			player->LearnSpell(63844, false);     //Argent Hippogryph
			player->LearnSpell(66907, false);     //Argent Warhorse
			player->LearnSpell(67466, false);     //Argent Warhorse
			player->LearnSpell(139595, false);     //Armored Bloodwing
			player->LearnSpell(142478, false);     //Armored Blue Dragonhawk
			player->LearnSpell(61230, false);     //Armored Blue Wind Rider
			player->LearnSpell(60114, false);     //Armored Brown Bear
			player->LearnSpell(60116, false);     //Armored Brown Bear
			player->LearnSpell(171629, false);     //Armored Frostboar
			player->LearnSpell(171838, false);     //Armored Frostwolf
			player->LearnSpell(171626, false);     //Armored Irontusk
			player->LearnSpell(171630, false);     //Armored Razorback
			player->LearnSpell(96491, false);     //Armored Razzashi Raptor
			player->LearnSpell(142266, false);     //Armored Red Dragonhawk
			player->LearnSpell(136400, false);     //Armored Skyscreamer
			player->LearnSpell(61229, false);     //Armored Snowy Gryphon
			player->LearnSpell(132117, false);     //Ashen Pandaren Phoenix
			player->LearnSpell(40192, false);     //Ashes of Al'ar
			player->LearnSpell(148428, false);     //Ashhide Mushan Beast
			player->LearnSpell(127170, false);     //Astral Cloud Serpent
			player->LearnSpell(123992, false);     //Azure Cloud Serpent
			player->LearnSpell(59567, false);     //Azure Drake
			player->LearnSpell(41514, false);     //Azure Netherwing Drake
			player->LearnSpell(127174, false);     //Azure Riding Crane
			player->LearnSpell(118089, false);     //Azure Water Strider
			player->LearnSpell(51412, false);     //Big Battle Bear
			player->LearnSpell(58983, false);     //Big Blizzard Bear
			player->LearnSpell(71342, false);     //Big Love Rocket
			player->LearnSpell(22719, false);     //Black Battlestrider
			player->LearnSpell(127286, false);     //Black Dragon Turtle
			player->LearnSpell(59650, false);     //Black Drake
			player->LearnSpell(35022, false);     //Black Hawkstrider
			player->LearnSpell(16055, false);     //Black Nightsaber
			player->LearnSpell(138642, false);     //Black Primal Raptor
			player->LearnSpell(59976, false);     //Black Proto-Drake
			player->LearnSpell(25863, false);     //Black Qiraji Battle Tank
			player->LearnSpell(26655, false);     //Black Qiraji Battle Tank
			player->LearnSpell(26656, false);     //Black Qiraji Battle Tank
			player->LearnSpell(17461, false);     //Black Ram
			player->LearnSpell(130138, false);     //Black Riding Goat
			player->LearnSpell(127209, false);     //Black Riding Yak
			player->LearnSpell(64977, false);     //Black Skeletal Horse
			player->LearnSpell(470, false);     //Black Stallion
			player->LearnSpell(60118, false);     //Black War Bear
			player->LearnSpell(60119, false);     //Black War Bear
			player->LearnSpell(48027, false);     //Black War Elekk
			player->LearnSpell(22718, false);     //Black War Kodo
			player->LearnSpell(59785, false);     //Black War Mammoth
			player->LearnSpell(59788, false);     //Black War Mammoth
			player->LearnSpell(22720, false);     //Black War Ram
			player->LearnSpell(22721, false);     //Black War Raptor
			player->LearnSpell(22717, false);     //Black War Steed
			player->LearnSpell(22723, false);     //Black War Tiger
			player->LearnSpell(22724, false);     //Black War Wolf
			player->LearnSpell(64658, false);     //Black Wolf
			player->LearnSpell(171627, false);     //Blacksteel Battleboar
			player->LearnSpell(107842, false);     //Blazing Drake
			player->LearnSpell(74856, false);     //Blazing Hippogryph
			player->LearnSpell(127220, false);     //Blonde Riding Yak
			player->LearnSpell(72808, false);     //Bloodbathed Frostbrood Vanquisher
			player->LearnSpell(171620, false);     //Bloodhoof Bull
			player->LearnSpell(127287, false);     //Blue Dragon Turtle
			player->LearnSpell(61996, false);     //Blue Dragonhawk
			player->LearnSpell(59568, false);     //Blue Drake
			player->LearnSpell(35020, false);     //Blue Hawkstrider
			player->LearnSpell(10969, false);     //Blue Mechanostrider
			player->LearnSpell(59996, false);     //Blue Proto-Drake
			player->LearnSpell(25953, false);     //Blue Qiraji Battle Tank
			player->LearnSpell(39803, false);     //Blue Riding Nether Ray
			player->LearnSpell(129934, false);     //Blue Shado-Pan Riding Tiger
			player->LearnSpell(17463, false);     //Blue Skeletal Horse
			player->LearnSpell(64656, false);     //Blue Skeletal Warhorse
			player->LearnSpell(32244, false);     //Blue Wind Rider
			player->LearnSpell(138640, false);     //Bone-White Primal Raptor
			player->LearnSpell(142641, false);     //Brawler's Burly Mushan Beast
			player->LearnSpell(171832, false);     //Breezestrider Stallion
			player->LearnSpell(50869, false);     //Brewfest Kodo
			player->LearnSpell(43899, false);     //Brewfest Ram
			player->LearnSpell(190690, false);     //Bristling Hellboar
			player->LearnSpell(59569, false);     //Bronze Drake
			player->LearnSpell(127288, false);     //Brown Dragon Turtle
			player->LearnSpell(34406, false);     //Brown Elekk
			player->LearnSpell(458, false);     //Brown Horse
			player->LearnSpell(18990, false);     //Brown Kodo
			player->LearnSpell(6899, false);     //Brown Ram
			player->LearnSpell(88748, false);     //Brown Riding Camel
			player->LearnSpell(130086, false);     //Brown Riding Goat
			player->LearnSpell(127213, false);     //Brown Riding Yak
			player->LearnSpell(17464, false);     //Brown Skeletal Horse
			player->LearnSpell(6654, false);     //Brown Wolf
			player->LearnSpell(58615, false);     //Brutal Nether Drake
			player->LearnSpell(124550, false);     //Cataclysmic Gladiator's Twilight Drake
			player->LearnSpell(75614, false);     //Celestial Steed
			player->LearnSpell(43927, false);     //Cenarion War Hippogryph
			player->LearnSpell(171848, false);     //Challenger's War Yeti
			player->LearnSpell(171846, false);     //Champion's Treadblade
			player->LearnSpell(6648, false);     //Chestnut Mare
			player->LearnSpell(171847, false);     //Cindermane Charger
			player->LearnSpell(139448, false);     //Clutch of Ji-Kun
			player->LearnSpell(189364, false);     //Coalfist Gronnling
			player->LearnSpell(41515, false);     //Cobalt Netherwing Drake
			player->LearnSpell(138423, false);     //Cobalt Primordial Direhorn
			player->LearnSpell(39315, false);     //Cobalt Riding Talbuk
			player->LearnSpell(34896, false);     //Cobalt War Talbuk
			player->LearnSpell(170347, false);     //Core Hound
			player->LearnSpell(183117, false);     //Corrupted Dreadwing
			player->LearnSpell(97560, false);     //Corrupted Fire Hawk
			player->LearnSpell(102514, false);     //Corrupted Hippogryph
			player->LearnSpell(169952, false);     //Creeping Carpet
			player->LearnSpell(127156, false);     //Crimson Cloud Serpent
			player->LearnSpell(73313, false);     //Crimson Deathcharger
			player->LearnSpell(129552, false);     //Crimson Pandaren Phoenix
			player->LearnSpell(140250, false);     //Crimson Primal Direhorn
			player->LearnSpell(123160, false);     //Crimson Riding Crane
			player->LearnSpell(127271, false);     //Crimson Water Strider
			player->LearnSpell(68188, false);     //Crusader's Black Warhorse
			player->LearnSpell(68187, false);     //Crusader's White Warhorse
			player->LearnSpell(88990, false);     //Dark Phoenix
			player->LearnSpell(39316, false);     //Dark Riding Talbuk
			player->LearnSpell(34790, false);     //Dark War Talbuk
			player->LearnSpell(103081, false);     //Darkmoon Dancing Bear
			player->LearnSpell(63635, false);     //Darkspear Raptor
			player->LearnSpell(63637, false);     //Darnassian Nightsaber
			player->LearnSpell(64927, false);     //Deadly Gladiator's Frost Wyrm
			player->LearnSpell(190977, false);     //Deathtusk Felboar
			player->LearnSpell(193007, false);     //Demonsaber
			player->LearnSpell(126507, false);     //Depleted-Kyparium Rocket
			player->LearnSpell(6653, false);     //Dire Wolf
			player->LearnSpell(171634, false);     //Domesticated Razorback
			player->LearnSpell(88335, false);     //Drake of the East Wind
			player->LearnSpell(88742, false);     //Drake of the North Wind
			player->LearnSpell(88744, false);     //Drake of the South Wind
			player->LearnSpell(88741, false);     //Drake of the West Wind
			player->LearnSpell(155741, false);     //Dread Raven
			player->LearnSpell(148972, false);     //Dreadsteed
			player->LearnSpell(171844, false);     //Dustmane Direwolf
			player->LearnSpell(171625, false);     //Dusty Rockhide
			player->LearnSpell(32239, false);     //Ebon Gryphon
			player->LearnSpell(194464, false);     //Eclipse Dragonhawk
			player->LearnSpell(175700, false);     //Emerald Drake
			player->LearnSpell(149801, false);     //Emerald Hippogryph
			player->LearnSpell(132118, false);     //Emerald Pandaren Phoenix
			player->LearnSpell(8395, false);     //Emerald Raptor
			player->LearnSpell(142878, false);     //Enchanted Fey Dragon
			player->LearnSpell(63639, false);     //Exodar Elekk
			player->LearnSpell(110039, false);     //Experiment 12-B
			player->LearnSpell(113120, false);     //Feldrake
			player->LearnSpell(97501, false);     //Felfire Hawk
			player->LearnSpell(200175, false);     //Felsaber
			player->LearnSpell(148970, false);     //Felsteed
			player->LearnSpell(182912, false);     //Felsteel Annihilator
			player->LearnSpell(36702, false);     //Fiery Warhorse
			player->LearnSpell(101542, false);     //Flametalon of Alysrazor
			player->LearnSpell(97359, false);     //Flameward Hippogryph
			player->LearnSpell(61451, false);     //Flying Carpet
			player->LearnSpell(44153, false);     //Flying Machine
			player->LearnSpell(63643, false);     //Forsaken Warhorse
			player->LearnSpell(84751, false);     //Fossilized Raptor
			player->LearnSpell(17460, false);     //Frost Ram
			player->LearnSpell(171632, false);     //Frostplains Battleboar
			player->LearnSpell(23509, false);     //Frostwolf Howler
			player->LearnSpell(75596, false);     //Frosty Flying Carpet
			player->LearnSpell(65439, false);     //Furious Gladiator's Frost Wyrm
			player->LearnSpell(171851, false);     //Garn Nighthowl
			player->LearnSpell(171836, false);     //Garn Steelmaw
			player->LearnSpell(126508, false);     //Geosynchronous World Spinner
			player->LearnSpell(136505, false);     //Ghastly Charger
			player->LearnSpell(171635, false);     //Giant Coldsnout
			player->LearnSpell(63638, false);     //Gnomeregan Mechanostrider
			player->LearnSpell(89520, false);     //Goblin Mini Hotrod
			player->LearnSpell(87090, false);     //Goblin Trike
			player->LearnSpell(87091, false);     //Goblin Turbo-Trike
			player->LearnSpell(123993, false);     //Golden Cloud Serpent
			player->LearnSpell(32235, false);     //Golden Gryphon
			player->LearnSpell(90621, false);     //Golden King
			player->LearnSpell(140249, false);     //Golden Primal Direhorn
			player->LearnSpell(127176, false);     //Golden Riding Crane
			player->LearnSpell(127278, false);     //Golden Water Strider
			player->LearnSpell(171436, false);     //Gorestrider Gronnling
			player->LearnSpell(135416, false);     //Grand Armored Gryphon
			player->LearnSpell(135418, false);     //Grand Armored Wyvern
			player->LearnSpell(61465, false);     //Grand Black War Mammoth
			player->LearnSpell(61467, false);     //Grand Black War Mammoth
			player->LearnSpell(122708, false);     //Grand Expedition Yak
			player->LearnSpell(136163, false);     //Grand Gryphon
			player->LearnSpell(61470, false);     //Grand Ice Mammoth
			player->LearnSpell(61469, false);     //Grand Ice Mammoth
			player->LearnSpell(136164, false);     //Grand Wyvern
			player->LearnSpell(35710, false);     //Gray Elekk
			player->LearnSpell(18989, false);     //Gray Kodo
			player->LearnSpell(6777, false);     //Gray Ram
			player->LearnSpell(127295, false);     //Great Black Dragon Turtle
			player->LearnSpell(127302, false);     //Great Blue Dragon Turtle
			player->LearnSpell(35713, false);     //Great Blue Elekk
			player->LearnSpell(49379, false);     //Great Brewfest Kodo
			player->LearnSpell(127308, false);     //Great Brown Dragon Turtle
			player->LearnSpell(23249, false);     //Great Brown Kodo
			player->LearnSpell(65641, false);     //Great Golden Kodo
			player->LearnSpell(23248, false);     //Great Gray Kodo
			player->LearnSpell(127293, false);     //Great Green Dragon Turtle
			player->LearnSpell(35712, false);     //Great Green Elekk
			player->LearnSpell(171636, false);     //Great Greytusk
			player->LearnSpell(127310, false);     //Great Purple Dragon Turtle
			player->LearnSpell(35714, false);     //Great Purple Elekk
			player->LearnSpell(120822, false);     //Great Red Dragon Turtle
			player->LearnSpell(65637, false);     //Great Red Elekk
			player->LearnSpell(23247, false);     //Great White Kodo
			player->LearnSpell(120395, false);     //Green Dragon Turtle
			player->LearnSpell(18991, false);     //Green Kodo
			player->LearnSpell(17453, false);     //Green Mechanostrider
			player->LearnSpell(138643, false);     //Green Primal Raptor
			player->LearnSpell(61294, false);     //Green Proto-Drake
			player->LearnSpell(26056, false);     //Green Qiraji Battle Tank
			player->LearnSpell(39798, false);     //Green Riding Nether Ray
			player->LearnSpell(129932, false);     //Green Shado-Pan Riding Tiger
			player->LearnSpell(17465, false);     //Green Skeletal Warhorse
			player->LearnSpell(32245, false);     //Green Wind Rider
			player->LearnSpell(88750, false);     //Grey Riding Camel
			player->LearnSpell(127216, false);     //Grey Riding Yak
			player->LearnSpell(148619, false);     //Grievous Gladiator's Cloud Serpent
			player->LearnSpell(163025, false);     //Grinning Reaver
			player->LearnSpell(189999, false);     //Grove Warden
			player->LearnSpell(48025, false);     //Headless Horseman's Mount
			player->LearnSpell(110051, false);     //Heart of the Aspects
			player->LearnSpell(142073, false);     //Hearthsteed
			player->LearnSpell(127169, false);     //Heavenly Azure Cloud Serpent
			player->LearnSpell(127161, false);     //Heavenly Crimson Cloud Serpent
			player->LearnSpell(127164, false);     //Heavenly Golden Cloud Serpent
			player->LearnSpell(127165, false);     //Heavenly Jade Cloud Serpent
			player->LearnSpell(127158, false);     //Heavenly Onyx Cloud Serpent
			player->LearnSpell(59799, false);     //Ice Mammoth
			player->LearnSpell(59797, false);     //Ice Mammoth
			player->LearnSpell(72807, false);     //Icebound Frostbrood Vanquisher
			player->LearnSpell(17459, false);     //Icy Blue Mechanostrider Mod A
			player->LearnSpell(189998, false);     //Illidari Felstalker
			player->LearnSpell(124659, false);     //Imperial Quilen
			player->LearnSpell(186305, false);     //Infernal Direwolf
			player->LearnSpell(201098, false);     //Infinite Timereaver
			player->LearnSpell(72286, false);     //Invincible
			player->LearnSpell(153489, false);     //Iron Skyreaver
			player->LearnSpell(63956, false);     //Ironbound Proto-Drake
			player->LearnSpell(142910, false);     //Ironbound Wraithcharger
			player->LearnSpell(63636, false);     //Ironforge Ram
			player->LearnSpell(171621, false);     //Ironhoof Destroyer
			player->LearnSpell(171839, false);     //Ironside Warwolf
			player->LearnSpell(17450, false);     //Ivory Raptor
			player->LearnSpell(113199, false);     //Jade Cloud Serpent
			player->LearnSpell(133023, false);     //Jade Pandaren Kite
			player->LearnSpell(121837, false);     //Jade Panther
			player->LearnSpell(138426, false);     //Jade Primordial Direhorn
			player->LearnSpell(127274, false);     //Jade Water Strider
			player->LearnSpell(120043, false);     //Jeweled Onyx Panther
			player->LearnSpell(127178, false);     //Jungle Riding Crane
			player->LearnSpell(93644, false);     //Kor'kron Annihilator
			player->LearnSpell(148417, false);     //Kor'kron Juggernaut
			player->LearnSpell(148396, false);     //Kor'kron War Wolf
			player->LearnSpell(107845, false);     //Life-Binder's Handmaiden
			player->LearnSpell(65917, false);     //Magic Rooster
			player->LearnSpell(61309, false);     //Magnificent Flying Carpet
			player->LearnSpell(139407, false);     //Malevolent Gladiator's Cloud Serpent
			player->LearnSpell(55531, false);     //Mechano-Hog
			player->LearnSpell(60424, false);     //Mekgineer's Chopper
			player->LearnSpell(44744, false);     //Merciless Nether Drake
			player->LearnSpell(63796, false);     //Mimiron's Head
			player->LearnSpell(191314, false);     //Minion of Grumpus
			player->LearnSpell(171825, false);     //Mosshide Riverwallow
			player->LearnSpell(93623, false);     //Mottled Drake
			player->LearnSpell(171622, false);     //Mottled Meadowstomper
			player->LearnSpell(16084, false);     //Mottled Red Raptor
			player->LearnSpell(171850, false);     //Mount Template 49
			player->LearnSpell(171827, false);     //Mount Template 50
			player->LearnSpell(171840, false);     //Mount Template 51
			player->LearnSpell(103195, false);     //Mountain Horse
			player->LearnSpell(171826, false);     //Mudback Riverbeast
			player->LearnSpell(180545, false);     //Mystic Runesaber
			player->LearnSpell(121820, false);     //Obsidian Nightwing
			player->LearnSpell(66846, false);     //Ochre Skeletal Warhorse
			player->LearnSpell(127154, false);     //Onyx Cloud Serpent
			player->LearnSpell(41513, false);     //Onyx Netherwing Drake
			player->LearnSpell(69395, false);     //Onyxian Drake
			player->LearnSpell(127272, false);     //Orange Water Strider
			player->LearnSpell(63640, false);     //Orgrimmar Wolf
			player->LearnSpell(171833, false);     //Pale Thorngrazer
			player->LearnSpell(16082, false);     //Palomino
			player->LearnSpell(118737, false);     //Pandaren Kite
			player->LearnSpell(130985, false);     //Pandaren Kite
			player->LearnSpell(32345, false);     //Peep the Phoenix Mount
			player->LearnSpell(88718, false);     //Phosphorescent Stone Drake
			player->LearnSpell(472, false);     //Pinto
			player->LearnSpell(60021, false);     //Plagued Proto-Drake
			player->LearnSpell(193695, false);     //Prestigious War Steed
			player->LearnSpell(204166, false);     //Prestigious War Wolf
			player->LearnSpell(148620, false);     //Prideful Gladiator's Cloud Serpent
			player->LearnSpell(186828, false);     //Primal Gladiator's Felblood Gronnling
			player->LearnSpell(97493, false);     //Pureblood Fire Hawk
			player->LearnSpell(127289, false);     //Purple Dragon Turtle
			player->LearnSpell(35711, false);     //Purple Elekk
			player->LearnSpell(35018, false);     //Purple Hawkstrider
			player->LearnSpell(41516, false);     //Purple Netherwing Drake
			player->LearnSpell(39801, false);     //Purple Riding Nether Ray
			player->LearnSpell(23246, false);     //Purple Skeletal Warhorse
			player->LearnSpell(66090, false);     //Quel'dorei Steed
			player->LearnSpell(41252, false);     //Raven Lord
			player->LearnSpell(127290, false);     //Red Dragon Turtle
			player->LearnSpell(61997, false);     //Red Dragonhawk
			player->LearnSpell(59570, false);     //Red Drake
			player->LearnSpell(130092, false);     //Red Flying Cloud
			player->LearnSpell(34795, false);     //Red Hawkstrider
			player->LearnSpell(10873, false);     //Red Mechanostrider
			player->LearnSpell(138641, false);     //Red Primal Raptor
			player->LearnSpell(59961, false);     //Red Proto-Drake
			player->LearnSpell(26054, false);     //Red Qiraji Battle Tank
			player->LearnSpell(39800, false);     //Red Riding Nether Ray
			player->LearnSpell(129935, false);     //Red Shado-Pan Riding Tiger
			player->LearnSpell(17462, false);     //Red Skeletal Horse
			player->LearnSpell(22722, false);     //Red Skeletal Warhorse
			player->LearnSpell(16080, false);     //Red Wolf
			player->LearnSpell(127177, false);     //Regal Riding Crane
			player->LearnSpell(67336, false);     //Relentless Gladiator's Frost Wyrm
			player->LearnSpell(30174, false);     //Riding Turtle
			player->LearnSpell(17481, false);     //Rivendare's Deathcharger
			player->LearnSpell(171628, false);     //Rocktusk Battleboar
			player->LearnSpell(121838, false);     //Ruby Panther
			player->LearnSpell(63963, false);     //Rusted Proto-Drake
			player->LearnSpell(101821, false);     //Ruthless Gladiator's Twilight Drake
			player->LearnSpell(93326, false);     //Sandstone Drake
			player->LearnSpell(121836, false);     //Sapphire Panther
			player->LearnSpell(171824, false);     //Sapphire Riverbeast
			player->LearnSpell(97581, false);     //Savage Raptor
			player->LearnSpell(64731, false);     //Sea Turtle
			player->LearnSpell(171624, false);     //Shadowhide Pearltusk
			player->LearnSpell(171829, false);     //Shadowmane Charger
			player->LearnSpell(66087, false);     //Silver Covenant Hippogryph
			player->LearnSpell(39802, false);     //Silver Riding Nether Ray
			player->LearnSpell(39317, false);     //Silver Riding Talbuk
			player->LearnSpell(34898, false);     //Silver War Talbuk
			player->LearnSpell(63642, false);     //Silvermoon Hawkstrider
			player->LearnSpell(134359, false);     //Sky Golem
			player->LearnSpell(138425, false);     //Slate Primordial Direhorn
			player->LearnSpell(171843, false);     //Smoky Direwolf
			player->LearnSpell(32240, false);     //Snowy Gryphon
			player->LearnSpell(191633, false);     //Soaring Skyterror
			player->LearnSpell(171828, false);     //Solar Spirehawk
			player->LearnSpell(130965, false);     //Son of Galleon
			player->LearnSpell(148392, false);     //Spawn of Galakras
			player->LearnSpell(136471, false);     //Spawn of Horridon
			player->LearnSpell(107516, false);     //Spectral Gryphon
			player->LearnSpell(92231, false);     //Spectral Steed
			player->LearnSpell(42776, false);     //Spectral Tiger
			player->LearnSpell(107517, false);     //Spectral Wind Rider
			player->LearnSpell(92232, false);     //Spectral Wolf
			player->LearnSpell(196681, false);     //Spirit of Eche'ro
			player->LearnSpell(10789, false);     //Spotted Frostsaber
			player->LearnSpell(147595, false);     //Stormcrow
			player->LearnSpell(23510, false);     //Stormpike Battle Charger
			player->LearnSpell(63232, false);     //Stormwind Steed
			player->LearnSpell(66847, false);     //Striped Dawnsaber
			player->LearnSpell(8394, false);     //Striped Frostsaber
			player->LearnSpell(10793, false);     //Striped Nightsaber
			player->LearnSpell(98718, false);     //Subdued Seahorse
			player->LearnSpell(179245, false);     //Summon Chauffeur
			player->LearnSpell(179244, false);     //Summon Chauffeur
			player->LearnSpell(171849, false);     //Sunhide Gronnling
			player->LearnSpell(66088, false);     //Sunreaver Dragonhawk
			player->LearnSpell(66091, false);     //Sunreaver Hawkstrider
			player->LearnSpell(121839, false);     //Sunstone Panther
			player->LearnSpell(68057, false);     //Swift Alliance Steed
			player->LearnSpell(32242, false);     //Swift Blue Gryphon
			player->LearnSpell(23241, false);     //Swift Blue Raptor
			player->LearnSpell(171830, false);     //Swift Breezestrider
			player->LearnSpell(43900, false);     //Swift Brewfest Ram
			player->LearnSpell(23238, false);     //Swift Brown Ram
			player->LearnSpell(23229, false);     //Swift Brown Steed
			player->LearnSpell(23250, false);     //Swift Brown Wolf
			player->LearnSpell(65646, false);     //Swift Burgundy Wolf
			player->LearnSpell(102346, false);     //Swift Forest Strider
			player->LearnSpell(23221, false);     //Swift Frostsaber
			player->LearnSpell(171842, false);     //Swift Frostwolf
			player->LearnSpell(23239, false);     //Swift Gray Ram
			player->LearnSpell(65640, false);     //Swift Gray Steed
			player->LearnSpell(23252, false);     //Swift Gray Wolf
			player->LearnSpell(32290, false);     //Swift Green Gryphon
			player->LearnSpell(35025, false);     //Swift Green Hawkstrider
			player->LearnSpell(23225, false);     //Swift Green Mechanostrider
			player->LearnSpell(32295, false);     //Swift Green Wind Rider
			player->LearnSpell(68056, false);     //Swift Horde Wolf
			player->LearnSpell(102350, false);     //Swift Lovebird
			player->LearnSpell(23219, false);     //Swift Mistsaber
			player->LearnSpell(65638, false);     //Swift Moonsaber
			player->LearnSpell(103196, false);     //Swift Mountain Horse
			player->LearnSpell(37015, false);     //Swift Nether Drake
			player->LearnSpell(23242, false);     //Swift Olive Raptor
			player->LearnSpell(23243, false);     //Swift Orange Raptor
			player->LearnSpell(23227, false);     //Swift Palomino
			player->LearnSpell(33660, false);     //Swift Pink Hawkstrider
			player->LearnSpell(32292, false);     //Swift Purple Gryphon
			player->LearnSpell(35027, false);     //Swift Purple Hawkstrider
			player->LearnSpell(65644, false);     //Swift Purple Raptor
			player->LearnSpell(32297, false);     //Swift Purple Wind Rider
			player->LearnSpell(24242, false);     //Swift Razzashi Raptor
			player->LearnSpell(32289, false);     //Swift Red Gryphon
			player->LearnSpell(65639, false);     //Swift Red Hawkstrider
			player->LearnSpell(32246, false);     //Swift Red Wind Rider
			player->LearnSpell(101573, false);     //Swift Shorestrider
			player->LearnSpell(55164, false);     //Swift Spectral Gryphon
			player->LearnSpell(194046, false);     //Swift Spectral Rylak
			player->LearnSpell(42777, false);     //Swift Spectral Tiger
			player->LearnSpell(102349, false);     //Swift Springstrider
			player->LearnSpell(23338, false);     //Swift Stormsaber
			player->LearnSpell(23251, false);     //Swift Timber Wolf
			player->LearnSpell(65643, false);     //Swift Violet Ram
			player->LearnSpell(35028, false);     //Swift Warstrider
			player->LearnSpell(46628, false);     //Swift White Hawkstrider
			player->LearnSpell(23223, false);     //Swift White Mechanostrider
			player->LearnSpell(23240, false);     //Swift White Ram
			player->LearnSpell(23228, false);     //Swift White Steed
			player->LearnSpell(134573, false);     //Swift Windsteed
			player->LearnSpell(23222, false);     //Swift Yellow Mechanostrider
			player->LearnSpell(32296, false);     //Swift Yellow Wind Rider
			player->LearnSpell(49322, false);     //Swift Zhevra
			player->LearnSpell(96499, false);     //Swift Zulian Panther
			player->LearnSpell(24252, false);     //Swift Zulian Tiger
			player->LearnSpell(88749, false);     //Tan Riding Camel
			player->LearnSpell(39318, false);     //Tan Riding Talbuk
			player->LearnSpell(34899, false);     //Tan War Talbuk
			player->LearnSpell(32243, false);     //Tawny Wind Rider
			player->LearnSpell(18992, false);     //Teal Kodo
			player->LearnSpell(63641, false);     //Thunder Bluff Kodo
			player->LearnSpell(129918, false);     //Thundering August Cloud Serpent
			player->LearnSpell(139442, false);     //Thundering Cobalt Cloud Serpent
			player->LearnSpell(124408, false);     //Thundering Jade Cloud Serpent
			player->LearnSpell(148476, false);     //Thundering Onyx Cloud Serpent
			player->LearnSpell(132036, false);     //Thundering Ruby Cloud Serpent
			player->LearnSpell(580, false);     //Timber Wolf
			player->LearnSpell(60002, false);     //Time-Lost Proto-Drake
			player->LearnSpell(171617, false);     //Trained Icehoof
			player->LearnSpell(171623, false);     //Trained Meadowstomper
			player->LearnSpell(171638, false);     //Trained Riverwallow
			player->LearnSpell(171637, false);     //Trained Rocktusk
			player->LearnSpell(171831, false);     //Trained Silverpelt
			player->LearnSpell(171841, false);     //Trained Snarler
			player->LearnSpell(61425, false);     //Traveler's Tundra Mammoth
			player->LearnSpell(61447, false);     //Traveler's Tundra Mammoth
			player->LearnSpell(171619, false);     //Tundra Icehoof
			player->LearnSpell(44151, false);     //Turbo-Charged Flying Machine
			player->LearnSpell(65642, false);     //Turbostrider
			player->LearnSpell(10796, false);     //Turquoise Raptor
			player->LearnSpell(59571, false);     //Twilight Drake
			player->LearnSpell(107844, false);     //Twilight Harbinger
			player->LearnSpell(107203, false);     //Tyrael's Charger
			player->LearnSpell(148618, false);     //Tyrannical Gladiator's Cloud Serpent
			player->LearnSpell(92155, false);     //Ultramarine Qiraji Battle Tank
			player->LearnSpell(17454, false);     //Unpainted Mechanostrider
			player->LearnSpell(75207, false);     //Vashj'ir Seahorse
			player->LearnSpell(49193, false);     //Vengeful Nether Drake
			player->LearnSpell(64659, false);     //Venomhide Ravasaur
			player->LearnSpell(41517, false);     //Veridian Netherwing Drake
			player->LearnSpell(101282, false);     //Vicious Gladiator's Twilight Drake
			player->LearnSpell(146622, false);     //Vicious Skeletal Warhorse
			player->LearnSpell(185052, false);     //Vicious War Kodo
			player->LearnSpell(183889, false);     //Vicious War Mechanostrider
			player->LearnSpell(171834, false);     //Vicious War Ram
			player->LearnSpell(171835, false);     //Vicious War Raptor
			player->LearnSpell(100332, false);     //Vicious War Steed
			player->LearnSpell(100333, false);     //Vicious War Wolf
			player->LearnSpell(146615, false);     //Vicious Warsaber
			player->LearnSpell(41518, false);     //Violet Netherwing Drake
			player->LearnSpell(132119, false);     //Violet Pandaren Phoenix
			player->LearnSpell(60024, false);     //Violet Proto-Drake
			player->LearnSpell(10799, false);     //Violet Raptor
			player->LearnSpell(88746, false);     //Vitreous Stone Drake
			player->LearnSpell(179478, false);     //Voidtalon of the Dark Star
			player->LearnSpell(88331, false);     //Volcanic Stone Drake
			player->LearnSpell(163024, false);     //Warforged Nightmare
			player->LearnSpell(171845, false);     //Warlord's Deathwheel
			player->LearnSpell(189044, false);     //Warmongering Gladiator's Felblood Gronnling
			player->LearnSpell(171837, false);     //Warsong Direfang
			player->LearnSpell(64657, false);     //White Kodo
			player->LearnSpell(15779, false);     //White Mechanostrider Mod B
			player->LearnSpell(54753, false);     //White Polar Bear
			player->LearnSpell(6898, false);     //White Ram
			player->LearnSpell(102488, false);     //White Riding Camel
			player->LearnSpell(130137, false);     //White Riding Goat
			player->LearnSpell(39319, false);     //White Riding Talbuk
			player->LearnSpell(123182, false);     //White Riding Yak
			player->LearnSpell(65645, false);     //White Skeletal Warhorse
			player->LearnSpell(16083, false);     //White Stallion
			player->LearnSpell(34897, false);     //White War Talbuk
			player->LearnSpell(189043, false);     //Wild Gladiator's Felblood Gronnling
			player->LearnSpell(171633, false);     //Wild Goretusk
			player->LearnSpell(98727, false);     //Winged Guardian
			player->LearnSpell(54729, false);     //Winged Steed of the Ebon Blade
			player->LearnSpell(17229, false);     //Winterspring Frostsaber
			player->LearnSpell(171616, false);     //Witherhide Cliffstomper
			player->LearnSpell(59791, false);     //Wooly Mammoth
			player->LearnSpell(59793, false);     //Wooly Mammoth
			player->LearnSpell(74918, false);     //Wooly White Rhino
			player->LearnSpell(71810, false);     //Wrathful Gladiator's Frost Wyrm
			player->LearnSpell(46197, false);     //X-51 Nether-Rocket
			player->LearnSpell(46199, false);     //X-51 Nether-Rocket X-TREME
			player->LearnSpell(75973, false);     //X-53 Touring Rocket
			player->LearnSpell(26055, false);     //Yellow Qiraji Battle Tank
			break;
		}
		case 61:
		{
			TC_LOG_INFO("misc", "Re-Loading Creature_template...");
			sObjectMgr->LoadCreatureTemplates();
			ChatHandler(player->GetSession()).SendGlobalGMSysMessage("DB table `Creature_template` reloaded.");
			Third(player, item);
			break;

		}
		case 90:
		{
			TC_LOG_INFO("misc", "Re-Loading Npc_vendor...");
			sObjectMgr->LoadVendors();
			ChatHandler(player->GetSession()).SendGlobalGMSysMessage("DB table 'npc_vendor` reloaded.");
			Third(player, item);
			break;
		}
		case 91:
		{
			TC_LOG_INFO("misc", "Re-Loading Npc_trainer...");
			sObjectMgr->LoadTrainerSpell();
			ChatHandler(player->GetSession()).SendGlobalGMSysMessage("DB table 'npc_trainer reloaded.");
			Third(player, item);
			break;
		}
		case 37: // god off
		{
			player->GetSession()->GetPlayer()->SetCommandStatusOff(CHEAT_GOD);
			ChatHandler(player->GetSession()).SendSysMessage("Godmode is OFF. You can take damage.");
			Second(player, item);
			break;

		}
		case 370: // god on
		{
			player->GetSession()->GetPlayer()->SetCommandStatusOn(CHEAT_GOD);
			ChatHandler(player->GetSession()).SendSysMessage("Godmode is ON. You won't take damage.");
			Second(player, item);
			break;
		}
		case 38:  // cast off
		{
			player->GetSession()->GetPlayer()->SetCommandStatusOff(CHEAT_CASTTIME);
			ChatHandler(player->GetSession()).SendSysMessage("Casttime cheat is OFF.");
			Second(player, item);
			return;
			break;
		}
		case 380:  //cast on
		{
			player->GetSession()->GetPlayer()->SetCommandStatusOn(CHEAT_CASTTIME);
			ChatHandler(player->GetSession()).SendSysMessage("Castime cheat is ON.");
			Second(player, item);
			return;
			break;
		}
		case 39:
		{
			player->GetSession()->GetPlayer()->SetCommandStatusOff(CHEAT_POWER);
			ChatHandler(player->GetSession()).SendSysMessage("Power Cheat is OFF.");
			Second(player, item);
			break;
		}
		case 390:
		{
			player->GetSession()->GetPlayer()->SetCommandStatusOn(CHEAT_POWER);
			ChatHandler(player->GetSession()).SendSysMessage("Power Cheat is ON.");
			Second(player, item);
			break;
		}
		case 40:
		{
			player->SetCommandStatusOff(CHEAT_WATERWALK);
			player->SetMovement(MOVE_LAND_WALK);
			ChatHandler(player->GetSession()).SendSysMessage("Waterwalk Cheat is OFF.");
			Second(player, item);
			break;
		}
		case 400:
		{
			player->SetCommandStatusOn(CHEAT_WATERWALK);
			player->SetMovement(MOVE_WATER_WALK);
			ChatHandler(player->GetSession()).SendSysMessage("Waterwalk Cheat is ON.");
			Second(player, item);
			break;
		}
		case 41:
		{
			player->GetSession()->GetPlayer()->SetCommandStatusOff(CHEAT_COOLDOWN);
			ChatHandler(player->GetSession()).SendSysMessage("Cooldown Cheat is OFF.");
			Second(player, item);
			break;
		}
		case 410:
		{
			player->GetSession()->GetPlayer()->SetCommandStatusOn(CHEAT_COOLDOWN);
			ChatHandler(player->GetSession()).SendSysMessage("Cooldown Cheat is ON.");
			Second(player, item);
			break;
		}
		case 42:
		{
			player->SetTaxiCheater(true);
			Second(player, item);
			ChatHandler(player->GetSession()).PSendSysMessage(LANG_YOU_GIVE_TAXIS, player->GetSession()->GetPlayerName().c_str());
			break;
		}    
		case 420:
		{
			player->SetTaxiCheater(false);
			Second(player, item);
			ChatHandler(player->GetSession()).PSendSysMessage(LANG_YOU_REMOVE_TAXIS, player->GetSession()->GetPlayerName().c_str());
			break;
		}
		case 43:
		{
			player->SetGMChat(false);
			player->GetSession()->SendNotification(LANG_GM_CHAT_OFF);
			Second(player, item);
			break;
		}
		case 430:
		{
			player->SetGMChat(true);
			player->GetSession()->SendNotification(LANG_GM_CHAT_ON);
			Second(player, item);
			break;
		}
		case 95:
		{
			player->AddAura(flyspell,player);
			Second(player, item);
			break;
		}
		case 950:
		{
			player->RemoveAura(flyspell);
			Second(player, item);
			break;
		}
		case 96:  //opcode fly on
		{
			player->SetCanFly(true);
			ChatHandler(player->GetSession()).PSendSysMessage(LANG_COMMAND_FLYMODE_STATUS, ChatHandler(player->GetSession()).GetNameLink(player).c_str(), "On");
			Second(player, item);
			break;
		}
		case 960: //opcode fly off
		{
			player->SetCanFly(false);
			ChatHandler(player->GetSession()).PSendSysMessage(LANG_COMMAND_FLYMODE_STATUS, ChatHandler(player->GetSession()).GetNameLink(player).c_str(), "Off");
			Second(player, item);
			break;
		}
		case 97:
		{
			//int mounts[] = {122};
			int balance[] = { 48778, 60025, 127180, 98204, 96503, 43688, 138424, 123886, 16056, 171618, 16081, 66906, 63844, 66907, 67466, 139595, 142478, 61230, 60114, 60116, 171629, 171838, 171626, 171630, 96491, 142266, 136400, 61229, 132117, 40192, 148428, 127170, 123992, 59567, 41514, 127174, 118089, 51412, 58983, 71342, 22719, 127286, 59650, 35022, 16055, 138642, 59976, 25863, 26655, 26656, 17461, 130138, 127209, 64977, 470, 60118, 60119, 48027, 22718, 59785, 59788, 22720, 22721, 22717, 22723, 22724, 64658, 171627, 107842, 74856, 127220, 72808, 171620, 127287, 61996, 59568, 35020, 10969, 59996, 25953, 39803, 129934, 17463, 64656, 32244, 138640, 142641, 171832, 50869, 43899, 190690, 59569, 127288, 34406, 458, 18990, 6899, 88748, 130086, 127213, 17464, 6654, 58615, 124550, 75614, 43927, 171848, 171846, 6648, 171847, 139448, 189364, 41515, 138423, 39315, 34896, 170347, 183117, 97560, 102514, 169952, 127156, 73313, 129552, 140250, 123160, 127271, 68188, 68187, 88990, 39316, 34790, 103081, 63635, 63637, 64927, 190977, 193007, 126507, 6653, 171634, 88335, 88742, 88744, 88741, 155741, 148972, 171844, 171625, 32239, 194464, 175700, 149801, 132118, 8395, 142878, 63639, 110039, 113120, 97501, 200175, 148970, 182912, 36702, 101542, 97359, 61451, 44153, 63643, 84751, 17460, 171632, 23509, 75596, 65439, 171851, 171836, 126508, 136505, 171635, 63638, 89520, 87090, 87091, 123993, 32235, 90621, 140249, 127176, 127278, 171436, 135416, 135418, 61465, 61467, 122708, 136163, 61470, 61469, 136164, 35710, 18989, 6777, 127295, 127302, 35713, 49379, 127308, 23249, 65641, 23248, 127293, 35712, 171636, 127310, 35714, 120822, 65637, 23247, 120395, 18991, 17453, 138643, 61294, 26056, 39798, 129932, 17465, 32245, 88750, 127216, 148619, 163025, 189999, 48025, 110051, 142073, 127169, 127161, 127164, 127165, 127158, 59799, 59797, 72807, 17459, 189998, 124659, 186305, 201098, 72286, 153489, 63956, 142910, 63636, 171621, 171839, 17450, 113199, 133023, 121837, 138426, 127274, 120043, 127178, 93644, 148417, 148396, 107845, 65917, 61309, 139407, 55531, 60424, 44744, 63796, 191314, 171825, 93623, 171622, 16084, 171850, 171827, 171840, 103195, 171826, 180545, 121820, 66846, 127154, 41513, 69395, 127272, 63640, 171833, 16082, 118737, 130985, 32345, 88718, 472, 60021, 193695, 204166, 148620, 186828, 97493, 127289, 35711, 35018, 41516, 39801, 23246, 66090, 41252, 127290, 61997, 59570, 130092, 34795, 10873, 138641, 59961, 26054, 39800, 129935, 17462, 22722, 16080, 127177, 67336, 30174, 17481, 171628, 121838, 63963, 101821, 93326, 121836, 171824, 97581, 64731, 171624, 171829, 66087, 39802, 39317, 34898, 63642, 134359, 138425, 171843, 32240, 191633, 171828, 130965, 148392, 136471, 107516, 92231, 42776, 107517, 92232, 196681, 10789, 147595, 23510, 63232, 66847, 8394, 10793, 98718, 179245, 179244, 171849, 66088, 66091, 121839, 68057, 32242, 23241, 171830, 43900, 23238, 23229, 23250, 65646, 102346, 23221, 171842, 23239, 65640, 23252, 32290, 35025, 23225, 32295, 68056, 102350, 23219, 65638, 103196, 37015, 23242, 23243, 23227, 33660, 32292, 35027, 65644, 32297, 24242, 32289, 65639, 32246, 101573, 55164, 194046, 42777, 102349, 23338, 23251, 65643, 35028, 46628, 23223, 23240, 23228, 134573, 23222, 32296, 49322, 96499, 24252, 88749, 39318, 34899, 32243, 18992, 63641, 129918, 139442, 124408, 148476, 132036, 580, 60002, 171617, 171623, 171638, 171637, 171831, 171841, 61425, 61447, 171619, 44151, 65642, 10796, 59571, 107844, 107203, 148618, 92155, 17454, 75207, 49193, 64659, 41517, 101282, 146622, 185052, 183889, 171834, 171835, 100332, 100333, 146615, 41518, 132119, 60024, 10799, 88746, 179478, 88331, 163024, 171845, 189044, 171837, 64657, 15779, 54753, 6898, 102488, 130137, 39319, 123182, 65645, 16083, 34897, 189043, 171633, 98727, 54729, 17229, 171616, 59791, 59793, 74918, 71810, 46197, 46199, 75973, 26055 };
			for (int i = 0; i < 514; i++)
			{
				SpellInfo const * info = sSpellMgr->GetSpellInfo(balance[i]);
				if (info == NULL)
				{
					ChatHandler(player->GetSession()).PSendSysMessage("Spell %u dont exist", balance[i]);

				}
				player->LearnSpell(balance[i], false);
				//ChatHandler(player->GetSession()).PSendSysMessage("Entry: %u Name: %s",balance[i],info->SpellName[player->GetSession()->GetSessionDbcLocale()]);
			}
			//player->GetSession()->SendNotification("%i", balance[1]);
			ModifyMenuE(player, item);
			break;
		}
		}
	}
	void OnGossipSelectCode(Player* player, Item* item, uint32 sender, uint32 action, const char*code)
	{
		player->PlayerTalkClass->ClearMenus();
		switch (action)
		{
		case 10:
		{
			uint32 spell = atol(code);
			player->LearnSpell(spell, false);
			First(player, item);
			break;
		}
		case 11:
		{
			uint32 unlearn = atol(code);
			player->RemoveSpell(unlearn, false);
			First(player, item);
			break;

		}
		case 12:
		{
			uint32 aura = atol(code);
			player->AddAura(aura, player);
			First(player, item);
			break;
		}
		case 13:
		{
			int8 level = atol(code);
			Player* target = player->GetSelectedPlayer();
			if (!level)
				return;
			PlayerLevelInfo info;
			sObjectMgr->GetPlayerLevelInfo(player->getRace(), player->getClass(), level, &info);
			if (target)
			{
				target->GiveLevel(level);
				First(player, item);
			}
			else
			{
				player->GiveLevel(level);
				First(player, item);
				player->GetSession()->SendNotification("You modify level %u", level);
			}
			break;

		}
		case 14:
		{
			uint32 creature = atol(code);
			Player *target = player->GetSession()->GetPlayer();
			


			if (!sObjectMgr->GetCreatureTemplate(creature))
			{
				target->GetSession()->SendNotification("No creature found with entry: %u", creature);
				First(player, item);
			}
			else
			{
				//player->SummonCreature(creature, player->GetPositionX(), player->GetPositionY(), player->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN, 45000);
				target->SummonCreature(creature, *target, TEMPSUMMON_TIMED_DESPAWN, 45000);
				First(player, item);
				break;
			}
		}
		case 15:
		{
			uint32 sound = atol(code);
			player->PlayDirectSound(sound);
			First(player, item);
			break;
		}
		case 16:
		{
			uint32 additem = 0;
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
		}
		case 17:
		{
			uint32 additem = atol(code);
			Player*target = player->GetSelectedPlayer();
			if (target)
			{
				target->AddItem(additem, 10);
				First(player, item);
			}
			else
			{
				player->AddItem(additem, 10);
				First(player, item);
			}
			break;
		}
		case 18:
		{
			uint32 desitem = atol(code);
			Player* target = player->GetSelectedPlayer();
			if (target)
			{
				target->DestroyItemCount(desitem, 1, false);
				First(player, item);
				player->GetSession()->SendNotification("You destroy item %u from player %s", desitem, target->GetName());
			}
			else
			{
				player->DestroyItemCount(desitem, 1, false);
				First(player, item);
			}
			break;
		}
		case 19:
		{
			uint32 morph = atol(code);
			Player* target = player->GetSelectedPlayer();
			if (!target)
				target = player;
			if (target)
			{
				target->SetDisplayId(morph);
				First(player, item);
			}
			break;
		}
		case 20:
		{
			uint8 speed = atol(code);
			if (speed > 50)
			{
				player->GetSession()->SendNotification("You cant set movespeed over 50");
				First(player, item);
			}
			else
			{
				player->SetSpeedRate(MOVE_WALK, speed);
				player->SetSpeedRate(MOVE_RUN, speed);
				player->SetSpeedRate(MOVE_RUN_BACK, speed);
				player->SetSpeedRate(MOVE_FLIGHT, speed);
				player->SetSpeedRate(MOVE_SWIM, speed);
				player->SetSpeedRate(MOVE_SWIM_BACK, speed);
				player->SetSpeedRate(MOVE_FLIGHT_BACK, speed);
				CharacterDatabase.PQuery("UPDATE teleport set X2 = %u WHERE guid = %u",speed,player->GetGUID());
				First(player, item);
			}
			break;
		}
		case 21:
		{
			for (uint8 i = 0; i < 64; i++)
			{
				player->SetFlag(PLAYER_EXPLORED_ZONES_1 + i, 0xFFFFFFFF);
				First(player, item);
			}
			break;
		}
		case 22:
		{
			uint32 entry = atoi(code);
			if (player->HasSkill(43))
			{
				player->UpdateSkill(43, entry);
			}
			else if (player->HasSkill(55))
			{
				player->UpdateSkill(55, entry);
			}
			else if (player->HasSkill(44))
			{
				player->UpdateSkill(44, entry);
			}
			else if (player->HasSkill(95))
			{
				player->UpdateSkill(95, entry);
			}
			else if (player->HasSkill(54))
			{
				player->UpdateSkill(54, entry);
			}
			else if (player->HasSkill(45))
			{
				player->UpdateSkill(45, entry);
			}
			else if (player->HasSkill(46))
			{
				player->UpdateSkill(46, entry);
			}
			else if (player->HasSkill(136))
			{
				player->UpdateSkill(136, entry);
			}
			else if (player->HasSkill(160))
			{
				player->UpdateSkill(160, entry);
			}
			else if (player->HasSkill(162))
			{
				player->UpdateSkill(162, entry);
			}
			else if (player->HasSkill(172))
			{
				player->UpdateSkill(172, entry);
			}
			else if (player->HasSkill(173))
			{
				player->UpdateSkill(173, entry);
			}
			else if (player->HasSkill(176))
			{
				player->UpdateSkill(176, entry);
			}
			else if (player->HasSkill(226))
			{
				player->UpdateSkill(226, entry);
			}
			else if (player->HasSkill(228))
			{
				player->UpdateSkill(228, entry);
			}
			else if (player->HasSkill(229))
			{
				player->UpdateSkill(229, entry);
			}
			else if (player->HasSkill(473))
			{
				player->UpdateSkill(473, entry);
			}
			ChatHandler(player->GetSession()).PSendSysMessage("Test for noobs");
			First(player, item);

			break;
		}
		case 23:
		{
			Player* target;
			ObjectGuid targetGuid;
			std::string targetName;
			if (!ChatHandler(player->GetSession()).extractPlayerTarget((char*)code, &target, &targetGuid, &targetName))
			{
				First(player, item);
				return;
			}

			Player* _player = player->GetSession()->GetPlayer();
			if (target == _player || targetGuid == _player->GetGUID())
			{
				ChatHandler(player->GetSession()).PSendSysMessage(LANG_CANT_TELEPORT_SELF);
				ChatHandler(player->GetSession()).SetSentErrorMessage(true);
				return;
			}

			if (target)
			{
				std::string nameLink = ChatHandler(player->GetSession()).playerLink(targetName);
				// check online security
				if (ChatHandler(player->GetSession()).HasLowerSecurity(target, ObjectGuid::Empty))
					return;

				if (target->IsBeingTeleported())
				{
					ChatHandler(player->GetSession()).PSendSysMessage(LANG_IS_TELEPORTED, nameLink.c_str());
					ChatHandler(player->GetSession()).SetSentErrorMessage(true);
					return;
				}

				Map* map = player->GetSession()->GetPlayer()->GetMap();

				if (map->IsBattlegroundOrArena())
				{
					// only allow if gm mode is on
					if (!_player->IsGameMaster())
					{
						ChatHandler(player->GetSession()).PSendSysMessage(LANG_CANNOT_GO_TO_BG_GM, nameLink.c_str());
						ChatHandler(player->GetSession()).SetSentErrorMessage(true);
						return;
					}
					// if both players are in different bgs
					else if (target->GetBattlegroundId() && player->GetSession()->GetPlayer()->GetBattlegroundId() != target->GetBattlegroundId())
						target->LeaveBattleground(false); // Note: should be changed so target gets no Deserter debuff

														  // all's well, set bg id
														  // when porting out from the bg, it will be reset to 0
					target->SetBattlegroundId(target->GetSession()->GetPlayer()->GetBattlegroundId(), target->GetSession()->GetPlayer()->GetBattlegroundTypeId());
					// remember current position as entry point for return at bg end teleportation
					if (!target->GetMap()->IsBattlegroundOrArena())
						target->SetBattlegroundEntryPoint();
				}
				else if (map->IsDungeon())
				{
					Map* destMap = target->GetMap();

					if (destMap->Instanceable() && destMap->GetInstanceId() != map->GetInstanceId())
						target->UnbindInstance(map->GetInstanceId(), target->GetDungeonDifficulty(), true);

				}

				ChatHandler(player->GetSession()).PSendSysMessage(LANG_SUMMONING, nameLink.c_str(), "");
				if (ChatHandler(player->GetSession()).needReportToTarget(target))
					ChatHandler(target->GetSession()).PSendSysMessage(LANG_SUMMONED_BY, ChatHandler(player->GetSession()).playerLink(_player->GetName()).c_str());

				// stop flight if need
				if (target->IsInFlight())
				{
					target->GetMotionMaster()->MovementExpired();
					target->CleanupAfterTaxiFlight();
				}
				// save only in non-flight case
				else
					target->SaveRecallPosition();

				// before GM
				float x, y, z;
				player->GetSession()->GetPlayer()->GetClosePoint(x, y, z, target->GetCombatReach());
				target->TeleportTo(player->GetSession()->GetPlayer()->GetMapId(), x, y, z, target->GetOrientation());
				target->SetPhaseMask(player->GetSession()->GetPlayer()->GetPhaseMask(), true);
			}
			else
			{
				// check offline security
				if (ChatHandler(player->GetSession()).HasLowerSecurity(NULL, targetGuid))
					return;

				std::string nameLink = ChatHandler(player->GetSession()).playerLink(targetName);

				ChatHandler(player->GetSession()).PSendSysMessage(LANG_SUMMONING, nameLink.c_str(), player->GetSession()->GetTrinityString(LANG_OFFLINE));

				// in point where GM stay
				SQLTransaction dummy;
				Player::SavePositionInDB(WorldLocation(player->GetSession()->GetPlayer()->GetMapId(),
					player->GetSession()->GetPlayer()->GetPositionX(),
					player->GetSession()->GetPlayer()->GetPositionY(),
					player->GetSession()->GetPlayer()->GetPositionZ(),
					player->GetSession()->GetPlayer()->GetOrientation()),
					player->GetSession()->GetPlayer()->GetZoneId(),
					targetGuid, dummy);
			}
			First(player, item);
			return;
			break;
		}
		case 24:
		{
			uint32 money = atol(code);
			Player* target = player->GetSelectedPlayer();
			if (target)
			{
				target->ModifyMoney(money*GOLD);
				First(player, item);
			}
			else
			{
				player->ModifyMoney(money*GOLD);
				First(player, item);
			}
			break;
		}
		case 26:
		{
			uint32 arenap = atol(code);
			Player* target = player->GetSelectedPlayer();
			if (target)
			{
				target->ModifyArenaPoints(arenap);
				First(player, item);
			}
			else
			{
				player->ModifyArenaPoints(arenap);
				First(player, item);
			}
			break;
		}
		case 27:
		{
			char* id_p = ChatHandler(player->GetSession()).extractKeyFromLink((char*)code, "Htitle");
			if (!id_p)
				return;

			int32 id = atoi(id_p);
			if (id <= 0)
			{
				ChatHandler(player->GetSession()).PSendSysMessage(LANG_INVALID_TITLE_ID, id);
				ChatHandler(player->GetSession()).SetSentErrorMessage(true);
				First(player, item);
				return;
			}

			Player* target = player->GetSelectedPlayer();
			if (!target)
			{
				ChatHandler(player->GetSession()).SendSysMessage(LANG_NO_CHAR_SELECTED);
				ChatHandler(player->GetSession()).SetSentErrorMessage(true);
				return;
			}

			// check online security
			if (ChatHandler(player->GetSession()).HasLowerSecurity(target, ObjectGuid::Empty))
			return;

			CharTitlesEntry const* titleInfo = sCharTitlesStore.LookupEntry(id);
			if (!titleInfo)
			{
				ChatHandler(player->GetSession()).PSendSysMessage(LANG_INVALID_TITLE_ID, id);
				ChatHandler(player->GetSession()).SetSentErrorMessage(true);
				return;
			}

			std::string tNameLink = ChatHandler(player->GetSession()).GetNameLink(target);

			char titleNameStr[80];
			snprintf(titleNameStr, 80, target->getGender() == GENDER_MALE ? titleInfo->nameMale[player->GetSession()->GetSessionDbcLocale()] : titleInfo->nameFemale[player->GetSession()->GetSessionDbcLocale()], target->GetName().c_str());

			target->SetTitle(titleInfo);
			ChatHandler(player->GetSession()).PSendSysMessage(LANG_TITLE_ADD_RES, id, titleNameStr, tNameLink.c_str());
			First(player, item);
			return;
			break;
		}
		case 29:
		{
			uint32 cast = atol(code);
			Player* target = player->GetSelectedPlayer();
			if (target)
			{
				target->CastSpell(player, cast, true, 0, 0, player->GetGUID());
				First(player, item);
			}
			else
			{
				player->CastSpell(player, cast);
				CharacterDatabase.PExecute("UPDATE start set spellcast = %u where guid = %u",cast, player->GetGUID());
				player->GetSession()->SendNotification("%s", RandomDBCNames(spell,cast).c_str());
				First(player, item);
			}
			break;
		}
		case 31:
		{
			char msg[2048];
			sprintf(msg, player->GetSession()->GetTrinityString(LANG_SYSTEMMESSAGE), code);
			Second(player, item);
			sWorld->SendServerMessage(SERVER_MSG_STRING, msg);
			break;

		}
		case 32:
		{
			std::string str = player->GetSession()->GetTrinityString(LANG_GLOBAL_NOTIFY);
			str += code;
			WorldPacket data(SMSG_NOTIFICATION, (str.size() + 5));
			Second(player, item);
			data << str;
			sWorld->SendGlobalMessage(&data);
			break;
		}
		case 36:  //item set opc
		{
			if (!player->GetSession() && !player->GetSession()->GetPlayer())
				return;

			char const* id = ChatHandler(player->GetSession()).extractKeyFromLink((char*)code, "Hitemset"); // number or [name] Shift-click form |color|Hitemset:itemset_id|h[name]|h|r
			if (!id)
				return;
			uint32 itemSetId = atoul(id);

			if (itemSetId == 0)
			{
				ChatHandler(player->GetSession()).PSendSysMessage(LANG_NO_ITEMS_FROM_ITEMSET_FOUND, itemSetId);
				ChatHandler(player->GetSession()).SetSentErrorMessage(true);
				Second(player, item);
				return;
			}

			Player* playerTarget = player->GetSelectedPlayer();
			if (!playerTarget)
				playerTarget = player;

			TC_LOG_DEBUG("misc", player->GetSession()->GetTrinityString(LANG_ADDITEMSET), itemSetId);

			bool found = false;
			ItemTemplateContainer const& its = sObjectMgr->GetItemTemplateStore();
			for (ItemTemplateContainer::const_iterator itr = its.begin(); itr != its.end(); ++itr)
			{
				if (itr->second.ItemSet == itemSetId)
				{
					found = true;
					ItemPosCountVec dest;
					InventoryResult msg = playerTarget->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, itr->second.ItemId, 1);
					if (msg == EQUIP_ERR_OK)
					{
						Item* item = playerTarget->StoreNewItem(dest, itr->second.ItemId, true);

						// remove binding (let GM give it to another player later)
						if (player == playerTarget)
							item->SetBinding(false);

						player->SendNewItem(item, 1, false, true);
						if (player != playerTarget)
							playerTarget->SendNewItem(item, 1, true, false);
					}
					else
					{
						player->SendEquipError(msg, NULL, NULL, itr->second.ItemId);
						ChatHandler(player->GetSession()).PSendSysMessage(LANG_ITEM_CANNOT_CREATE, itr->second.ItemId, 1);
						Second(player, item);
					}
				}
			}

			if (!found)
			{
				ChatHandler(player->GetSession()).PSendSysMessage(LANG_NO_ITEMS_FROM_ITEMSET_FOUND, itemSetId);
				ChatHandler(player->GetSession()).SetSentErrorMessage(true);
				Second(player, item);
				return;
			}
			break;
		}
		
		
		
 
		case 44:
		{
			if (!code || code != "on" || code != "off")
			{
				Second(player, item);
			}
			Player* target = player->GetSession()->GetPlayer();
		    WorldPacket data(12);
			 if (strncmp(code, "on", 3) == 0)
			    	data.SetOpcode(SMSG_MOVE_SET_CAN_FLY);
			 else if (strncmp(code, "off", 4) == 0)
				    data.SetOpcode(SMSG_MOVE_UNSET_CAN_FLY);
		    	else
			{
					ChatHandler(player->GetSession()).PSendSysMessage(LANG_USE_BOL);
					Second(player, item);
			}
	        data << target->GetPackGUID();
		    data << uint32(0);
	        target->SendMessageToSet(&data, true);
		    ChatHandler(player->GetSession()).PSendSysMessage(LANG_COMMAND_FLYMODE_STATUS, ChatHandler(player->GetSession()).GetNameLink(target).c_str(), code);
			Second(player, item);
			return;
			break;
		}
		case 45:
		{
			uint32 honor = atol(code);
			Player* target = player->GetSelectedPlayer();
			if (target)
			{
				target->ModifyHonorPoints(honor);
				Second(player, item);
			}
			else
				player->ModifyHonorPoints(honor);
				Second(player, item);

			break;
		}
		case 46:
		{
			if (!*code)
				return;

			std::string namePart = code;
			std::wstring wNamePart;

			// converting string that we try to find to lower case
			if (!Utf8toWStr(namePart, wNamePart))
				return;

			wstrToLower(wNamePart);

			bool found = false;
			uint32 count = 0;
			uint32 maxResults = sWorld->getIntConfig(CONFIG_MAX_RESULTS_LOOKUP_COMMANDS);

			// Search in `item_template`
			ItemTemplateContainer const& its = sObjectMgr->GetItemTemplateStore();
			for (ItemTemplateContainer::const_iterator itr = its.begin(); itr != its.end(); ++itr)
			{
				int localeIndex = player->GetSession()->GetSessionDbLocaleIndex();
				if (localeIndex >= 0)
				{
					uint8 ulocaleIndex = uint8(localeIndex);
					if (ItemLocale const* il = sObjectMgr->GetItemLocale(itr->second.ItemId))
					{
						if (il->Name.size() > ulocaleIndex && !il->Name[ulocaleIndex].empty())
						{
							std::string name = il->Name[ulocaleIndex];

							if (Utf8FitTo(name, wNamePart))
							{
								if (maxResults && count++ == maxResults)
								{
									ChatHandler(player->GetSession()).PSendSysMessage(LANG_COMMAND_LOOKUP_MAX_RESULTS, maxResults);
									return;
								}

								if (player->GetSession())
									ChatHandler(player->GetSession()).PSendSysMessage(LANG_ITEM_LIST_CHAT, itr->second.ItemId, itr->second.ItemId, name.c_str());
								else
									ChatHandler(player->GetSession()).PSendSysMessage(LANG_ITEM_LIST_CONSOLE, itr->second.ItemId, name.c_str());

								if (!found)
									found = true;

								continue;
							}
						}
					}
				}

				std::string name = itr->second.Name1;
				if (name.empty())
					continue;

				if (Utf8FitTo(name, wNamePart))
				{
					if (maxResults && count++ == maxResults)
					{
						ChatHandler(player->GetSession()).PSendSysMessage(LANG_COMMAND_LOOKUP_MAX_RESULTS, maxResults);
						return;
					}

					if (player->GetSession())
						ChatHandler(player->GetSession()).PSendSysMessage(LANG_ITEM_LIST_CHAT, itr->second.ItemId, itr->second.ItemId, name.c_str());
					else
						ChatHandler(player->GetSession()).PSendSysMessage(LANG_ITEM_LIST_CONSOLE, itr->second.ItemId, name.c_str());

					if (!found)
						found = true;
				}
			}

			if (!found)
				ChatHandler(player->GetSession()).SendSysMessage(LANG_COMMAND_NOITEMFOUND);
			Third(player, item);

			return;
			break;
		}
		case 47:
		{
			if (!*code)
				return;

			// can be NULL at console call
			Player* target = player;

			std::string namePart = code;
			std::wstring wNamePart;

			// converting string that we try to find to lower case
			if (!Utf8toWStr(namePart, wNamePart))
				return;

			wstrToLower(wNamePart);

			bool found = false;
			uint32 count = 0;
			uint32 maxResults = sWorld->getIntConfig(CONFIG_MAX_RESULTS_LOOKUP_COMMANDS);

			ObjectMgr::QuestMap const& qTemplates = sObjectMgr->GetQuestTemplates();
			for (ObjectMgr::QuestMap::const_iterator iter = qTemplates.begin(); iter != qTemplates.end(); ++iter)
			{
				Quest* qInfo = iter->second;

				int localeIndex = player->GetSession()->GetSessionDbLocaleIndex();
				if (localeIndex >= 0)
				{
					uint8 ulocaleIndex = uint8(localeIndex);
					if (QuestLocale const* questLocale = sObjectMgr->GetQuestLocale(qInfo->GetQuestId()))
					{
						if (questLocale->Title.size() > ulocaleIndex && !questLocale->Title[ulocaleIndex].empty())
						{
							std::string title = questLocale->Title[ulocaleIndex];

							if (Utf8FitTo(title, wNamePart))
							{
								if (maxResults && count++ == maxResults)
								{
									ChatHandler(player->GetSession()).PSendSysMessage(LANG_COMMAND_LOOKUP_MAX_RESULTS, maxResults);
									return;
								}

								char const* statusStr = "";

								if (target)
								{
									QuestStatus status = target->GetQuestStatus(qInfo->GetQuestId());

									switch (status)
									{
									case QUEST_STATUS_COMPLETE:
										statusStr = player->GetSession()->GetTrinityString(LANG_COMMAND_QUEST_COMPLETE);
										break;
									case QUEST_STATUS_INCOMPLETE:
										statusStr = player->GetSession()->GetTrinityString(LANG_COMMAND_QUEST_ACTIVE);
										break;
									case QUEST_STATUS_REWARDED:
										statusStr = player->GetSession()->GetTrinityString(LANG_COMMAND_QUEST_REWARDED);
										break;
									default:
										break;
									}
								}

								if (player->GetSession())
									ChatHandler(player->GetSession()).PSendSysMessage(LANG_QUEST_LIST_CHAT, qInfo->GetQuestId(), qInfo->GetQuestId(), qInfo->GetQuestLevel(), title.c_str(), statusStr);
								else
									ChatHandler(player->GetSession()).PSendSysMessage(LANG_QUEST_LIST_CONSOLE, qInfo->GetQuestId(), title.c_str(), statusStr);

								if (!found)
									found = true;

								continue;
							}
						}
					}
				}

				std::string title = qInfo->GetTitle();
				if (title.empty())
					continue;

				if (Utf8FitTo(title, wNamePart))
				{
					if (maxResults && count++ == maxResults)
					{
						ChatHandler(player->GetSession()).PSendSysMessage(LANG_COMMAND_LOOKUP_MAX_RESULTS, maxResults);
						return;
					}

					char const* statusStr = "";

					if (target)
					{
						QuestStatus status = target->GetQuestStatus(qInfo->GetQuestId());

						switch (status)
						{
						case QUEST_STATUS_COMPLETE:
							statusStr = target->GetSession()->GetTrinityString(LANG_COMMAND_QUEST_COMPLETE);
							break;
						case QUEST_STATUS_INCOMPLETE:
							statusStr = target->GetSession()->GetTrinityString(LANG_COMMAND_QUEST_ACTIVE);
							break;
						case QUEST_STATUS_REWARDED:
							statusStr = target->GetSession()->GetTrinityString(LANG_COMMAND_QUEST_REWARDED);
							break;
						default:
							break;
						}
					}

					if (target->GetSession())
						ChatHandler(target->GetSession()).PSendSysMessage(LANG_QUEST_LIST_CHAT, qInfo->GetQuestId(), qInfo->GetQuestId(), qInfo->GetQuestLevel(), title.c_str(), statusStr);
					else
						ChatHandler(target->GetSession()).PSendSysMessage(LANG_QUEST_LIST_CONSOLE, qInfo->GetQuestId(), title.c_str(), statusStr);

					if (!found)
						found = true;
				}
			}

			if (!found)
				ChatHandler(target->GetSession()).SendSysMessage(LANG_COMMAND_NOQUESTFOUND);
			Third(player, item);
			return;
			break;
		}
		case 48:
		{

			if (!*code)
				return;

			// can be NULL at console call
			Player* target = player->GetSelectedPlayer();

			std::string namePart = code;
			std::wstring wNamePart;

			if (!Utf8toWStr(namePart, wNamePart))
				return;

			// converting string that we try to find to lower case
			wstrToLower(wNamePart);

			bool found = false;
			uint32 count = 0;
			uint32 maxResults = sWorld->getIntConfig(CONFIG_MAX_RESULTS_LOOKUP_COMMANDS);

			// Search in Spell.dbc
			for (uint32 id = 0; id < sSpellMgr->GetSpellInfoStoreSize(); id++)
			{
				SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(id);
				if (spellInfo)
				{
					int locale = player->GetSession()->GetSessionDbcLocale();
					std::string name = spellInfo->SpellName[locale];
					if (name.empty())
						continue;

					if (!Utf8FitTo(name, wNamePart))
					{
						locale = 0;
						for (; locale < TOTAL_LOCALES; ++locale)
						{
							if (locale == player->GetSession()->GetSessionDbcLocale())
								continue;

							name = spellInfo->SpellName[locale];
							if (name.empty())
								continue;

							if (Utf8FitTo(name, wNamePart))
								break;
						}
					}

					if (locale < TOTAL_LOCALES)
					{
						if (maxResults && count++ == maxResults)
						{
							ChatHandler(player->GetSession()).PSendSysMessage(LANG_COMMAND_LOOKUP_MAX_RESULTS, maxResults);
							return;
						}

						bool known = target && target->HasSpell(id);
						bool learn = (spellInfo->Effects[0].Effect == SPELL_EFFECT_LEARN_SPELL);

						SpellInfo const* learnSpellInfo = sSpellMgr->GetSpellInfo(spellInfo->Effects[0].TriggerSpell);

						uint32 talentCost = GetTalentSpellCost(id);

						bool talent = (talentCost > 0);
						bool passive = spellInfo->IsPassive();
						bool active = target && target->HasAura(id);

						// unit32 used to prevent interpreting uint8 as char at output
						// find rank of learned spell for learning spell, or talent rank
						uint32 rank = talentCost ? talentCost : learn && learnSpellInfo ? learnSpellInfo->GetRank() : spellInfo->GetRank();

						// send spell in "id - [name, rank N] [talent] [passive] [learn] [known]" format
						std::ostringstream ss;
						if (player->GetSession())
							ss << id << " - |cffffffff|Hspell:" << id << "|h[" << name;
						else
							ss << id << " - " << name;

						// include rank in link name
						if (rank)
							ss << player->GetSession()->GetTrinityString(LANG_SPELL_RANK) << rank;

						if (player->GetSession())
							ss << ' ' << localeNames[locale] << "]|h|r";
						else
							ss << ' ' << localeNames[locale];

						if (talent)
							ss << player->GetSession()->GetTrinityString(LANG_TALENT);
						if (passive)
							ss << player->GetSession()->GetTrinityString(LANG_PASSIVE);
						if (learn)
							ss << player->GetSession()->GetTrinityString(LANG_LEARN);
						if (known)
							ss << player->GetSession()->GetTrinityString(LANG_KNOWN);
						if (active)
							ss << player->GetSession()->GetTrinityString(LANG_ACTIVE);

						ChatHandler(player->GetSession()).SendSysMessage(ss.str().c_str());

						if (!found)
							found = true;
					}
				}
			}
			if (!found)
				ChatHandler(player->GetSession()).SendSysMessage(LANG_COMMAND_NOSPELLFOUND);
			Third(player, item);

			return;
			break;

		}
		case 49:
		{
			if (!*code)
				return;

			// can be NULL in console call
			Player* target = player->GetSelectedPlayer();

			// title name have single string arg for player name
			char const* targetName = target ? target->GetName().c_str() : "NAME";

			std::string namePart = code;
			std::wstring wNamePart;

			if (!Utf8toWStr(namePart, wNamePart))
				return;

			// converting string that we try to find to lower case
			wstrToLower(wNamePart);

			uint32 counter = 0;                                     // Counter for figure out that we found smth.
			uint32 maxResults = sWorld->getIntConfig(CONFIG_MAX_RESULTS_LOOKUP_COMMANDS);

			// Search in CharTitles.dbc
			for (uint32 id = 0; id < sCharTitlesStore.GetNumRows(); id++)
			{
				CharTitlesEntry const* titleInfo = sCharTitlesStore.LookupEntry(id);
				if (titleInfo)
				{
					/// @todo: implement female support
					int locale = player->GetSession()->GetSessionDbcLocale();
					std::string name = titleInfo->nameMale[locale];
					if (name.empty())
						continue;

					if (!Utf8FitTo(name, wNamePart))
					{
						locale = 0;
						for (; locale < TOTAL_LOCALES; ++locale)
						{
							if (locale == player->GetSession()->GetSessionDbcLocale())
								continue;

							name = titleInfo->nameMale[locale];
							if (name.empty())
								continue;

							if (Utf8FitTo(name, wNamePart))
								break;
						}
					}

					if (locale < TOTAL_LOCALES)
					{
						if (maxResults && counter == maxResults)
						{
							ChatHandler(player->GetSession()).PSendSysMessage(LANG_COMMAND_LOOKUP_MAX_RESULTS, maxResults);
							return;
						}

						char const* knownStr = target && target->HasTitle(titleInfo) ? player->GetSession()->GetTrinityString(LANG_KNOWN) : "";

						char const* activeStr = target && target->GetUInt32Value(PLAYER_CHOSEN_TITLE) == titleInfo->bit_index
							? player->GetSession()->GetTrinityString(LANG_ACTIVE)
							: "";

						char titleNameStr[80];
						snprintf(titleNameStr, 80, name.c_str(), targetName);

						// send title in "id (idx:idx) - [namedlink locale]" format
						if (player->GetSession())
							ChatHandler(player->GetSession()).PSendSysMessage(LANG_TITLE_LIST_CHAT, id, titleInfo->bit_index, id, titleNameStr, localeNames[locale], knownStr, activeStr);
						else
							ChatHandler(player->GetSession()).PSendSysMessage(LANG_TITLE_LIST_CONSOLE, id, titleInfo->bit_index, titleNameStr, localeNames[locale], knownStr, activeStr);

						++counter;
					}
				}
			}
			if (counter == 0)  // if counter == 0 then we found nth
				ChatHandler(player->GetSession()).SendSysMessage(LANG_COMMAND_NOTITLEFOUND);
			Third(player, item);
			return;
			break;
		}
		case 60:
		{
			if (!*code)
				return;

			Tokenizer entries(std::string(code), ' ');

			for (Tokenizer::const_iterator itr = entries.begin(); itr != entries.end(); ++itr)
			{
				uint32 entry = uint32(atoi(*itr));

				PreparedStatement* stmt = WorldDatabase.GetPreparedStatement(WORLD_SEL_CREATURE_TEMPLATE);
				stmt->setUInt32(0, entry);
				PreparedQueryResult result = WorldDatabase.Query(stmt);

				if (!result)
				{
					ChatHandler(player->GetSession()).PSendSysMessage(LANG_COMMAND_CREATURETEMPLATE_NOTFOUND, entry);
					continue;
				}

				CreatureTemplate const* cInfo = sObjectMgr->GetCreatureTemplate(entry);
				if (!cInfo)
				{
					ChatHandler(player->GetSession()).PSendSysMessage(LANG_COMMAND_CREATURESTORAGE_NOTFOUND, entry);
					continue;
				}

				TC_LOG_INFO("misc", "Reloading creature template entry %u", entry);

				Field* fields = result->Fetch();
				sObjectMgr->LoadCreatureTemplate(fields);
				sObjectMgr->CheckCreatureTemplate(cInfo);
			}

			ChatHandler(player->GetSession()).SendGlobalGMSysMessage("Creature template reloaded.");
			Fourth(player, item);
			return;
			break;
		}
		case 610:
		{
			Player*target = player->GetSelectedPlayer();
			uint32 exp = atol(code);
			if (!code)
			{
				First(player, item);
			}
			if (!target)
				target = player;
			if (target)
			{
				target->GiveXP(exp, nullptr);
			}
			First(player, item);
			break;
		}
		case 71:
		{
			uint32 entry = atol(code);
			ItemTemplate const*Info = sObjectMgr->GetItemTemplate(entry);
			if (!Info)
			{
				player->GetSession()->SendNotification("no item found");
				Third(player, item);
			}
			else
			Seven(player, item, code);
			break;
		}
		case 72:
		{
			uint32 count = atol(code);
			QueryResult result = CharacterDatabase.PQuery("SELECT item FROM `start` WHERE guid = %u", player->GetGUID());
			Field*fields = result->Fetch();
			int32 item2 = fields[0].GetUInt32();
			player->AddItem(item2, count);
			Third(player, item);
			break;
		}
		case 73:
		{
			uint32 entry = atol(code);
			CreatureDisplayInfoEntry const*Info = sCreatureDisplayInfoStore.LookupEntry(entry);
			if (!Info)
			{
				player->GetSession()->SendNotification("no CreatureDisplay found");
				Third(player, item);
			}
			else
				CreatureDi(player, item, code);
			break;
		}
		case 74:
		{
			uint32 entry = atol(code);
			SpellEntry const*Info = sSpellStore.LookupEntry(entry);
			if (!Info)
			{
				player->GetSession()->SendNotification("no Spell found");
				Third(player, item);
			}
			else
				SpellInfoadmin(player, item, code);
			break;
		}
		case 75:
		{
			uint32 entry = atol(code);
			GameObjectTemplate const*Info = sObjectMgr->GetGameObjectTemplate(entry);
			if (!Info)
			{
				player->GetSession()->SendNotification("no Gameobject found");
				Third(player, item);
			}
			else
				GObjInfo(player, item, code);
			break;
		}
		case 76:
		{
			uint32 entry = atol(code);
			CreatureDisplayInfoExtraEntry const*Info = sCreatureDisplayInfoExtraStore.LookupEntry(entry);
			if (Info == NULL)
			{
				player->GetSession()->SendNotification("extradisplay is not found");
				Third(player, item);
			}
			else
				CreatureDisplayExtra(player, item, code);
			break;
		}
		case 77:
		{
			uint32 entry = atol(code);
			CreatureTemplate const * info = sObjectMgr->GetCreatureTemplate(entry);
			if (!info)
			{
				player->GetSession()->SendNotification("That creature entry dont exist");
				Third(player, item);
			}
			else
				CreaturesTran(player, item, code);
			break;
		}
		case 78:
		{
			uint32 points = atol(code);
			Unit* target = player->GetSelectedUnit();
			if (!target)
				target = player;
			player->SetFreeTalentPoints(points);
			ModifyMenuE(player, item);
			break;

		}
		case 79:
		{
			int32 hp = atol(code);
			Player* target = ChatHandler(player->GetSession()).getSelectedPlayerOrSelf();
			target->SetMaxHealth(hp);
			target->SetHealth(hp);
			ModifyMenuE(player, item);
			break;
		}
		case 80:
		{
			char* spring = strtok((char*)code, " ");
			char* summer = strtok(NULL, " ");
			char* fall = strtok(NULL, " ");
			char* winter = strtok(NULL , " ");
			int32 sp, su, fa, wi;
			sp = atol(spring);
			su = atol(summer);
			fa = atol(fall);
			wi = atol(winter);
			WorldDatabase.DirectPExecute("INSERT INTO `game_weather` VALUES ('%u','%u','%u','%u','%u','%u','%u','%u','%u','%u','%u','%u','%u', '')", player->GetZoneId(), sp, sp, sp, su, su, su, fa, fa, fa, wi, wi, wi);
			ChatHandler(player->GetSession()).PSendSysMessage("ZoneWeather add to zone: %u", player->GetZoneId());
			Sixth(player, item);
			break;
		}
		case 81:
		{
			uint32 entry = atol(code);
			ItemDisplayInfoEntry const * info = sItemDisplayInfoStore.LookupEntry(entry);
			if (info == NULL)
			{
				player->GetSession()->SendNotification("displayid dont exist");
				Third(player, item);
			}
			else
				ItemdisplayTemp(player, item, code);
			break;
		}
		case 82:
		{
			uint32 entry = atol(code);
			ItemTemplate const*Info = sObjectMgr->GetItemTemplate(entry);
			if (!Info)
			{
				player->GetSession()->SendNotification("no item found");
				Third(player, item);
			}
			else
				ItemTemplateMenu(player, item, code);
			break;
		}
		case 83:
		{
			
			char * first = strtok((char*)code, " ");
			char * second = strtok(nullptr, " ");
			ObjectGuid::LowType lowguid = 0;
			float x = 0.0f, y = 0.0f, z = 0.0f;
			uint8 select = atol(first);
				switch (select)
				{
				case 1:
					x = atof(second);
					break;
				case 2:
					y = atof(second);
					break;
				case 3:
					z = atof(second);
					break;
				}
				//player->GetSession()->SendNotification("%u %f %f %f", select, x, y, z);
				
			Creature* creature = ChatHandler(player->GetSession()).getSelectedCreature();

			if (creature)
				lowguid = creature->GetSpawnId();

			// Attempting creature load from DB data
			CreatureData const* data = sObjectMgr->GetCreatureData(lowguid);
			if (!data)
			{
				ChatHandler(player->GetSession()).PSendSysMessage(LANG_COMMAND_CREATGUIDNOTFOUND, lowguid);
				ChatHandler(player->GetSession()).SetSentErrorMessage(true);
				return;
			}

			if (player->GetMapId() != data->spawnPoint.GetMapId())
			{
				ChatHandler(player->GetSession()).PSendSysMessage(LANG_COMMAND_CREATUREATSAMEMAP, lowguid);
				ChatHandler(player->GetSession()).SetSentErrorMessage(true);
				return;
			}

			// update position in memory
			const_cast<CreatureData*>(data)->spawnPoint.Relocate(*player);

			// update position in DB
			PreparedStatement* stmt = WorldDatabase.GetPreparedStatement(WORLD_UPD_CREATURE_POSITION);
			stmt->setFloat(0, creature->GetPositionX() + x);
			stmt->setFloat(1, creature->GetPositionY() + y);
			stmt->setFloat(2, creature->GetPositionZ() + z);
			stmt->setFloat(3, creature->GetOrientation());
			stmt->setUInt32(4, lowguid);
			WorldDatabase.Execute(stmt);

			// respawn selected creature at the new location
			if (creature)
			{
				if (creature->IsAlive())
					creature->setDeathState(JUST_DIED);
				creature->Respawn(true);
				if (!creature->GetRespawnCompatibilityMode())
					creature->AddObjectToRemoveList();
			}

			ChatHandler(player->GetSession()).PSendSysMessage(LANG_COMMAND_CREATUREMOVED);
			Third(player, item);
			break;
		}
		case 200:
		{
			uint32 time = atol(code), option = 0, exitcode = 0;
			string reson = " ";
			sWorld->ShutdownServ(time, option, exitcode, reson);
			//return ShutdownServer(ChatHandler(player->GetSession())* handler, code, uint32 shutdownMask, int32 defaultExitCode)
			break;
		}
		case 201:
		{
			uint32 phase = atol(code);
			player->SetPhaseMask(phase, true);
			Second(player, item);
			break;
		}

	}
};
};
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
			"`guid` INT(11) NULL DEFAULT NULL,"
			"`map` INT(11) NULL DEFAULT NULL,"
			"`x` FLOAT NULL DEFAULT NULL,"
			"`y` FLOAT NULL DEFAULT NULL,"
			"`z` FLOAT NULL DEFAULT NULL,"
			"`X2` FLOAT NULL DEFAULT NULL,"
			"`Y2` FLOAT NULL DEFAULT NULL"
			")"
			"COLLATE = 'latin1_swedish_ci'"
			"ENGINE = InnoDB;";
		//const char* sql3 =
			//"CREATE TABLE `characters_gold_bank` ("
			//"`guid` INT(11) UNSIGNED NOT NULL,"
			//"`gold` INT(11) UNSIGNED NULL DEFAULT NULL,"
			//"UNIQUE INDEX `guid_2` (`guid`),"
			//"INDEX `guid` (`guid`)"
			//")"
			//"COLLATE = 'utf8_general_ci'"
			//"ENGINE = InnoDB;";

		CharacterDatabase.DirectExecute(sql);
		CharacterDatabase.DirectExecute(sql2);
		//CharacterDatabase.DirectExecute(sql3);
	}
	void OnLogin(Player* player, bool firstLogin)
	{
		CharacterDatabase.PExecute("INSERT INTO `start` (guid, xsor, ysor, item, spellcast) VALUES(%u, 1, 1, 0, 0) ON DUPLICATE KEY UPDATE xsor = xsor;", player->GetGUID());
		CharacterDatabase.PExecute("INSERT INTO `teleport` (guid, map, `x`,`y`,z,X2,y2) VALUES(%u, 0, 0, 0,0,0,0) ON DUPLICATE KEY UPDATE `map` = `map`;", player->GetGUID());
		CharacterDatabase.PExecute("INSERT INTO characters_gold_bank (guid, gold) VALUES(%u, 0) ON DUPLICATE KEY UPDATE gold=gold;", player->GetGUID());
	}

};
void AddSC_GMSTONE2()
{
	new ADDGMTOOLS();
	new GMSTONE2();
	new DBedit();
}