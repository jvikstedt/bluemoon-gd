#pragma once

#include "node.hpp"

class Node;
class Entity {
public:
  Entity(float x, float y, float width, float height);
  void Update(float delta);
  float GetX();
  float GetY();
  float GetWidth();
  float GetHeight();
  void AddNode(Node* node);

private:
  float m_x;
  float m_y;
  float m_width;
  float m_height;

  std::vector<Node*> m_nodes;
};
