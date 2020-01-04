#include <iostream>
#include <signal.h>
#include <yojimbo.h>
#include "GameServer.hpp"

const int ServerPort = 40000;

GameServer* server;

void interrupt_handler(int) {
  if (server != nullptr) {
    server->Stop();
  }
}

int main() {
  if (!InitializeYojimbo()) {
    printf("error: failed to initialize Yojimbo!\n");
    return 1;
  }

  signal(SIGINT, interrupt_handler);

  yojimbo_log_level(YOJIMBO_LOG_LEVEL_INFO);

  srand((unsigned int) time( NULL ));

  uint8_t privateKey[yojimbo::KeyBytes];
  memset(privateKey, 0, yojimbo::KeyBytes);
  GameServer gameServer(yojimbo::Address("127.0.0.1", ServerPort), privateKey);
  server = &gameServer;
  server->Run();

  ShutdownYojimbo();

  return 0;
}
