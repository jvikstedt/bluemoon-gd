#include "gdbluemoon.hpp"
#include <yojimbo.h>

using namespace godot;

void GDBluemoon::_register_methods() {
	register_method("a_method", &GDBluemoon::a_method);

	register_property<GDBluemoon, String>("data", &GDBluemoon::set_data, &GDBluemoon::get_data, String("Hello world"));
}

void GDBluemoon::_init() {
}

void GDBluemoon::set_data(String new_data) {
	_data = new_data;
}

String GDBluemoon::get_data() const {
	return _data;
}

String GDBluemoon::a_method() {
  if (!InitializeYojimbo()) {
    return String("error: failed to initialize Yojimbo!\n");
  } else {
    return String("OK: succesfully initialized Yojimbo!\n");
  }
}
