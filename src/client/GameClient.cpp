#include "GameClient.hpp"
#include <iostream>
#include <string>
#include "../shared/MyMessage.hpp"

GameClient::GameClient(uint64_t clientId, const yojimbo::Address &serverAddress, const uint8_t privateKey[yojimbo::KeyBytes]) :
        time(0.0f),
        running(true),
        adapter(),
        client(yojimbo::GetDefaultAllocator(), yojimbo::Address("0.0.0.0"), connectionConfig, adapter, time) {

  client.InsecureConnect(privateKey, clientId, serverAddress);
}

bool GameClient::IsConnected() {
  return client.IsConnected();
}

void GameClient::Disconnect() {
  client.Disconnect();
}

void GameClient::Update(float delta) {
  double previousTime = client.GetTime();

  time = time + delta;
  if (time  < (previousTime + 1/5)) {
    return;
  }

  client.AdvanceTime(time);
  client.ReceivePackets();

  if (client.IsConnected()) {
    MyMessage* message = (MyMessage*)client.CreateMessage((int)GameMessageType::TEST);
    message->m_data = 42;
    client.SendMessage((int)GameChannel::RELIABLE, message);
  }

  client.SendPackets();
}
