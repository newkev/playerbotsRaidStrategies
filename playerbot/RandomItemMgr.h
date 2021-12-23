#ifndef _RandomItemMgr_H
#define _RandomItemMgr_H

#include "Common.h"
#include "PlayerbotAIBase.h"
#include "AiFactory.h"
#ifdef CMANGOS
#include "Entities/Player.h"
#endif
#ifdef MANGOS
#include "Object/Player.h"
#endif

using namespace std;

enum RandomItemType
{
    RANDOM_ITEM_GUILD_TASK,
    RANDOM_ITEM_GUILD_TASK_REWARD_EQUIP_BLUE,
    RANDOM_ITEM_GUILD_TASK_REWARD_EQUIP_GREEN,
    RANDOM_ITEM_GUILD_TASK_REWARD_TRADE,
    RANDOM_ITEM_GUILD_TASK_REWARD_TRADE_RARE
};

#ifdef MANGOSBOT_TWO
#define MAX_STAT_SCALES 32
#endif

enum ItemSource
{
    ITEM_SOURCE_NONE,
    ITEM_SOURCE_DROP,
    ITEM_SOURCE_VENDOR,
    ITEM_SOURCE_QUEST,
    ITEM_SOURCE_CRAFT,
    ITEM_SOURCE_PVP
};

struct WeightScaleInfo
{
    uint32 id;
    string name;
};

struct WeightScaleStat
{
    string stat;
    uint32 weight;
};

struct StatWeight
{
    uint32 id;
    uint32 weight;
};

struct ItemInfoEntry
{
    ItemInfoEntry() : minLevel(0), source(0), sourceId(0), team(0), repRank(0), repFaction(0), quality(0), slot(0), itemId(0)
    {
        for (int i = 1; i <= MAX_STAT_SCALES; ++i)
        {
            weights[i] = 0;
        }
    }

    map<uint32, uint32> weights;
    uint32 minLevel;
    uint32 source;
    uint32 sourceId;
    uint32 team;
    uint32 repRank;
    uint32 repFaction;
    uint32 quality;
    uint32 slot;
    uint32 itemId;
};

typedef vector<WeightScaleStat> WeightScaleStats;
//typedef map<WeightScaleInfo, WeightScaleStats> WeightScaleList;

struct WeightScale
{
    WeightScaleInfo info;
    WeightScaleStats stats;
};

//typedef map<uint32, WeightScale> WeightScales;

class RandomItemPredicate
{
public:
    virtual ~RandomItemPredicate(){};
    virtual bool Apply(ItemPrototype const* proto) = 0;
};

typedef vector<uint32> RandomItemList;
typedef map<RandomItemType, RandomItemList> RandomItemCache;

class BotEquipKey
{
public:
    uint32 level;
    uint8 clazz;
    uint8 slot;
    uint32 quality;
    uint64 key;

public:
    BotEquipKey() : level(0), clazz(0), slot(0), quality(0), key(GetKey()) {}
    BotEquipKey(uint32 level, uint8 clazz, uint8 slot, uint32 quality) : level(level), clazz(clazz), slot(slot), quality(quality), key(GetKey()) {}
    BotEquipKey(BotEquipKey const& other)  : level(other.level), clazz(other.clazz), slot(other.slot), quality(other.quality), key(GetKey()) {}

private:
    uint64 GetKey();

public:
    bool operator< (const BotEquipKey& other) const
    {
        return other.key < this->key;
    }
};

typedef map<BotEquipKey, RandomItemList> BotEquipCache;

class RandomItemMgr
{
    public:
        RandomItemMgr();
        virtual ~RandomItemMgr();
        static RandomItemMgr& instance()
        {
            static RandomItemMgr instance;
            return instance;
        }

	public:
        void Init();
        void InitAfterAhBot();
        static bool HandleConsoleCommand(ChatHandler* handler, char const* args);
        RandomItemList Query(uint32 level, RandomItemType type, RandomItemPredicate* predicate);
        RandomItemList Query(uint32 level, uint8 clazz, uint8 slot, uint32 quality);
        uint32 GetUpgrade(Player* player, std::string spec, uint8 slot, uint32 quality, uint32 itemId);
        vector<uint32> GetUpgradeList(Player* player, std::string spec, uint8 slot, uint32 quality, uint32 itemId, uint32 amount = 1);
        bool HasStatWeight(uint32 itemId);
        uint32 GetMinLevelFromCache(uint32 itemId);
        uint32 GetStatWeight(Player* player, uint32 itemId);
        uint32 GetLiveStatWeight(Player* player, uint32 itemId);
        uint32 GetRandomItem(uint32 level, RandomItemType type, RandomItemPredicate* predicate = NULL);
        uint32 GetAmmo(uint32 level, uint32 subClass);
        uint32 GetRandomPotion(uint32 level, uint32 effect);
        uint32 GetRandomFood(uint32 level, uint32 category);
        uint32 GetFood(uint32 level, uint32 category);
        uint32 GetRandomTrade(uint32 level);
        uint32 CalculateStatWeight(uint8 playerclass, uint8 spec, ItemPrototype const* proto);
        uint32 CalculateSingleStatWeight(uint8 playerclass, uint8 spec, std::string stat, uint32 value);
        bool CanEquipArmor(uint8 clazz, uint32 level, ItemPrototype const* proto);
        bool ShouldEquipArmorForSpec(uint8 playerclass, uint8 spec, ItemPrototype const* proto);
        bool CanEquipWeapon(uint8 clazz, ItemPrototype const* proto);
        bool ShouldEquipWeaponForSpec(uint8 playerclass, uint8 spec, ItemPrototype const* proto);
        float GetItemRarity(uint32 itemId);
        uint32 GetQuestIdForItem(uint32 itemId);
        vector<uint32> GetQuestIdsForItem(uint32 itemId);

    private:
        void BuildRandomItemCache();
        void BuildEquipCache();
        void BuildItemInfoCache();
        void BuildAmmoCache();
        void BuildFoodCache();
        void BuildPotionCache();
        void BuildTradeCache();
        void BuildRarityCache();
        bool CanEquipItem(BotEquipKey key, ItemPrototype const* proto);
        bool CanEquipItemNew(ItemPrototype const* proto);
        void AddItemStats(uint32 mod, uint8 &sp, uint8 &ap, uint8 &tank);
        bool CheckItemStats(uint8 clazz, uint8 sp, uint8 ap, uint8 tank);

    private:
        map<uint32, RandomItemCache> randomItemCache;
        map<RandomItemType, RandomItemPredicate*> predicates;
        BotEquipCache equipCache;
        map<EquipmentSlots, set<InventoryType> > viableSlots;
        map<uint32, map<uint32, uint32> > ammoCache;
        map<uint32, map<uint32, vector<uint32> > > potionCache;
        map<uint32, map<uint32, vector<uint32> > > foodCache;
        map<uint32, vector<uint32> > tradeCache;
        map<uint32, float> rarityCache;
        map<uint32, WeightScale> m_weightScales[MAX_CLASSES];
        map<string, uint32 > weightStatLink;
        map<string, uint32 > weightRatingLink;
        map<uint32, ItemInfoEntry*> itemInfoCache;
};

#define sRandomItemMgr RandomItemMgr::instance()

#endif
