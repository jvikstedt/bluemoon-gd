#pragma once

#include <memory>
#include <Godot.hpp>
#include <Node2D.hpp>
#include <yojimbo.h>
#include "../client/GameClient.hpp"
#include "../client/MessageHandler.hpp"

class GDBluemoon : public godot::Node2D, MessageHandler {
  GODOT_CLASS(GDBluemoon, Node2D)

private:
  std::unique_ptr<GameClient> gameClient;

  static int GodotPrint(const char *format, ... );

public:
  static void _register_methods();

  void _init();
  void _process(float delta);
  void _ready();

  void HandleMessage(const yojimbo::Message &message) override;
};
