#include "Entity.hpp"

Entity::Entity(int type, int id, float x, float y) :
  type(type),
  id(id),
  x(x),
  y(y) {}

void Entity::Update(float delta) {
}
