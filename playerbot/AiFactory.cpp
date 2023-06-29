#include "../botpch.h"
#include "playerbot.h"
#include "AiFactory.h"
#include "strategy/AiObjectContext.h"
#include "strategy/ReactionEngine.h"

#include "strategy/priest/PriestAiObjectContext.h"
#include "strategy/mage/MageAiObjectContext.h"
#include "strategy/warlock/WarlockAiObjectContext.h"
#include "strategy/warrior/WarriorAiObjectContext.h"
#include "strategy/shaman/ShamanAiObjectContext.h"
#include "strategy/paladin/PaladinAiObjectContext.h"
#include "strategy/druid/DruidAiObjectContext.h"
#include "strategy/hunter/HunterAiObjectContext.h"
#include "strategy/rogue/RogueAiObjectContext.h"
#include "strategy/deathknight/DKAiObjectContext.h"
#include "Player.h"
#include "PlayerbotAIConfig.h"
#include "RandomPlayerbotMgr.h"
#include "BattleGroundMgr.h"

AiObjectContext* AiFactory::createAiObjectContext(Player* player, PlayerbotAI* ai)
{
    switch (player->getClass())
    {
        case CLASS_PRIEST:
        {
            return new PriestAiObjectContext(ai);
            break;
        }

        case CLASS_MAGE:
        {
            return new MageAiObjectContext(ai);
            break;
        }

        case CLASS_WARLOCK:
        {
            return new WarlockAiObjectContext(ai);
            break;
        }

        case CLASS_WARRIOR:
        {
            return new WarriorAiObjectContext(ai);
            break;
        }

        case CLASS_SHAMAN:
        {
            return new ShamanAiObjectContext(ai);
            break;
        }

        case CLASS_PALADIN:
        {
            return new PaladinAiObjectContext(ai);
            break;
        }

        case CLASS_DRUID:
        {
            return new DruidAiObjectContext(ai);
            break;
        }

        case CLASS_HUNTER:
        {
            return new HunterAiObjectContext(ai);
            break;
        }

        case CLASS_ROGUE:
        {
            return new RogueAiObjectContext(ai);
            break;
        }

#ifdef MANGOSBOT_TWO
        case CLASS_DEATH_KNIGHT:
        {
            return new DKAiObjectContext(ai);
            break;
        }
#endif
    }
    return new AiObjectContext(ai);
}

int AiFactory::GetPlayerSpecTab(Player* bot)
{
    map<uint32, int32> tabs = GetPlayerSpecTabs(bot);

    if (bot->GetLevel() >= 10 && ((tabs[0] + tabs[1] + tabs[2]) > 0))
    {
        int tab = -1, max = 0;
        for (uint32 i = 0; i < uint32(3); i++)
        {
            if (tab == -1 || max < tabs[i])
            {
                tab = i;
                max = tabs[i];
            }
        }
        return tab;
    }
    else
    {
        int tab = 0;

        switch (bot->getClass())
        {
        case CLASS_MAGE:
            tab = 1;
            break;
        case CLASS_PALADIN:
            tab = 0;
            break;
        case CLASS_PRIEST:
            tab = 1;
            break;
        }
        return tab;
    }
}

map<uint32, int32> AiFactory::GetPlayerSpecTabs(Player* bot)
{
    map<uint32, int32> tabs;
    for (uint32 i = 0; i < uint32(3); i++)
        tabs[i] = 0;

    uint32 classMask = bot->getClassMask();
    for (uint32 i = 0; i < sTalentStore.GetNumRows(); ++i)
    {
        TalentEntry const *talentInfo = sTalentStore.LookupEntry(i);
        if (!talentInfo)
            continue;

        TalentTabEntry const *talentTabInfo = sTalentTabStore.LookupEntry(talentInfo->TalentTab);
        if (!talentTabInfo)
            continue;

        if ((classMask & talentTabInfo->ClassMask) == 0)
            continue;

        int maxRank = 0;
        for (int rank = MAX_TALENT_RANK - 1; rank >= 0; --rank)
        {
            if (!talentInfo->RankID[rank])
                continue;

            uint32 spellid = talentInfo->RankID[rank];
            if (spellid && bot->HasSpell(spellid))
                maxRank = rank + 1;

        }
        tabs[talentTabInfo->tabpage] += maxRank;
    }

    return tabs;
}

