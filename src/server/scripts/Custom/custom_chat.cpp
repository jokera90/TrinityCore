#include "RBAC.h"
#include "Chat.h"
#include "Language.h"
#include "Guild.h"
#include "GuildMgr.h"

class custom_chat : public CommandScript
{
public:
	custom_chat() : CommandScript("custom_chat") {}

	std::vector<ChatCommand> GetCommands() const override
	{
		static std::vector<ChatCommand> customchat =
		{
			{"custom",rbac::RBAC_PERM_COMMAND_RELOAD,true,&HandlerCustomChat,"" },
		};
		return customchat;
	}
	static bool HandlerCustomChat(ChatHandler* handler, const char* args)
	{
		if (!*args)
			return false;
		Player* target;
		if (!handler->extractPlayerTarget(*args != '"' ? (char*)args : nullptr, &target))
			return false;

		char *tailStr = *args != '"' ? strtok(nullptr, "") : (char*)args;

		if (!tailStr)
			return false;

		char *guildStr = handler->extractQuotedArg(tailStr);

		if (!guildStr)
			return false;

		std::string guildName = guildStr;

		if (target->GetGuildId())
		{
			handler->SendSysMessage(LANG_PLAYER_IN_GUILD);
			return true;
		}
		Guild* guild = new Guild;
		if (!guild->Create(target, guildName))
		{
			delete guild;
			handler->SendSysMessage(LANG_GUILD_NOT_CREATED);
			handler->SetSentErrorMessage(true);
		}
		sGuildMgr->AddGuild(guild);

		handler->PSendSysMessage("%s", guildStr);
		handler->PSendSysMessage("test %s and %u", target->GetName().c_str(), target->GetGUID());
		handler->PSendSysMessage("%s", tailStr);
		return true;
	}
};
void AddSC_custom_chatcommandscript()
{
	new custom_chat();
}