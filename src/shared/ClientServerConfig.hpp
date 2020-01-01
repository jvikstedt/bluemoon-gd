#pragma once

#include <yojimbo.h>

enum class GameChannel {
  RELIABLE,
  UNRELIABLE,
  COUNT
};

struct ClientServerConfig : public yojimbo::ClientServerConfig {
  ClientServerConfig() {
    numChannels = 2;
    channel[(int) GameChannel::RELIABLE].type = yojimbo::CHANNEL_TYPE_RELIABLE_ORDERED;
    channel[(int) GameChannel::UNRELIABLE].type = yojimbo::CHANNEL_TYPE_UNRELIABLE_UNORDERED;
  }
};
