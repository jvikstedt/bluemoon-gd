#pragma once

#include "GameMessageType.hpp"
#include "MyMessage.hpp"

YOJIMBO_MESSAGE_FACTORY_START(GameMessageFactory, (int) GameMessageType::COUNT);
  YOJIMBO_DECLARE_MESSAGE_TYPE((int) GameMessageType::TEST, MyMessage);
YOJIMBO_MESSAGE_FACTORY_FINISH();
