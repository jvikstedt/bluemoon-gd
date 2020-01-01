#include <iostream>
#include "GameServer.hpp"
#include <yojimbo.h>

const int ServerPort = 40000;

int main() {
  if (!InitializeYojimbo()) {
    printf("error: failed to initialize Yojimbo!\n");
    return 1;
  }

  yojimbo_log_level(YOJIMBO_LOG_LEVEL_INFO);

  srand((unsigned int) time( NULL ));

  uint8_t privateKey[yojimbo::KeyBytes];
  memset(privateKey, 0, yojimbo::KeyBytes);

  GameServer server(yojimbo::Address("127.0.0.1", ServerPort), privateKey);
  server.Run();

  ShutdownYojimbo();

  return 0;
}
