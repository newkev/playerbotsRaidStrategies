#pragma once
#include "WarriorStrategy.h"

namespace ai
{
    class ArmsWarriorPlaceholderStrategy : public SpecPlaceholderStrategy
    {
    public:
        ArmsWarriorPlaceholderStrategy(PlayerbotAI* ai) : SpecPlaceholderStrategy(ai) {}
        int GetType() override { return STRATEGY_TYPE_COMBAT | STRATEGY_TYPE_DPS | STRATEGY_TYPE_MELEE; }
        string getName() override { return "arms"; }
    };

    class ArmsWarriorStrategy : public WarriorStrategy
    {
    public:
        ArmsWarriorStrategy(PlayerbotAI* ai);

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;

        virtual NextAction** GetDefaultCombatActions() override;
    };

    class ArmsWarriorPveStrategy : public ArmsWarriorStrategy
    {
    public:
        ArmsWarriorPveStrategy(PlayerbotAI* ai) : ArmsWarriorStrategy(ai) {}
        std::string getName() override { return "arms pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;
    };

    class ArmsWarriorPvpStrategy : public ArmsWarriorStrategy
    {
    public:
        ArmsWarriorPvpStrategy(PlayerbotAI* ai) : ArmsWarriorStrategy(ai) {}
        std::string getName() override { return "arms pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;
    };

    class ArmsWarriorRaidStrategy : public ArmsWarriorStrategy
    {
    public:
        ArmsWarriorRaidStrategy(PlayerbotAI* ai) : ArmsWarriorStrategy(ai) {}
        std::string getName() override { return "arms raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;
    };

    class ArmsWarriorAoeStrategy : public WarriorAoeStrategy
    {
    public:
        ArmsWarriorAoeStrategy(PlayerbotAI* ai) : WarriorAoeStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    class ArmsWarriorAoePveStrategy : public ArmsWarriorAoeStrategy
    {
    public:
        ArmsWarriorAoePveStrategy(PlayerbotAI* ai) : ArmsWarriorAoeStrategy(ai) {}
        string getName() override { return "aoe arms pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    class ArmsWarriorAoePvpStrategy : public ArmsWarriorAoeStrategy
    {
    public:
        ArmsWarriorAoePvpStrategy(PlayerbotAI* ai) : ArmsWarriorAoeStrategy(ai) {}
        string getName() override { return "aoe arms pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    class ArmsWarriorAoeRaidStrategy : public ArmsWarriorAoeStrategy
    {
    public:
        ArmsWarriorAoeRaidStrategy(PlayerbotAI* ai) : ArmsWarriorAoeStrategy(ai) {}
        string getName() override { return "aoe arms raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    class ArmsWarriorBuffStrategy : public WarriorBuffStrategy
    {
    public:
        ArmsWarriorBuffStrategy(PlayerbotAI* ai) : WarriorBuffStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    class ArmsWarriorBuffPveStrategy : public ArmsWarriorBuffStrategy
    {
    public:
        ArmsWarriorBuffPveStrategy(PlayerbotAI* ai) : ArmsWarriorBuffStrategy(ai) {}
        string getName() override { return "buff arms pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    class ArmsWarriorBuffPvpStrategy : public ArmsWarriorBuffStrategy
    {
    public:
        ArmsWarriorBuffPvpStrategy(PlayerbotAI* ai) : ArmsWarriorBuffStrategy(ai) {}
        string getName() override { return "buff arms pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    class ArmsWarriorBuffRaidStrategy : public ArmsWarriorBuffStrategy
    {
    public:
        ArmsWarriorBuffRaidStrategy(PlayerbotAI* ai) : ArmsWarriorBuffStrategy(ai) {}
        string getName() override { return "buff arms raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    class ArmsWarriorCcStrategy : public WarriorCcStrategy
    {
    public:
        ArmsWarriorCcStrategy(PlayerbotAI* ai) : WarriorCcStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    class ArmsWarriorCcPveStrategy : public ArmsWarriorCcStrategy
    {
    public:
        ArmsWarriorCcPveStrategy(PlayerbotAI* ai) : ArmsWarriorCcStrategy(ai) {}
        string getName() override { return "cc arms pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    class ArmsWarriorCcPvpStrategy : public ArmsWarriorCcStrategy
    {
    public:
        ArmsWarriorCcPvpStrategy(PlayerbotAI* ai) : ArmsWarriorCcStrategy(ai) {}
        string getName() override { return "cc arms pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    class ArmsWarriorCcRaidStrategy : public ArmsWarriorCcStrategy
    {
    public:
        ArmsWarriorCcRaidStrategy(PlayerbotAI* ai) : ArmsWarriorCcStrategy(ai) {}
        string getName() override { return "cc arms raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };
}