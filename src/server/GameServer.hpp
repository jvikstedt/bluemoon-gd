#pragma once

#include <yojimbo.h>
#include "ServerAdapter.hpp"
#include "../shared/ClientServerConfig.hpp"

class GameServer {

  public:
    explicit GameServer(const yojimbo::Address &address, const uint8_t privateKey[yojimbo::KeyBytes]);

    void ClientConnected(int clientIndex);

    void ClientDisconnected(int clientIndex);

    void Run();

  private:
    float time;
    bool running;

    ServerAdapter adapter;
    ClientServerConfig connectionConfig;
    yojimbo::Server server;

    void Update(float dt);

    void ProcessMessages();

    void ProcessMessage(int clientIndex, int channelIndex, yojimbo::Message *message);

    void ProcessTestMessage(int clientIndex, int channelIndex, MyMessage *message);
};
