#pragma once
#include "playerbot/strategy/Trigger.h"

namespace ai
{
    class NoTravelTargetTrigger : public Trigger
    {
    public:
        NoTravelTargetTrigger(PlayerbotAI* ai) : Trigger(ai, "no travel target", 10) {}

        virtual bool IsActive();
    };

    class FarFromTravelTargetTrigger : public Trigger
    {
    public:
        FarFromTravelTargetTrigger(PlayerbotAI* ai) : Trigger(ai, "far from travel target") {}

        virtual bool IsActive();
    };

    class NearDarkPortalTrigger : public Trigger
    {
    public:
        NearDarkPortalTrigger(PlayerbotAI* ai) : Trigger(ai, "near dark portal", 10) {}

        virtual bool IsActive();
    };

    class AtDarkPortalAzerothTrigger : public Trigger
    {
    public:
        AtDarkPortalAzerothTrigger(PlayerbotAI* ai) : Trigger(ai, "at dark portal azeroth", 10) {}

        virtual bool IsActive();
    };

    class AtDarkPortalOutlandTrigger : public Trigger
    {
    public:
        AtDarkPortalOutlandTrigger(PlayerbotAI* ai) : Trigger(ai, "at dark portal outland", 10) {}

        virtual bool IsActive();
    };
}
