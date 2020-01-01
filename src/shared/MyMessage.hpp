#pragma once

#include <yojimbo.h>

class MyMessage : public yojimbo::Message {
public:
  int m_data;

  MyMessage() :
    m_data(0) {}

  template <typename Stream>
    bool Serialize(Stream& stream) {
      serialize_int(stream, m_data, 0, 512);
      return true;
    }

  YOJIMBO_VIRTUAL_SERIALIZE_FUNCTIONS();
};
