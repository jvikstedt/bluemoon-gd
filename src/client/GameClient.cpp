#include "GameClient.hpp"
#include <iostream>
#include <string>
#include "logger.hpp"

#include "../shared/PlayerSync.hpp"

GameClient::GameClient(uint64_t clientId, const yojimbo::Address &serverAddress, const uint8_t privateKey[yojimbo::KeyBytes], MessageHandler* messageHandler) :
        time(0.0f),
        running(true),
        adapter(),
        messageHandler(messageHandler),
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
  if (time  < (previousTime + 1)) {
    return;
  }

  // client_printf("%f\n", time);

  client.AdvanceTime(time);
  client.ReceivePackets();

  if (client.IsConnected()) {
    ProcessMessages();
    // MyMessage* message = (MyMessage*)client.CreateMessage((int)GameMessageType::TEST);
    // message->m_data = 42;
    // client.SendMessage((int)GameChannel::RELIABLE, message);
  }

  client.SendPackets();
}

void GameClient::ProcessMessages() {
  for (int i = 0; i < connectionConfig.numChannels; i++) {
    yojimbo::Message *message = client.ReceiveMessage(i);
    while (message != NULL) {
      ProcessMessage(message);
      client.ReleaseMessage(message);
      message = client.ReceiveMessage(i);
    }
  }
}

void GameClient::ProcessMessage(yojimbo::Message* message) {
  switch (message->GetType()) {
    case (int)GameMessageType::PLAYER_SYNC:
      // ProcessPlayerSyncMessage((PlayerSync*)message);
      messageHandler->PlayerSyncMsg((PlayerSync*)message);
      break;
    default:
      break;
  }
}

void GameClient::ProcessPlayerSyncMessage(PlayerSync* message) {
  int playersSize = message->players.size();
  client_printf("Received PlayerSync with %d players\n", playersSize);
  for (int i = 0; i < playersSize; i++) {
    Player p = message->players[i];
    client_printf("Player(%d) x: %f y: %f\n", p.id, p.x, p.y);
  }
}
