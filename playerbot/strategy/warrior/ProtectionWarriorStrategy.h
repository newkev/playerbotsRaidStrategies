#pragma once
#include "WarriorStrategy.h"

namespace ai
{
    class ProtectionWarriorPlaceholderStrategy : public SpecPlaceholderStrategy
    {
    public:
        ProtectionWarriorPlaceholderStrategy(PlayerbotAI* ai) : SpecPlaceholderStrategy(ai) {}
        int GetType() override { return STRATEGY_TYPE_TANK | STRATEGY_TYPE_MELEE; }
        string getName() override { return "protection"; }
    };

    class ProtectionWarriorStrategy : public WarriorStrategy
    {
    public:
        ProtectionWarriorStrategy(PlayerbotAI* ai);

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;

        virtual NextAction** GetDefaultCombatActions() override;
    };

    class ProtectionWarriorPveStrategy : public ProtectionWarriorStrategy
    {
    public:
        ProtectionWarriorPveStrategy(PlayerbotAI* ai) : ProtectionWarriorStrategy(ai) {}
        std::string getName() override { return "protection pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;
    };

    class ProtectionWarriorPvpStrategy : public ProtectionWarriorStrategy
    {
    public:
        ProtectionWarriorPvpStrategy(PlayerbotAI* ai) : ProtectionWarriorStrategy(ai) {}
        std::string getName() override { return "protection pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;
    };

    class ProtectionWarriorRaidStrategy : public ProtectionWarriorStrategy
    {
    public:
        ProtectionWarriorRaidStrategy(PlayerbotAI* ai) : ProtectionWarriorStrategy(ai) {}
        std::string getName() override { return "protection raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitReactionTriggers(std::list<TriggerNode*>& triggers) override;
        void InitDeadTriggers(std::list<TriggerNode*>& triggers) override;
    };

    class ProtectionWarriorAoeStrategy : public WarriorAoeStrategy
    {
    public:
        ProtectionWarriorAoeStrategy(PlayerbotAI* ai) : WarriorAoeStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    class ProtectionWarriorAoePveStrategy : public ProtectionWarriorAoeStrategy
    {
    public:
        ProtectionWarriorAoePveStrategy(PlayerbotAI* ai) : ProtectionWarriorAoeStrategy(ai) {}
        string getName() override { return "aoe protection pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    class ProtectionWarriorAoePvpStrategy : public ProtectionWarriorAoeStrategy
    {
    public:
        ProtectionWarriorAoePvpStrategy(PlayerbotAI* ai) : ProtectionWarriorAoeStrategy(ai) {}
        string getName() override { return "aoe protection pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    class ProtectionWarriorAoeRaidStrategy : public ProtectionWarriorAoeStrategy
    {
    public:
        ProtectionWarriorAoeRaidStrategy(PlayerbotAI* ai) : ProtectionWarriorAoeStrategy(ai) {}
        string getName() override { return "aoe protection raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    class ProtectionWarriorBuffStrategy : public WarriorBuffStrategy
    {
    public:
        ProtectionWarriorBuffStrategy(PlayerbotAI* ai) : WarriorBuffStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    class ProtectionWarriorBuffPveStrategy : public ProtectionWarriorBuffStrategy
    {
    public:
        ProtectionWarriorBuffPveStrategy(PlayerbotAI* ai) : ProtectionWarriorBuffStrategy(ai) {}
        string getName() override { return "buff protection pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    class ProtectionWarriorBuffPvpStrategy : public ProtectionWarriorBuffStrategy
    {
    public:
        ProtectionWarriorBuffPvpStrategy(PlayerbotAI* ai) : ProtectionWarriorBuffStrategy(ai) {}
        string getName() override { return "buff protection pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    class ProtectionWarriorBuffRaidStrategy : public ProtectionWarriorBuffStrategy
    {
    public:
        ProtectionWarriorBuffRaidStrategy(PlayerbotAI* ai) : ProtectionWarriorBuffStrategy(ai) {}
        string getName() override { return "buff protection raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    class ProtectionWarriorCcStrategy : public WarriorCcStrategy
    {
    public:
        ProtectionWarriorCcStrategy(PlayerbotAI* ai) : WarriorCcStrategy(ai) {}

    protected:
        virtual void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        virtual void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    class ProtectionWarriorCcPveStrategy : public ProtectionWarriorCcStrategy
    {
    public:
        ProtectionWarriorCcPveStrategy(PlayerbotAI* ai) : ProtectionWarriorCcStrategy(ai) {}
        string getName() override { return "cc protection pve"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    class ProtectionWarriorCcPvpStrategy : public ProtectionWarriorCcStrategy
    {
    public:
        ProtectionWarriorCcPvpStrategy(PlayerbotAI* ai) : ProtectionWarriorCcStrategy(ai) {}
        string getName() override { return "cc protection pvp"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };

    class ProtectionWarriorCcRaidStrategy : public ProtectionWarriorCcStrategy
    {
    public:
        ProtectionWarriorCcRaidStrategy(PlayerbotAI* ai) : ProtectionWarriorCcStrategy(ai) {}
        string getName() override { return "cc protection raid"; }

    private:
        void InitCombatTriggers(std::list<TriggerNode*>& triggers) override;
        void InitNonCombatTriggers(std::list<TriggerNode*>& triggers) override;
    };
}