#pragma once

class Player {
  public:
    int id;
    float x;
    float y;

    Player();
    Player(int id, float x, float y) : id(id), x(x), y(y) {}
};
