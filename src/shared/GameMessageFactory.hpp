#pragma once

#include "GameMessageType.hpp"
#include "PlayerSync.hpp"

YOJIMBO_MESSAGE_FACTORY_START(GameMessageFactory, (int) GameMessageType::COUNT);
  YOJIMBO_DECLARE_MESSAGE_TYPE((int) GameMessageType::PLAYER_SYNC, PlayerSync);
YOJIMBO_MESSAGE_FACTORY_FINISH();