BotRoles AiFactory::GetPlayerRoles(Player* player)
{
    BotRoles role = BOT_ROLE_NONE;
    int tab = GetPlayerSpecTab(player);
    switch (player->getClass())
    {
        case CLASS_PRIEST:
        {
            if (tab == 2)
            {
                role = BOT_ROLE_DPS;
            }
            else
            {
                role = BOT_ROLE_HEALER;
            }

            break;
        }

        case CLASS_SHAMAN:
        {
            if (tab == 2)
            {
                role = BOT_ROLE_HEALER;
            }
            else
            {
                role = BOT_ROLE_DPS;
            }

            break;
        }

        case CLASS_WARRIOR:
        {
            if (tab == 2 || player->HasAura(71)) // Defensive stance
            {
                role = BOT_ROLE_TANK;
            }
            else
            {
                role = BOT_ROLE_DPS;
            }

            break;
        }

        case CLASS_PALADIN:
        {
            if (tab == 1 || player->HasAura(25780)) // Righteous fury
            {
                role = BOT_ROLE_TANK;
            }
            else if (tab == 0)
            {
                role = BOT_ROLE_HEALER;  
            }
            else if (tab == 2)
            {
                role = BOT_ROLE_DPS;
            }

            break;
        }

        case CLASS_DRUID:
        {
            if (player->HasAura(5487) || player->HasAura(9634)) // Bear form, Dire bear form
            {
                role = BOT_ROLE_TANK;
            }
            else if (tab == 0)
            {
                role = BOT_ROLE_DPS;
            }
            else if (tab == 1)
            {
                role = (BotRoles)(BOT_ROLE_TANK | BOT_ROLE_DPS);
            }
            else if (tab == 2)
            {
                role = BOT_ROLE_HEALER;
            }

            break;
        }

#ifdef MANGOSBOT_TWO
        case CLASS_DEATH_KNIGHT:
        {
            if (player->HasAura(48263)) // Frost presence
            {
                role = BOT_ROLE_TANK;
            }
            else if (tab == 0)
            {
                role = BOT_ROLE_TANK;
            }
            else if (tab == 1)
            {
                role = (BotRoles)(BOT_ROLE_TANK | BOT_ROLE_DPS);
            }
            else if (tab == 2)
            {
                role = BOT_ROLE_DPS;
            }

            break;
        }
#endif
        default:
        {
            role = BOT_ROLE_DPS;
            break;
        }
    }


    return role;
}

