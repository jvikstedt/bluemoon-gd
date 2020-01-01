#include "GameServer.hpp"
#include <iostream>
#include <string>

static const int MAX_PLAYERS = 8;

GameServer::GameServer(const yojimbo::Address &address, const uint8_t privateKey[yojimbo::KeyBytes]) :
        time(0.0f),
        running(true),
        adapter(this),
        server(yojimbo::GetDefaultAllocator(), privateKey, address, connectionConfig, adapter, time) {

  server.Start(MAX_PLAYERS);
  if (!server.IsRunning()) {
    throw std::runtime_error("Could not start server at port " + std::to_string(address.GetPort()));
  }

  // print the port we got in case we used port 0
  char addressString[256];
  server.GetAddress().ToString(addressString, sizeof(addressString));
  printf("server address is %s\n", addressString);
}

void GameServer::ClientConnected(int clientIndex) {
  std::cout << "client " << clientIndex << " connected" << std::endl;
}

void GameServer::ClientDisconnected(int clientIndex) {
  std::cout << "client " << clientIndex << " disconnected" << std::endl;
}

void GameServer::Run() {
  float fixedDt = 1.0f / 10.0f;
  while (running) {
    double currentTime = yojimbo_time();
    if (time <= currentTime) {
      Update(fixedDt);
      time += fixedDt;
    } else {
      yojimbo_sleep(time - currentTime);
    }
  }
}

void GameServer::Update(float dt) {
  if (!server.IsRunning()) {
    running = false;
    return;
  }

  server.AdvanceTime(time);
  server.ReceivePackets();
  ProcessMessages();


  // ... process client inputs ...
  // ... update game ...
  // ... send game state to clients ...


  server.SendPackets();
}

void GameServer::ProcessMessages() {
  for (int i = 0; i < MAX_PLAYERS; i++) {
    if (server.IsClientConnected(i)) {
      for (int j = 0; j < connectionConfig.numChannels; j++) {
        yojimbo::Message *message = server.ReceiveMessage(i, j);
        while (message != NULL) {
          ProcessMessage(i, j, message);
          server.ReleaseMessage(i, message);
          message = server.ReceiveMessage(i, j);
        }
      }
    }
  }
}

void GameServer::ProcessMessage(int clientIndex, int channelIndex, yojimbo::Message *message) {
  switch (message->GetType()) {
    case (int) GameMessageType::TEST:
      ProcessTestMessage(clientIndex, channelIndex, (MyMessage*) message);
      break;
    default:
      break;
  }
}

void GameServer::ProcessTestMessage(int clientIndex, int channelIndex, MyMessage *message) {
  printf("Client index %d sent message %d\n", clientIndex, message->m_data);
  // auto respond = (MyMessage*) server.CreateMessage(clientIndex, (int) GameMessageType::TEST);
  // respond->m_data = 100;

  // server.SendMessage(clientIndex, channelIndex, respond);
}
