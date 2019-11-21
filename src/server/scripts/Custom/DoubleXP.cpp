#include "Player.h"
#include "Chat.h"
#include "World.h"
#include "boost/date_time.hpp"
#include "Config.h"


class DoubleXP : public PlayerScript
{
public:
	DoubleXP() : PlayerScript("weekendoubledXP") {}

	void OnGiveXP(Player* player, uint32& amount, Unit* victim) override
	{
		if (sConfigMgr->GetBoolDefault("DoubleXP.enabled", true))
		{
			boost::gregorian::date date(boost::gregorian::day_clock::local_day());
			auto day = date.day_of_week();
			if (day == boost::date_time::Monday ||
				day == boost::date_time::Thursday ||
				day == boost::date_time::Wednesday ||
				day == boost::date_time::Tuesday)
			{
				amount = amount * 10;
			}
			else  if (day == boost::date_time::Friday ||
				day == boost::date_time::Saturday ||
				day == boost::date_time::Saturday)
				amount = amount * 2;
		}
	}
	void OnLogin(Player* player, bool firstlogin)
	{
		if (sConfigMgr->GetBoolDefault("DoubleXP.enabled", true))
		{
			boost::gregorian::date date(boost::gregorian::day_clock::local_day());
			auto day = date.day_of_week();
			if (day == boost::date_time::Monday ||
				day == boost::date_time::Thursday ||
				day == boost::date_time::Wednesday ||
				day == boost::date_time::Tuesday)
			{
				ChatHandler(player->GetSession()).PSendSysMessage("TenXP is going now!");
			}
			else if (day == boost::date_time::Friday ||
				day == boost::date_time::Saturday ||
				day == boost::date_time::Saturday)
				ChatHandler(player->GetSession()).PSendSysMessage("DoubleXP is going now!");
		}
	}

};
void AddSC_DoubleXP()
{
	new DoubleXP();
}