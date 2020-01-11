#include "entity.hpp"


Entity::Entity(float x, float y, float width, float height) :
  m_x(x), m_y(y), m_width(width), m_height(height) {}

void Entity::Update(float delta) {
  m_x = m_x + delta * 1;
  m_y = m_y + delta * 2;
}

float Entity::GetX() {
  return m_x;
}

float Entity::GetY() {
  return m_y;
}

float Entity::GetWidth() {
  return m_width;
}

float Entity::GetHeight() {
  return m_height;
}

void Entity::AddNode(Node* node) {
  m_nodes.push_back(node);
}
