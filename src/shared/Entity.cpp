#include "Entity.hpp"

Entity::Entity(int type, int id, float x, float y) :
  type(type),
  id(id),
  x(x),
  y(y) {}

void Entity::Update(float delta) {
}

template <typename Stream>
bool Entity::Serialize(Stream& stream) {
  serialize_int(stream, type, 0, 512);
  serialize_int(stream, id, 0, 512);
  serialize_float(stream, x);
  serialize_float(stream, y);
  return true;
}
