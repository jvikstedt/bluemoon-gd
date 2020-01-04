#pragma once

#include "../shared/PlayerSync.hpp"

class MessageHandler {
public:
  virtual void PlayerSyncMsg(PlayerSync* playerSync) = 0;
};
