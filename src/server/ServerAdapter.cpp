#include "ServerAdapter.hpp"
#include "GameServer.hpp"

void ServerAdapter::OnServerClientConnected(int clientIndex) {
  if (server != nullptr) {
    server->ClientConnected(clientIndex);
  }
}

void ServerAdapter::OnServerClientDisconnected(int clientIndex) {
  if (server != nullptr) {
    server->ClientDisconnected(clientIndex);
  }
}
