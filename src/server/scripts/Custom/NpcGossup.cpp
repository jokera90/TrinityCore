#include "ScriptedGossip.h"
class NpcTestGossip : public CreatureScript
{
public:
	NpcTestGossip() : CreatureScript("WarTest") {}
	class NpcTestGossipAI : public ScriptedAI
	{
		public:
			NpcTestGossipAI(Creature* creature) : ScriptedAI(creature) {}
			bool GossipHello(Player*player) override
			{
				AddGossipItemFor(player, 0, "1", 0, 1);
				AddGossipItemFor(player, 0, "2", 0, 1);
				player->PlayerTalkClass->SendGossipMenu(2, me->GetGUID());
				return true;
				
			}
			bool GossipSelect(Player* player, uint32 menuid, uint32 gossipmenuid)
			{
				uint32 sender = player->PlayerTalkClass->GetGossipOptionSender(menuid);
				uint32 action = player->PlayerTalkClass->GetGossipOptionAction(gossipmenuid);
				return OnGossipSelect(player, me, sender, action);
			}
			bool OnGossipSelect(Player*player, Creature* creature, uint32 sender, uint32 action)
			{
				switch (action)
				{
				case 1:
				{
					me->Say("GROOR", LANG_UNIVERSAL, me);
				}
				}
				return true;
			}
	};
	CreatureAI *GetAI(Creature*creature) const override
	{
		return new NpcTestGossipAI(creature);
	}
};
void AddSC_NpcTestGossip()
{
	new NpcTestGossip();
}