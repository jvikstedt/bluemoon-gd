#include "Character.hpp"

Character::Character(int id, float x, float y) :
  Entity(100, id, x, y) { }


template <typename Stream>
bool Character::Serialize(Stream& stream) {
  serialize_int(stream, type, 0, 512);
  serialize_int(stream, id, 0, 512);
  serialize_float(stream, x);
  serialize_float(stream, y);
  return true;
}
