#include <yojimbo.h>
#include "gdbluemoon.hpp"
#include "../client/GameClient.hpp"
#include "../client/logger.hpp"

const int SERVER_PORT = 40000;

void GDBluemoon::_register_methods() {
  register_method("_process", &GDBluemoon::_process);
  register_method("_ready", &GDBluemoon::_ready);
}

int GDBluemoon::GodotPrint(const char *format, ...) {
  va_list args;
  int done;
  char buffer[1000];

  va_start(args, format);
  done = vsnprintf(buffer, sizeof(buffer), format, args);
  va_end(args);

  godot::Godot::print(buffer);
  return done;
}

void GDBluemoon::_init() { }

void GDBluemoon::_ready() {
  if (!InitializeYojimbo()) {
    printf("error: failed to initialize Yojimbo!\n");
    return;
  }

  client_set_printf_function(GodotPrint);
  yojimbo_set_printf_function(GodotPrint);
  yojimbo_log_level(YOJIMBO_LOG_LEVEL_INFO);

  srand((unsigned int) time(nullptr));

  uint64_t clientId = 0;
  yojimbo::random_bytes((uint8_t*) &clientId, 8);

  yojimbo::Address serverAddress("127.0.0.1", SERVER_PORT);

  uint8_t privateKey[yojimbo::KeyBytes];
  memset(privateKey, 0, yojimbo::KeyBytes);

  MessageHandler *messageHandler = this;
  gameClient = std::make_unique<GameClient>(clientId, 1, serverAddress, privateKey, messageHandler);
}

void GDBluemoon::_process(float delta) {
  if (gameClient == nullptr) {
    GodotPrint("No client setup...");
    return;
  }

  gameClient->Update(delta);
}

void GDBluemoon::HandleMessage(const yojimbo::Message &message) {
  GodotPrint("received message of type: %d\n", message.GetType());
}

// #include <ResourceLoader.hpp>
// #include <PackedScene.hpp>
// #include <String.hpp>

// register_method("Initialize", &GDBluemoon::Initialize);
// register_method("Update", &GDBluemoon::Update);

// register_property<GDBluemoon, String>("data", &GDBluemoon::set_data, &GDBluemoon::get_data, String("Hello world"));

// switch (message->GetType()) {
//   case (int)GameMessageType::PLAYER_SYNC:
//     // ProcessPlayerSyncMessage((PlayerSync*)message);
//     messageHandler->PlayerSyncMsg((PlayerSync*)message);
//     break;
//   default:
//     break;
// }
// auto loader = godot::ResourceLoader::get_singleton();
// godot::Ref<godot::PackedScene> playerScene = loader->load("res://Player.tscn", "PackedScene");

// Node* playersNode = get_node("../Players");
// // godot::Array children = playersNode->get_children();
// std::vector<Player> players = playerSync->players;

// for (int i = 0; i < players.size(); i++) {
//   std::string name = std::to_string(players[i].id);
//   char const *namechar = name.c_str();
//   Node2D* p = (Node2D*)playersNode->get_node_or_null(namechar);
//   if (p == nullptr) {
//     Node2D* node = (Node2D*)playerScene->instance();
//     node->set_position(godot::Vector2(players[i].x, players[i].y));
//     node->set_name(namechar);
//     playersNode->add_child(node);
//   } else {
//     p->set_position(godot::Vector2(players[i].x, players[i].y));
//   }
// }


// int64_t childCount = playersNode->get_child_count();
// for (int64_t x = 0; x < childCount; x++) {
//   Node2D* player = (Node2D*)playersNode->get_child(x);
//   player->set_position(godot::Vector2(200, 200));

//   godot::Godot::print(player->get_name());
// }

// int playersSize = playerSync->players.size();
// GodotPrint("Received PlayerSync with %d players\n", playersSize);
// for (int i = 0; i < playersSize; i++) {
//   Player p = playerSync->players[i];
//   GodotPrint("Player(%d) x: %f y: %f\n", p.id, p.x, p.y);
// }


// auto loader = godot::ResourceLoader::get_singleton();
// godot::Ref<godot::PackedScene> playerScene = loader->load("res://Player.tscn", "PackedScene");
// Node* playersNode = get_node("../Players");
// if (playerScene.is_valid()) {
//   Node* node = playerScene->instance();
//   node->set_meta("id", 1);
//   playersNode->add_child(node);
// }