void AiFactory::AddDefaultCombatStrategies(Player* player, PlayerbotAI* const facade, Engine* combatEngine)
{
    int tab = GetPlayerSpecTab(player);

    combatEngine->addStrategies("mount", NULL);

    if (!player->InBattleGround())
    {
        combatEngine->addStrategies("racials", "default", "duel", "pvp", NULL);
    }

    switch (player->getClass())
    {
        case CLASS_PRIEST:
        {
            if (tab == 2)
            {
                combatEngine->addStrategies("dps", "shadow debuff", "shadow aoe", "threat", NULL);
            }
            else if (tab == 0)
            {
                combatEngine->addStrategies("holy", "shadow debuff", "shadow aoe", "threat", NULL);
                    //if (player->GetLevel() >= 4)
                       //engine->addStrategy("dps debuff");
            }
            else
            {
                combatEngine->addStrategies("heal", "threat", NULL);
            }

            combatEngine->addStrategies("dps assist", "flee", "cure", "ranged", "cc", NULL);
            break;
        }

        case CLASS_MAGE:
        {
            if (tab == 0)
            {
                combatEngine->addStrategy("arcane");
            }
            else if (tab == 1)
            {
                combatEngine->addStrategy("fire");
            }
            else
            {
                combatEngine->addStrategy("frost");
            }

            combatEngine->addStrategies("dps", "dps assist", "threat", "flee", "cure", "ranged", "cc", "buff", "aoe", NULL);
            break;
        }

        case CLASS_WARRIOR:
        {
            if (tab == 2)
            {
                combatEngine->addStrategies("protection", "tank assist", "pull", "pull back", "mark rti", NULL);
            }
            else if (player->GetLevel() < 30 || tab == 0)
            {
                combatEngine->addStrategies("arms", "dps assist", "threat", "behind", NULL);
            }
            else
            {
                combatEngine->addStrategies("fury", "dps assist", "threat", "behind", NULL);
            }

            combatEngine->addStrategies("aoe", "cc", "buff", NULL);
            break;
        }

        case CLASS_SHAMAN:
        {
            if (tab == 0)
            {
                combatEngine->addStrategies("elemental", "aoe", "bmana", "threat", "flee", "ranged", NULL);
            }
            else if (tab == 2)
            {
                combatEngine->addStrategies("restoration", "bmana", "flee", "ranged", NULL);
            }
            else
            {
                combatEngine->addStrategies("enhancement", "aoe", "bdps", "threat", "close", NULL);
            }

            combatEngine->addStrategies("dps assist", "cure", "totems", "buff", NULL);
            break;
        }

        case CLASS_PALADIN:
        {
            if (tab == 1)
            {
                combatEngine->addStrategies("protection", "tank assist", "pull", "pull back", "bthreat", "close", NULL);
			}
            else if(tab == 0)
            {
                combatEngine->addStrategies("holy", "dps assist", "flee", "ranged", NULL);
            }
            else
            {
                combatEngine->addStrategies("retribution", "dps assist", "close", NULL);
            }

            combatEngine->addStrategies("cure", "aoe", "cc", "buff", "aura", "blessing", NULL);
            break;
        }

        case CLASS_DRUID:
        {
            if (tab == 0)
            {
                combatEngine->addStrategies("caster", "cure", "caster aoe", "threat", "flee", "dps assist", "ranged", "cc", NULL);
                if (player->GetLevel() > 19)
                {
                    combatEngine->addStrategy("caster debuff");
                }
            }
            else if (tab == 2)
            {
                combatEngine->addStrategies("heal", "cure", "flee", "dps assist", "ranged", "cc", NULL);
            }
            else
            {
                combatEngine->removeStrategy("ranged");
                combatEngine->addStrategies("bear", "tank assist", "pull", "pull back", "flee", "close", "behind", NULL);
            }

            break;
        }

        case CLASS_HUNTER:
        {
            combatEngine->addStrategies("dps", "bdps", "threat", "dps assist", "ranged", "cc", "aoe", "dps debuff", NULL);
            break;
        }

        case CLASS_ROGUE:
        {
            if (tab == 0)
            {
                combatEngine->addStrategy("assassination");
            }
            else if (tab == 2)
            {
                combatEngine->addStrategy("subtlety");
            }
            else
            {
                combatEngine->addStrategy("combat");
            }

            combatEngine->addStrategies("threat", "dps assist", "aoe", "close", "cc", "behind", "stealth", "poisons", "buff", NULL);

            break;
        }

        case CLASS_WARLOCK:
        {
            if (tab == 0)
            {
                combatEngine->addStrategy("affliction");
            }
            else if (tab == 1)
            {
                combatEngine->addStrategy("demonology");
            }
            else
            {
                combatEngine->addStrategy("destruction");
            }

            combatEngine->addStrategies("dps assist", "flee", "ranged", "cc", "pet", "threat", "aoe", "buff", "curse", NULL);
            break;
        }

#ifdef MANGOSBOT_TWO
        case CLASS_DEATH_KNIGHT:
        {
            if (tab == 0)
            {
                combatEngine->addStrategies("blood", "tank assist", "pull", "pull back", NULL);
            }
            else if (tab == 1)
            {
                combatEngine->addStrategies("frost", "frost aoe", "dps assist", "threat", NULL);
            }
            else
            {
                combatEngine->addStrategies("unholy", "unholy aoe", "dps assist", "threat", NULL);
            }

            combatEngine->addStrategies("dps assist", "flee", "close", "cc", NULL);
            break;
        }
#endif
    }

	if (facade->IsRealPlayer() || sRandomPlayerbotMgr.IsFreeBot(player))
	{
        combatEngine->addStrategy("roll");

        if (!player->GetGroup())
        {
            combatEngine->addStrategy("flee");
            combatEngine->addStrategy("boost");
            
            if (player->getClass() == CLASS_DRUID && tab == 2)
            {
                combatEngine->addStrategies("caster", "caster aoe", NULL);
            }

            if (player->getClass() == CLASS_DRUID && tab == 1 && urand(0, 100) > 50 && player->GetLevel() > 19)
            {
                combatEngine->addStrategy("dps");
            }

            if (player->getClass() == CLASS_PRIEST && tab == 1)
            {
                combatEngine->removeStrategy("heal");
                combatEngine->addStrategies("holy", "shadow debuff", "shadow aoe", "threat", NULL);
            }

            if (player->getClass() == CLASS_SHAMAN && tab == 2)
            {
                combatEngine->addStrategies("elemental", "aoe", NULL);
            }

            if (player->getClass() == CLASS_PALADIN && tab == 0)
            {
                combatEngine->addStrategies("retribution", "close", NULL);
                combatEngine->removeStrategy("ranged");
            }
        }

        // enable paladin fight at low level
        if (player->getClass() == CLASS_PALADIN && tab == 0 && player->GetLevel() < 10)
        {
            combatEngine->addStrategies("retribution", "close", NULL);
            combatEngine->removeStrategy("ranged");
        }

        // remove threat for now
        //engine->removeStrategy("threat");

        combatEngine->ChangeStrategy(sPlayerbotAIConfig.randomBotCombatStrategies);
    }
    else
    {
        combatEngine->ChangeStrategy(sPlayerbotAIConfig.combatStrategies);
    }

    // Battleground switch
    if (player->InBattleGround())
    {
        BattleGroundTypeId bgType = player->GetBattleGroundTypeId();

#ifdef MANGOSBOT_TWO
        if (bgType == BATTLEGROUND_RB)
        {
            bgType = player->GetBattleGround()->GetTypeId(true);
        }

        if (bgType == BATTLEGROUND_IC)
        {
            combatEngine->addStrategy("isle");
        }
#endif

        if (bgType == BATTLEGROUND_WS)
        {
            combatEngine->addStrategy("warsong");
        }

        if (bgType == BATTLEGROUND_AB)
        {
            combatEngine->addStrategy("arathi");
        }

        if(bgType == BATTLEGROUND_AV)
        {
            combatEngine->addStrategy("alterac");
        }

#ifndef MANGOSBOT_ZERO
        if (bgType == BATTLEGROUND_EY)
        {
            combatEngine->addStrategy("eye");
        }
#endif

#ifndef MANGOSBOT_ZERO
        if (player->InArena())
        {
            combatEngine->addStrategy("arena");
        }
#endif
        combatEngine->addStrategies("boost", "racials", "default", "aoe", "dps assist", "pvp", NULL);
        combatEngine->removeStrategy("custom::say");
        combatEngine->removeStrategy("flee");
        combatEngine->removeStrategy("threat");
        combatEngine->removeStrategy("follow");
        combatEngine->removeStrategy("conserve mana");
        combatEngine->removeStrategy("cast time");
        combatEngine->addStrategy("boost");

        if (player->getClass() == CLASS_SHAMAN && tab == 2)
        {
            combatEngine->addStrategies("elemental", "aoe", NULL);
        }

        if (player->getClass() == CLASS_DRUID && tab == 2)
        {
            combatEngine->addStrategies("caster", "caster aoe", NULL);
        }

        if (player->getClass() == CLASS_DRUID && tab == 1)
        {
            combatEngine->addStrategies("behind", "dps", NULL);
        }
        
        if (player->getClass() == CLASS_ROGUE)
        {
            combatEngine->addStrategies("behind", "stealth", "poisons", "buff", NULL);
        }
    }
}

