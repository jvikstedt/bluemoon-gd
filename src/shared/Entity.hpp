#pragma once

class Entity {
public:
  int type;
  int id;
  float x;
  float y;

  explicit Entity(int type, int id, float x, float y);
  void Update(float delta);

  template <typename Stream>
  bool Serialize(Stream& stream);
};
