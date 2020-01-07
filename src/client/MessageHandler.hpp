#pragma once

#include <yojimbo.h>

class MessageHandler {
public:
  virtual void HandleMessage(const yojimbo::Message* message) = 0;
};
