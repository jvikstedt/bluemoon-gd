#include "GameClient.hpp"
#include "logger.hpp"

GameClient::GameClient(uint64_t clientId, int tickrate, const yojimbo::Address &serverAddress, const uint8_t privateKey[yojimbo::KeyBytes], MessageHandler* messageHandler) :
        tickrate(tickrate),
        timePassed(0.0f),
        running(true),
        adapter(),
        messageHandler(messageHandler),
        client(yojimbo::GetDefaultAllocator(), yojimbo::Address("0.0.0.0"), connectionConfig, adapter, timePassed) {

  client.InsecureConnect(privateKey, clientId, serverAddress);
}

bool GameClient::IsConnected() const {
  return client.IsConnected();
}

void GameClient::Disconnect() {
  client.Disconnect();
}

void GameClient::Update(float delta) {
  double previousTickTime = client.GetTime();
  double nextTickTime = previousTickTime + (1 / tickrate);

  timePassed = timePassed + delta;
  if (timePassed < nextTickTime) {
    return;
  }

  client.AdvanceTime(timePassed);
  client.ReceivePackets();

  if (client.IsConnected()) {
    ProcessMessages();
  }

  client.SendPackets();
}

void GameClient::ProcessMessages() {
  if (messageHandler == nullptr) {
    client_printf("Can't process messages, because messageHandler is nullptr");
    Disconnect();
    return;
  }

  for (int i = 0; i < connectionConfig.numChannels; i++) {
    yojimbo::Message *message = client.ReceiveMessage(i);
    while (message != nullptr) {
      messageHandler->HandleMessage(message);
      client.ReleaseMessage(message);
      message = client.ReceiveMessage(i);
    }
  }
}
