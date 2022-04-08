#ifndef _PlayerbotTextMgr_H
#define _PlayerbotTextMgr_H

#include "Common.h"
#include "PlayerbotAIBase.h"

#define BOT_TEXT(name) sPlayerbotTextMgr.GetBotText(name)
#define BOT_TEXT2(name, replace) sPlayerbotTextMgr.GetBotText(name, replace)

using namespace std;

struct BotTextEntry
{
    BotTextEntry(std::string name, std::map<int32, std::string> text, uint32 say_type, uint32 reply_type) : m_name(name), m_text(text), m_sayType(say_type), m_replyType(reply_type) {}
    std::string m_name;
    std::map<int32, std::string> m_text;
    uint32 m_sayType;
    uint32 m_replyType;
};

struct ChatReplyData
{
    ChatReplyData(uint32 guid, uint32 type, std::string chat) : m_guid(guid), m_type(type), m_chat(chat) {}
    uint32 m_type, m_guid = 0;
    std::string m_chat = "";
};

struct ChatQueuedReply
{
    ChatQueuedReply(uint32 type, uint32 guid1, uint32 guid2, std::string msg, std::string chanName, std::string name, time_t time) : m_type(type), m_guid1(guid1), m_guid2(guid2), m_msg(msg), m_chanName(chanName), m_name(name), m_time(time) {}
    uint32 m_type;
    uint32 m_guid1;
    uint32 m_guid2;
    std::string m_msg;
    std::string m_chanName;
    std::string m_name;
    time_t m_time;
};

enum ChatReplyType
{
    REPLY_NOT_UNDERSTAND,
    REPLY_GRUDGE,
    REPLY_VICTIM,
    REPLY_ATTACKER,
    REPLY_HELLO,
    REPLY_NAME,
    REPLY_ADMIN_ABUSE
};

class PlayerbotTextMgr
{
    public:
        PlayerbotTextMgr();
        virtual ~PlayerbotTextMgr();
        static PlayerbotTextMgr& instance()
        {
            static PlayerbotTextMgr instance;
            return instance;
        }

	public:
        string GetBotText(string name, map<string, string> placeholders);
        string GetBotText(string name);
        string GetBotText(ChatReplyType replyType, map<string, string> placeholders);
        string GetBotText(ChatReplyType replyType, string name);
        bool GetBotText(string name, string& text);
        bool GetBotText(string name, string& text, map<string, string> placeholders);
        void LoadBotTexts();
        void LoadBotTextChance();

        void replaceAll(std::string& str, const std::string& from, const std::string& to);
        bool rollTextChance(string text);

        int32 GetLocalePriority();
        void AddLocalePriority(int32 locale);
        void ResetLocalePriority();

    private:
        map<string, vector<BotTextEntry>> botTexts;
        map<string, uint32 > botTextChance;
        uint32 botTextLocalePriority[MAX_LOCALE];
};

#define sPlayerbotTextMgr PlayerbotTextMgr::instance()

#endif
