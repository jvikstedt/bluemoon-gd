#pragma once

#include <vector>
#include <memory>
#include <yojimbo.h>

#include "Entity.hpp"
#include "Character.hpp"

// TODO investigate serialize_int min and max values

class EntitySync : public yojimbo::Message {
public:
  std::vector<std::shared_ptr<Entity>> entities;

  EntitySync() {}

  template <typename Stream>
    bool Serialize(Stream& stream) {
      if (Stream::IsReading) {
        int entitiesSize = 0;
        int type = 0;
        int id = 0;
        float x = 0;
        float y = 0;

        serialize_int(stream, entitiesSize, 0, 512);
        for (int i = 0; i < entitiesSize; i++) {
          auto entity = std::make_shared<Character>(id, x, y);
          entity->SerializeInternal(stream);
          entities.push_back(entity);
        }
      }
      if (Stream::IsWriting) {
        int entitiesSize = entities.size();
        serialize_int(stream, entitiesSize, 0, 512);
        for (int i = 0; i < entitiesSize; i++) {
          entities[i]->SerializeInternal(stream);
        }
      }
      return true;
    }

  YOJIMBO_VIRTUAL_SERIALIZE_FUNCTIONS();
};
