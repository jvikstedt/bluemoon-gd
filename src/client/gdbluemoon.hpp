#pragma once

#include <memory>
#include <Godot.hpp>
#include <Node2D.hpp>
#include <yojimbo.h>
#include "GameClient.hpp"

namespace godot {

class GDBluemoon : public Node2D {
	GODOT_CLASS(GDBluemoon, Node2D)

private:
  std::unique_ptr<GameClient> gameClient;

  static int GodotPrint(const char *format, ... );

public:
	static void _register_methods();

	void _init();
  void _process(float delta);
};

}
