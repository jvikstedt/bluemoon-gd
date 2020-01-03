#include "ServerAdapter.hpp"
#include "GameServer.hpp"

void ServerAdapter::OnServerClientConnected(int clientIndex) {
  if (server != NULL) {
    server->ClientConnected(clientIndex);
  }
}

void ServerAdapter::OnServerClientDisconnected(int clientIndex) {
  if (server != NULL) {
    server->ClientDisconnected(clientIndex);
  }
}
