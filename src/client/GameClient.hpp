#pragma once

#include <yojimbo.h>
#include "ClientAdapter.hpp"
#include "../shared/ClientServerConfig.hpp"

class GameClient {
  public:
    explicit GameClient(uint64_t clientId, const yojimbo::Address &serverAddress, const uint8_t privateKey[yojimbo::KeyBytes]);
    void Update(float delta);
    bool IsConnected();
    void Disconnect();

  private:
    float time;
    bool running;

    ClientAdapter adapter;
    ClientServerConfig connectionConfig;
    yojimbo::Client client;
};
