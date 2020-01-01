#pragma once

#include <Godot.hpp>
#include <Node2D.hpp>

namespace godot {

class GDBluemoon : public Node2D {
	GODOT_CLASS(GDBluemoon, Node2D)

private:
	String _data;

public:
	static void _register_methods();

	void _init();

	void set_data(String new_data);
	String get_data() const;

	String a_method();
};

}
