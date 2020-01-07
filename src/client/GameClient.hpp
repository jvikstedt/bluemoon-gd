#pragma once

#include <yojimbo.h>
#include "ClientAdapter.hpp"
#include "MessageHandler.hpp"
#include "../shared/ClientServerConfig.hpp"

class GameClient {
  public:
    explicit GameClient(uint64_t clientId, int tickrate, const yojimbo::Address &serverAddress, const uint8_t privateKey[yojimbo::KeyBytes], MessageHandler* messageHandler);
    void Update(float delta);
    bool IsConnected() const;
    void Disconnect();

  private:
    float timePassed;
    int tickrate;
    bool running;

    void ProcessMessages();
    void ProcessMessage(yojimbo::Message* message);
    void ProcessPlayerSyncMessage(PlayerSync* message);

    ClientAdapter adapter;
    ClientServerConfig connectionConfig;
    yojimbo::Client client;
    MessageHandler* messageHandler;
};
