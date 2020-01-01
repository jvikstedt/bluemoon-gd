#include <yojimbo.h>
#include "gdbluemoon.hpp"
#include "../shared/ClientServerConfig.hpp"
#include "ClientAdapter.hpp"
#include "GameClient.hpp"

const int ServerPort = 40000;

void godot::GDBluemoon::_register_methods() {
  register_method("_process", &GDBluemoon::_process);
	// register_method("Initialize", &GDBluemoon::Initialize);
	// register_method("Update", &GDBluemoon::Update);

	// register_property<GDBluemoon, String>("data", &GDBluemoon::set_data, &GDBluemoon::get_data, String("Hello world"));
}

int godot::GDBluemoon::GodotPrint(const char *format, ... ) {
  va_list args;
  int done;
  char buffer[1000];

  va_start(args, format);
  done = vsnprintf(buffer, sizeof(buffer), format, args);
  va_end(args);

  Godot::print(buffer);
  return done;
}

void godot::GDBluemoon::_init() {
  if (!InitializeYojimbo()) {
    printf("error: failed to initialize Yojimbo!\n");
  }

  yojimbo_set_printf_function(GodotPrint);
  yojimbo_log_level(YOJIMBO_LOG_LEVEL_INFO);

  srand((unsigned int) time(NULL));

  double time = 100.0;
  uint64_t clientId = 0;
  yojimbo::random_bytes((uint8_t*) &clientId, 8);

  yojimbo::Address serverAddress("127.0.0.1", ServerPort);

  uint8_t privateKey[yojimbo::KeyBytes];
  memset(privateKey, 0, yojimbo::KeyBytes);

  // TODO Remove memory
  gameClient = new GameClient(clientId, serverAddress, privateKey);
  // GameClient gameClient(clientId, serverAddress, privateKey);
}

void godot::GDBluemoon::_process(float delta) {
  if (gameClient == NULL) {
    Godot::print("No client setup...");
    return;
  }

  gameClient->Update(delta);
}
