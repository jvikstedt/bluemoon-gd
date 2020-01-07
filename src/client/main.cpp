#include <memory>
#include <iostream>
#include "GameClient.hpp"
#include <yojimbo.h>
#include <unistd.h>
#include "../shared/Entity.hpp"
#include "../shared/Character.hpp"

const int ServerPort = 40000;

int a_printf(const char *format, ... ) {
  va_list args;
  int done;
  char buf[1000];

  va_start(args, format);
  done = vsnprintf(buf, sizeof(buf), format, args );
  va_end(args);

  std::cout << buf << std::endl;
  return done;
}

int main() {
  if (!InitializeYojimbo()) {
    printf("error: failed to initialize Yojimbo!\n");
    return 1;
  }

  yojimbo_set_printf_function(a_printf);
  yojimbo_log_level(YOJIMBO_LOG_LEVEL_DEBUG);

  srand((unsigned int) time(nullptr));

  double time = 100.0;
  uint64_t clientId = 0;
  yojimbo::random_bytes((uint8_t*) &clientId, 8);

  yojimbo::Address serverAddress("127.0.0.1", ServerPort);

  uint8_t privateKey[yojimbo::KeyBytes];
  memset(privateKey, 0, yojimbo::KeyBytes);

  // GameClient gameClient(clientId, serverAddress, privateKey);
  // gameClient.Update(0.0f);

  // usleep(1000000);

  // gameClient.Update(0.5f);

  // usleep(1000000);

  // gameClient.Update(0.5f);

  // usleep(1000000);
  // gameClient.Update(0.5f);

  // usleep(1000000);
  // gameClient.Update(0.5f);

  // usleep(1000000);
  // gameClient.Update(0.5f);

  // usleep(1000000);
  // gameClient.Update(0.5f);

  // usleep(1000000);
  // gameClient.Update(0.5f);

  // usleep(1000000);
  // gameClient.Update(0.5f);

  // usleep(1000000);

  // gameClient.Disconnect();

  std::shared_ptr<Entity> entity = std::make_shared<Character>(1, 50.0f, 50.0f);

  std::printf("%d %d %f %f\n", entity->type, entity->id, entity->x, entity->y);

  return 0;
}
