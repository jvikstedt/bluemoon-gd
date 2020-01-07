#pragma once

#include "GameMessageType.hpp"
#include "EntitySync.hpp"

YOJIMBO_MESSAGE_FACTORY_START(GameMessageFactory, (int) GameMessageType::COUNT);
  YOJIMBO_DECLARE_MESSAGE_TYPE((int) GameMessageType::ENTITY_SYNC, EntitySync);
YOJIMBO_MESSAGE_FACTORY_FINISH();
