#include "node.hpp"


Node::Node(int x, int y, int width, int height) :
  m_x(x), m_y(y), m_width(width), m_height(height) {}

std::vector<std::shared_ptr<Entity>> Node::GetEntities() const {
  return m_entities;
}

void Node::AddEntity(std::shared_ptr<Entity> entity) {
  m_entities.push_back(entity);
}
