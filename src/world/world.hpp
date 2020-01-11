#pragma once

#include <vector>
#include <memory>
#include "node.hpp"
#include "entity.hpp"

class World {
public:
  World(int num_rows, int num_cols, int node_width, int node_height);
  ~World();
  std::vector<std::vector<Node*>> GetMap() const;
  std::vector<std::shared_ptr<Entity>> GetEntities() const;

  void Update(float delta);
  void AddEntity(std::shared_ptr<Entity> entity);

  const int m_num_rows;
  const int m_num_cols;

  const int m_node_width;
  const int m_node_height;

private:
  std::vector<std::vector<Node*>> m_map;
  std::vector<std::shared_ptr<Entity>> m_entities;
};
