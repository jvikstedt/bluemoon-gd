#pragma once

#include <vector>
#include <memory>
#include "entity.hpp"

class Entity;
class Node {
public:
  Node(int x, int y, int width, int height);
  const int m_x;
  const int m_y;
  const int m_width;
  const int m_height;

  std::vector<std::shared_ptr<Entity>> GetEntities() const;
  void AddEntity(std::shared_ptr<Entity> entity);

private:
  std::vector<std::shared_ptr<Entity>> m_entities;
};
