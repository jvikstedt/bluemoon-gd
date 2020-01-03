#pragma once

#include <vector>
#include <yojimbo.h>
#include "ServerAdapter.hpp"
#include "../shared/ClientServerConfig.hpp"

class GameServer {

  public:
    explicit GameServer(const yojimbo::Address &address, const uint8_t privateKey[yojimbo::KeyBytes]);

    void ClientConnected(int clientIndex);

    void ClientDisconnected(int clientIndex);

    void Run();
    void Stop();

  private:
    float time;
    bool running;

    ServerAdapter adapter;
    ClientServerConfig connectionConfig;
    yojimbo::Server server;
    std::vector<Player> players;

    void Update(float dt);

    void ProcessMessages();

    void ProcessMessage(int clientIndex, int channelIndex, yojimbo::Message *message);
};
