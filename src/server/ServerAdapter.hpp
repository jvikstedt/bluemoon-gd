#pragma once

#include <yojimbo.h>
#include "../shared/GameMessageFactory.hpp"

class GameServer;

class ServerAdapter : public yojimbo::Adapter {
public:
  explicit ServerAdapter(GameServer *server = NULL) {
    this->server = server;
  }

  yojimbo::MessageFactory *CreateMessageFactory(yojimbo::Allocator &allocator) override {
    return YOJIMBO_NEW(allocator, GameMessageFactory, allocator);
  }

  void OnServerClientConnected(int clientIndex) override;

  void OnServerClientDisconnected(int clientIndex) override;

private:
  GameServer *server;
};
