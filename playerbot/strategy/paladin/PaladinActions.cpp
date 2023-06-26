#include "botpch.h"
#include "../../playerbot.h"
#include "PaladinActions.h"

using namespace ai;

bool CastPaladinAuraAction::Execute(Event& event)
{
    vector<std::string> altAuras;
    vector<std::string> haveAuras;
    altAuras.push_back("devotion aura");
    altAuras.push_back("retribution aura");
    altAuras.push_back("concentration aura");
    altAuras.push_back("sanctity aura");
    altAuras.push_back("shadow resistance aura");
    altAuras.push_back("fire resistance aura");
    altAuras.push_back("frost resistance aura");
    altAuras.push_back("crusader aura");

    for (auto aura : altAuras)
    {
        if (AI_VALUE2(uint32, "spell id", aura))
            haveAuras.push_back(aura);
    }

    if (haveAuras.empty())
    {
        return false;
    }

    for (auto aura : haveAuras)
    {
        if (!ai->HasAura(aura, bot))
        {
            uint32 spellDuration = sPlayerbotAIConfig.globalCoolDown;
            bool executed = ai->CastSpell(aura, bot, nullptr, false);
            if (executed)
            {
                SetDuration(1.0f);
            }

            return executed;
        }
    }

    return false;
}

Unit* CastBlessingAction::GetTarget()
{
    return bot;
}

bool CastBlessingAction::isPossible()
{
    Unit* target = GetTarget();
    if (target)
    {
        std::string blessing = GetBlessingForTarget(target);
        if (!blessing.empty())
        {
            SetSpellName(blessing);
            return CastSpellAction::isPossible();
        }
    }

    return false;
}

std::string CastBlessingAction::GetBlessingForTarget(Unit* target)
{
    std::string chosenBlessing = "";
    if (target)
    {
        std::vector<std::string> possibleBlessings = GetPossibleBlessingsForTarget(target);
        for (const std::string& blessing : possibleBlessings)
        {
            // Don't cast greater buffs on possible tank classes (ask ile why :D)
            bool tryCastGreater = greater;
            if (tryCastGreater && target->IsPlayer())
            {
                const uint8 playerClass = ((Player*)target)->getClass();
#ifdef MANGOSBOT_TWO
                tryCastGreater = playerClass == CLASS_PALADIN || playerClass == CLASS_WARRIOR || playerClass == CLASS_DRUID || playerClass == CLASS_DEATH_KNIGHT;
#else
                tryCastGreater = playerClass == CLASS_PALADIN || playerClass == CLASS_WARRIOR || playerClass == CLASS_DRUID;
#endif
            }

            const std::string greaterBlessing = "greater " + blessing;
            if ((tryCastGreater || !ai->HasAura(blessing, target)) && !ai->HasAura(greaterBlessing, target))
            {
                if ((tryCastGreater && ai->CanCastSpell(greaterBlessing, target, 0, nullptr, true)) ||
                    (!tryCastGreater && ai->CanCastSpell(blessing, target, 0, nullptr, true)))
                {
                    chosenBlessing = tryCastGreater ? greaterBlessing : blessing;
                    break;
                }
            }
        }
    }

    return chosenBlessing;
}

std::vector<std::string> CastPveBlessingAction::GetPossibleBlessingsForTarget(Unit* target) const
{
    std::vector<std::string> blessings;
    if (target && target->IsPlayer())
    {
        Player* player = (Player*)target;
        if (ai->IsTank(player))
        {
            blessings = { "blessing of kings", "blessing of might", "blessing of sanctuary", "blessing of light" };
        }
        else if (ai->IsHeal(player))
        {
            blessings = { "blessing of wisdom", "blessing of kings", "blessing of light" };
        }
        else
        {
            blessings = { "blessing of might", "blessing of kings", "blessing of light" };
        }
    }

    return blessings;
}

std::vector<std::string> CastPvpBlessingAction::GetPossibleBlessingsForTarget(Unit* target) const
{
    std::vector<std::string> blessings;
    if (target && target->IsPlayer())
    {
        Player* player = (Player*)target;
        if (ai->IsTank(player))
        {
            blessings = { "blessing of kings", "blessing of might", "blessing of sanctuary", "blessing of light" };
        }
        else if (ai->IsHeal(player))
        {
            blessings = { "blessing of wisdom", "blessing of kings", "blessing of light" };
        }
        else
        {
            blessings = { "blessing of might", "blessing of kings", "blessing of light" };
        }
    }

    return blessings;
}

std::vector<std::string> CastRaidBlessingAction::GetPossibleBlessingsForTarget(Unit* target) const
{
    std::vector<std::string> blessings;
    if (target && target->IsPlayer())
    {
        Player* player = (Player*)target;
        if (ai->IsTank(player))
        {
            blessings = { "blessing of kings", "blessing of might", "blessing of sanctuary", "blessing of light" };
        }
        else if (ai->IsHeal(player))
        {
            blessings = { "blessing of wisdom", "blessing of kings", "blessing of salvation", "blessing of light" };
        }
        else
        {
            blessings = { "blessing of might", "blessing of kings", "blessing of salvation", "blessing of light" };
        }
    }

    return blessings;
}

