#pragma once

#include <vector>
#include <yojimbo.h>

#include "Player.hpp"

// TODO investigate serialize_int min and max values

class PlayerSync : public yojimbo::Message {
public:
  std::vector<Player> players;

  PlayerSync() {}

  template <typename Stream>
    bool Serialize(Stream& stream) {
      if (Stream::IsReading) {
        int playersSize = 0;
        int id = 0;
        float x = 0;
        float y = 0;

        serialize_int(stream, playersSize, 0, 512);
        for (int i = 0; i < playersSize; i++) {
          serialize_int(stream, id, 0, 512);
          serialize_float(stream, x);
          serialize_float(stream, y);

          Player p(id, x, y);
          players.push_back(p);
        }
      }
      if (Stream::IsWriting) {
        int playersSize = players.size();
        serialize_int(stream, playersSize, 0, 512);
        for (int i = 0; i < playersSize; i++) {
          int id = players[i].id;
          float x = players[i].x;
          float y = players[i].y;

          serialize_int(stream, id, 0, 512);
          serialize_float(stream, x);
          serialize_float(stream, y);
        }
      }
      return true;
    }

  YOJIMBO_VIRTUAL_SERIALIZE_FUNCTIONS();
};