Engine* AiFactory::createCombatEngine(Player* player, PlayerbotAI* const facade, AiObjectContext* AiObjectContext)
{
	Engine* engine = new Engine(facade, AiObjectContext, BotState::BOT_STATE_COMBAT);
    AddDefaultCombatStrategies(player, facade, engine);
    return engine;
}

void AiFactory::AddDefaultNonCombatStrategies(Player* player, PlayerbotAI* const facade, Engine* nonCombatEngine)
{
    const int tab = GetPlayerSpecTab(player);
    switch (player->getClass())
    {
        case CLASS_PRIEST:
        {
            nonCombatEngine->addStrategies("dps assist", "cure", "rshadow", NULL);
            break;
        }

        case CLASS_PALADIN:
        {
            if (tab == 1)
            {
                nonCombatEngine->addStrategies("protection", "tank assist", NULL);
            }
            else if (tab == 0)
            {
                nonCombatEngine->addStrategies("holy", "dps assist", NULL);
            }
            else
            {
                nonCombatEngine->addStrategies("retribution", "dps assist", NULL);
            }

            nonCombatEngine->addStrategies("cure", "buff", "blessing", "aura", NULL);
            break;
        }

        case CLASS_HUNTER:
        {
            nonCombatEngine->addStrategies("bdps", "dps assist", "pet", NULL);
            break;
        }

        case CLASS_SHAMAN:
        {
            if (tab == 0)
            {
                nonCombatEngine->addStrategies("elemental", "bmana", "aoe", NULL);
            }
            else if (tab == 2)
            {
                nonCombatEngine->addStrategies("restoration", "bmana", NULL);
            }
            else
            {
                nonCombatEngine->addStrategies("enhancement", "bdps", NULL);
            }

            nonCombatEngine->addStrategies("dps assist", "cure", "totems", "buff", NULL);
            break;
        }

        case CLASS_ROGUE:
        {
            if (tab == 0)
            {
                nonCombatEngine->addStrategy("assassination");
            }
            else if (tab == 2)
            {
                nonCombatEngine->addStrategy("subtlety");
            }
            else
            {
                nonCombatEngine->addStrategy("combat");
            }

            nonCombatEngine->addStrategies("dps assist", "poisons", "stealth", "buff", NULL);
            break;
        }

        case CLASS_WARLOCK:
        {
            if (tab == 0)
            {
                nonCombatEngine->addStrategy("affliction");
            }
            else if (tab == 1)
            {
                nonCombatEngine->addStrategy("demonology");
            }
            else
            {
                nonCombatEngine->addStrategy("destruction");
            }

            nonCombatEngine->addStrategies("dps assist", "pet", "buff", NULL);
            break;
        }

        case CLASS_MAGE:
        {
            if (tab == 0)
            {
                nonCombatEngine->addStrategy("arcane");
            }
            else if (tab == 1)
            {
                nonCombatEngine->addStrategy("fire");
            }
            else
            {
                nonCombatEngine->addStrategy("frost");
            }

            nonCombatEngine->addStrategies("dps assist", "cure", "buff", NULL);
            break;
        }

        case CLASS_DRUID:
        {
            if (tab == 1)
            {
                nonCombatEngine->addStrategies("tank assist", "cure", NULL);
            }
            else
            {
                nonCombatEngine->addStrategies("dps assist", "cure", NULL);
            }

            break;
        }

        case CLASS_WARRIOR:
        {
            if (tab == 2)
            {
                nonCombatEngine->addStrategies("protection", "tank assist", NULL);
            }
            else if(tab == 0)
            {
                nonCombatEngine->addStrategies("arms", "dps assist", NULL);
            }
            else
            {
                nonCombatEngine->addStrategies("fury", "dps assist", NULL);
            }

            nonCombatEngine->addStrategy("buff");
            break;
        }

#ifdef MANGOSBOT_TWO
        case CLASS_DEATH_KNIGHT:
        {
            if (tab == 0)
            {
                nonCombatEngine->addStrategy("tank assist");
            }
            else
            {
                nonCombatEngine->addStrategy("dps assist");
            }

            break;
        }
#endif

        default:
        {
            nonCombatEngine->addStrategy("dps assist");
            break;
        }
    }

    nonCombatEngine->addStrategies("wbuff", NULL);

    if (!player->InBattleGround())
    {
        nonCombatEngine->addStrategies("racials", "nc", "food", "follow", "default", "quest", "loot", "gather", "duel", "emote", "buff", "mount", NULL);
    }

    if ((facade->IsRealPlayer() || sRandomPlayerbotMgr.IsFreeBot(player)) && !player->InBattleGround())
    {   
        Player* master = facade->GetMaster();

        nonCombatEngine->addStrategy("roll");

        // let 25% of free bots start duels.
        if (!urand(0, 3))
        {
            nonCombatEngine->addStrategy("start duel");
        }

        if (sPlayerbotAIConfig.randomBotJoinLfg)
        {
            nonCombatEngine->addStrategy("lfg");
        }

        if (!player->GetGroup() || player->GetGroup()->GetLeaderGuid() == player->GetObjectGuid())
        {
            // let 25% of random not grouped (or group leader) bots help other players
            if (!urand(0, 3))
            {
                nonCombatEngine->addStrategy("attack tagged");
            }

            nonCombatEngine->addStrategy("collision");
            nonCombatEngine->addStrategy("grind");            
            nonCombatEngine->addStrategy("group");
            nonCombatEngine->addStrategy("guild");

            if (sPlayerbotAIConfig.autoDoQuests)
            {
                nonCombatEngine->addStrategy("travel");
                nonCombatEngine->addStrategy("rpg");                
                nonCombatEngine->removeStrategy("rpg craft");
            }

            if (sPlayerbotAIConfig.randomBotJoinBG)
            {
                nonCombatEngine->addStrategy("bg");
            }

            if(!master || master->GetPlayerbotAI())
            {
                nonCombatEngine->addStrategy("maintenance");
            }

            nonCombatEngine->ChangeStrategy(sPlayerbotAIConfig.randomBotNonCombatStrategies);
        }
        else 
        {
            if (facade)
            {
                if (master)
                {
                    if (master->GetPlayerbotAI() || sRandomPlayerbotMgr.IsFreeBot(player))
                    {
                        nonCombatEngine->addStrategy("collision");
                        nonCombatEngine->addStrategy("grind");
                        nonCombatEngine->addStrategy("group");
                        nonCombatEngine->addStrategy("guild");

                        if (sPlayerbotAIConfig.autoDoQuests)
                        {
                            nonCombatEngine->addStrategy("travel");
                            nonCombatEngine->addStrategy("rpg");
                            nonCombatEngine->removeStrategy("rpg craft");

                        }

                        if (!master || master->GetPlayerbotAI())
                        {
                            nonCombatEngine->addStrategy("maintenance");
                        }

                        nonCombatEngine->ChangeStrategy(sPlayerbotAIConfig.randomBotNonCombatStrategies);
                    }
                    else
                    {
                        nonCombatEngine->ChangeStrategy(sPlayerbotAIConfig.nonCombatStrategies);
                    }
                }
            }
        }
    }
    else
    {
        nonCombatEngine->ChangeStrategy(sPlayerbotAIConfig.nonCombatStrategies);
    }

    // Battleground switch
    if (player->InBattleGround())
    {
        nonCombatEngine->addStrategies("racials", "nc", "default", "buff", "food", "mount", "collision", "dps assist", "attack tagged", "emote", NULL);
        nonCombatEngine->removeStrategy("custom::say");
        nonCombatEngine->removeStrategy("travel");
        nonCombatEngine->removeStrategy("rpg");
        nonCombatEngine->removeStrategy("rpg craft");
        nonCombatEngine->removeStrategy("follow");

        nonCombatEngine->removeStrategy("grind");

        BattleGroundTypeId bgType = player->GetBattleGroundTypeId();
#ifdef MANGOSBOT_TWO
        if (bgType == BATTLEGROUND_RB)
        {
            bgType = player->GetBattleGround()->GetTypeId(true);
        }
#endif

        bool isArena = false;

#ifndef MANGOSBOT_ZERO
        if (player->InArena())
        {
            isArena = true;
        }
#endif
        if (isArena)
        {
            nonCombatEngine->addStrategy("arena");
            nonCombatEngine->removeStrategy("mount");
        }
        else
        {
#ifndef MANGOSBOT_ZERO
#ifdef MANGOSBOT_TWO
            if (bgType <= BATTLEGROUND_EY || bgType == BATTLEGROUND_IC) // do not add for not supported bg
            {
                nonCombatEngine->addStrategy("battleground");
            }
#else
            if (bgType <= BATTLEGROUND_EY) // do not add for not supported bg
            {
                nonCombatEngine->addStrategy("battleground");
            }
#endif
#else
            if (bgType <= BATTLEGROUND_AB) // do not add for not supported bg
            {
                nonCombatEngine->addStrategy("battleground");
            }
#endif

            if (bgType == BATTLEGROUND_WS)
            {
                nonCombatEngine->addStrategy("warsong");
            }

            if (bgType == BATTLEGROUND_AV)
            {
                nonCombatEngine->addStrategy("alterac");
            }

            if (bgType == BATTLEGROUND_AB)
            {
                nonCombatEngine->addStrategy("arathi");
            }

#ifndef MANGOSBOT_ZERO
            if (bgType == BATTLEGROUND_EY)
            {
                nonCombatEngine->addStrategy("eye");
            }
#endif
#ifdef MANGOSBOT_TWO
            if (bgType == BATTLEGROUND_IC)
            {
                nonCombatEngine->addStrategy("isle");
            }
#endif
        }
    }
}

