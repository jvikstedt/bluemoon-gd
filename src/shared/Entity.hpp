#pragma once

#include <yojimbo.h>

class Entity : public yojimbo::Serializable {
public:
  int type;
  int id;
  float x;
  float y;

  explicit Entity(int type, int id, float x, float y);
  void Update(float delta);

  virtual bool SerializeInternal(yojimbo::ReadStream & stream) = 0;
  virtual bool SerializeInternal(yojimbo::WriteStream & stream) = 0;
  virtual bool SerializeInternal(yojimbo::MeasureStream & stream) = 0;
};
