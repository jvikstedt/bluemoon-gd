#pragma once

#include "Entity.hpp"

class Character : public Entity {
public:
  Character(int id, float x, float y);

  template <typename Stream>
  bool Serialize(Stream& stream);

  YOJIMBO_VIRTUAL_SERIALIZE_FUNCTIONS();
};