Engine* AiFactory::createNonCombatEngine(Player* player, PlayerbotAI* const facade, AiObjectContext* AiObjectContext) 
{
	Engine* nonCombatEngine = new Engine(facade, AiObjectContext, BotState::BOT_STATE_NON_COMBAT);
    AddDefaultNonCombatStrategies(player, facade, nonCombatEngine);
	return nonCombatEngine;
}

void AiFactory::AddDefaultDeadStrategies(Player* player, PlayerbotAI* const facade, Engine* deadEngine)
{
    deadEngine->addStrategies("dead", "stay", "default", "follow", "group", NULL);
    if (sRandomPlayerbotMgr.IsFreeBot(player) && !player->GetGroup())
    {
        deadEngine->removeStrategy("follow");
    }

    const int tab = GetPlayerSpecTab(player);
    switch (player->getClass())
    {
        case CLASS_SHAMAN:
        {
            if (tab == 0)
            {
                deadEngine->addStrategy("elemental");
            }
            else if (tab == 2)
            {
                deadEngine->addStrategy("restoration");
            }
            else
            {
                deadEngine->addStrategy("enhancement");
            }

            break;
        }

        case CLASS_ROGUE:
        {
            if (tab == 0)
            {
                deadEngine->addStrategy("assassination");
            }
            else if (tab == 2)
            {
                deadEngine->addStrategy("subtlety");
            }
            else
            {
                deadEngine->addStrategy("combat");
            }

            break;
        }

        case CLASS_WARLOCK:
        {
            if (tab == 0)
            {
                deadEngine->addStrategy("affliction");
            }
            else if (tab == 1)
            {
                deadEngine->addStrategy("demonology");
            }
            else
            {
                deadEngine->addStrategy("destruction");
            }

            break;
        }

        case CLASS_MAGE:
        {
            if (tab == 0)
            {
                deadEngine->addStrategy("arcane");
            }
            else if (tab == 1)
            {
                deadEngine->addStrategy("fire");
            }
            else
            {
                deadEngine->addStrategy("frost");
            }

            break;
        }

        case CLASS_PALADIN:
        {
            if (tab == 1)
            {
                deadEngine->addStrategy("protection");
            }
            else if (tab == 0)
            {
                deadEngine->addStrategy("holy");
            }
            else
            {
                deadEngine->addStrategy("retribution");
            }

            break;
        }

        case CLASS_WARRIOR:
        {
            if (tab == 2)
            {
                deadEngine->addStrategy("protection");
            }
            else if (tab == 0)
            {
                deadEngine->addStrategy("arms");
            }
            else
            {
                deadEngine->addStrategy("fury");
            }

            break;
        }
    }
}

