#pragma once

#include "../Action.h"

namespace ai
{
   class AcceptBgInvitationAction : public Action {
   public:
      AcceptBgInvitationAction(PlayerbotAI* ai) : Action(ai, "accept bg invitation") {}

      virtual bool Execute(Event event)
      {
         /*
         uint8 type = 0;                                             // arenatype if arena
         uint8 unk2;                                             // unk, can be 0x0 (may be if was invited?) and 0x1
         uint32 bgTypeId_ = BATTLEGROUND_WS;                                       // type id from dbc
         uint16 unk = 0x1F90;                                              // 0x1F90 constant?
         uint8 action = 1;

         WorldPacket packet(CMSG_BATTLEFIELD_PORT, 20);
         //packet << type << unk2 << bgTypeId_ << unk << action;
         packet << bgTypeId_ << action;
         //bot->GetSession()->HandleBattleFieldPortOpcode(packet);

         ai->ResetStrategies();*/
         return true;
      }
   };
}

