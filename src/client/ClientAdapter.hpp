#pragma once

#include <yojimbo.h>
#include "../shared/GameMessageFactory.hpp"

class GameServer;

class ClientAdapter : public yojimbo::Adapter {
public:
  yojimbo::MessageFactory *CreateMessageFactory(yojimbo::Allocator &allocator) override {
    return YOJIMBO_NEW(allocator, GameMessageFactory, allocator);
  }
};