Engine* AiFactory::createDeadEngine(Player* player, PlayerbotAI* const facade, AiObjectContext* AiObjectContext)
{
    Engine* deadEngine = new Engine(facade, AiObjectContext, BotState::BOT_STATE_DEAD);
    AddDefaultDeadStrategies(player, facade, deadEngine);
    return deadEngine;
}

void AiFactory::AddDefaultReactionStrategies(Player* player, PlayerbotAI* const facade, ReactionEngine* reactionEngine)
{
    reactionEngine->addStrategies("react", "chat", "avoid aoe", "potions", NULL);

    const int tab = GetPlayerSpecTab(player);
    switch (player->getClass())
    {
        case CLASS_SHAMAN:
        {
            if (tab == 0)
            {
                reactionEngine->addStrategy("elemental");
            }
            else if (tab == 2)
            {
                reactionEngine->addStrategy("restoration");
            }
            else
            {
                reactionEngine->addStrategy("enhancement");
            }

            break;
        }

        case CLASS_ROGUE:
        {
            if (tab == 0)
            {
                reactionEngine->addStrategy("assassination");
            }
            else if (tab == 2)
            {
                reactionEngine->addStrategy("subtlety");
            }
            else
            {
                reactionEngine->addStrategy("combat");
            }

            break;
        }

        case CLASS_WARLOCK:
        {
            if (tab == 0)
            {
                reactionEngine->addStrategy("affliction");
            }
            else if (tab == 1)
            {
                reactionEngine->addStrategy("demonology");
            }
            else
            {
                reactionEngine->addStrategy("destruction");
            }

            break;
        }

        case CLASS_MAGE:
        {
            if (tab == 0)
            {
                reactionEngine->addStrategy("arcane");
            }
            else if (tab == 1)
            {
                reactionEngine->addStrategy("fire");
            }
            else
            {
                reactionEngine->addStrategy("frost");
            }

            break;
        }

        case CLASS_PALADIN:
        {
            if (tab == 1)
            {
                reactionEngine->addStrategy("protection");
            }
            else if (tab == 0)
            {
                reactionEngine->addStrategy("holy");
            }
            else
            {
                reactionEngine->addStrategy("retribution");
            }

            break;
        }

        case CLASS_WARRIOR:
        {
            if (tab == 2)
            {
                reactionEngine->addStrategy("protection");
            }
            else if (tab == 0)
            {
                reactionEngine->addStrategy("arms");
            }
            else
            {
                reactionEngine->addStrategy("fury");
            }

            break;
        }
    }
}

ReactionEngine* AiFactory::createReactionEngine(Player* player, PlayerbotAI* const facade, AiObjectContext* AiObjectContext)
{
    ReactionEngine* reactionEngine = new ReactionEngine(facade, AiObjectContext, BotState::BOT_STATE_REACTION);
    AddDefaultReactionStrategies(player, facade, reactionEngine);
    return reactionEngine;
}