Unit* CastBlessingOnPartyAction::GetTarget()
{
    vector<std::string> altBlessings;
    vector<std::string> haveBlessings;
    altBlessings.push_back("blessing of might");
    altBlessings.push_back("blessing of wisdom");
    altBlessings.push_back("blessing of kings");
    altBlessings.push_back("blessing of sanctuary");
    altBlessings.push_back("blessing of salvation");
    altBlessings.push_back("blessing of light");

    for (auto blessing : altBlessings)
    {
        if (AI_VALUE2(uint32, "spell id", blessing))
        {
            haveBlessings.push_back(blessing);
            haveBlessings.push_back("greater " + blessing);
        }
    }

    if (haveBlessings.empty())
    {
        return nullptr;
    }

    std::string blessList = "";
    for (auto blessing : haveBlessings)
    {
        blessList += blessing;
        if (blessing != haveBlessings[haveBlessings.size() - 1])
        {
            blessList += ",";
        }
    }

    return AI_VALUE2(Unit*, "party member without my aura", blessList);
}

bool CastBlessingOnPartyAction::isPossible()
{
    Unit* target = GetTarget();
    if (target)
    {
        std::string blessing = GetBlessingForTarget(target);
        if (!blessing.empty())
        {
            SetSpellName(blessing);
            return CastSpellAction::isPossible();
        }
    }

    return false;
}

std::string CastBlessingOnPartyAction::GetBlessingForTarget(Unit* target)
{
    std::string chosenBlessing = "";
    if (target)
    {
        std::vector<std::string> possibleBlessings = GetPossibleBlessingsForTarget(target);
        for (const std::string& blessing : possibleBlessings)
        {
            const std::string greaterBlessing = "greater " + blessing;
            if ((greater || !ai->HasAura(blessing, target)) && !ai->HasAura(greaterBlessing, target))
            {
                if((greater && ai->CanCastSpell(greaterBlessing, target, 0, nullptr, true)) ||
                   (!greater && ai->CanCastSpell(blessing, target, 0, nullptr, true)))
                {
                    chosenBlessing = greater ? greaterBlessing : blessing;
                    break;
                }
            }
        }
    }

    return chosenBlessing;
}

std::vector<std::string> CastPveBlessingOnPartyAction::GetPossibleBlessingsForTarget(Unit* target) const
{
    std::vector<std::string> blessings;
    if (target && target->IsPlayer())
    {
        Player* player = (Player*)target;
        if (ai->IsTank(player))
        {
            blessings = { "blessing of kings", "blessing of might", "blessing of sanctuary", "blessing of light" };
        }
        else if (ai->IsHeal(player))
        {
            blessings = { "blessing of wisdom", "blessing of kings", "blessing of light" };
        }
        else if (ai->IsRanged(player))
        {
            if (player->getClass() == CLASS_HUNTER)
            {
                blessings = { "blessing of wisdom", "blessing of kings", "blessing of might", "blessing of light" };
            }
            else
            {
                blessings = { "blessing of kings", "blessing of wisdom", "blessing of light" };
            }
        }
        else
        {
            blessings = { "blessing of might", "blessing of kings", "blessing of light" };
        }
    }
    else
    {
        // Blessings for pets
        blessings = { "blessing of might", "blessing of kings", "blessing of light" };
    }

    return blessings;
}

std::vector<std::string> CastPvpBlessingOnPartyAction::GetPossibleBlessingsForTarget(Unit* target) const
{
    std::vector<std::string> blessings;
    if (target && target->IsPlayer())
    {
        Player* player = (Player*)target;
        if (ai->IsTank(player))
        {
            blessings = { "blessing of kings", "blessing of might", "blessing of sanctuary", "blessing of light" };
        }
        else if (ai->IsHeal(player))
        {
            blessings = { "blessing of wisdom", "blessing of kings", "blessing of light" };
        }
        else if (ai->IsRanged(player))
        {
            if (player->getClass() == CLASS_HUNTER)
            {
                blessings = { "blessing of wisdom", "blessing of kings", "blessing of might", "blessing of light" };
            }
            else
            {
                blessings = { "blessing of kings", "blessing of wisdom", "blessing of light" };
            }
        }
        else
        {
            blessings = { "blessing of might", "blessing of kings", "blessing of light" };
        }
    }
    else
    {
        // Blessings for pets
        blessings = { "blessing of might", "blessing of kings", "blessing of light" };
    }

    return blessings;
}

std::vector<std::string> CastRaidBlessingOnPartyAction::GetPossibleBlessingsForTarget(Unit* target) const
{
    std::vector<std::string> blessings;
    if (target && target->IsPlayer())
    {
        Player* player = (Player*)target;
        if (ai->IsTank(player))
        {
            blessings = { "blessing of kings", "blessing of might", "blessing of sanctuary", "blessing of light" };
        }
        else if (ai->IsHeal(player))
        {
            blessings = { "blessing of wisdom", "blessing of kings", "blessing of salvation", "blessing of light" };
        }
        else if (ai->IsRanged(player))
        {
            if (player->getClass() == CLASS_HUNTER)
            {
                blessings = { "blessing of wisdom", "blessing of kings", "blessing of might", "blessing of light" };
            }
            else
            {
                blessings = { "blessing of salvation", "blessing of kings", "blessing of wisdom", "blessing of light" };
            }
        }
        else
        {
            blessings = { "blessing of might", "blessing of kings", "blessing of salvation", "blessing of light" };
        }
    }
    else
    {
        // Blessings for pets
        blessings = { "blessing of might", "blessing of kings", "blessing of salvation", "blessing of light" };
    }

    return blessings;
}