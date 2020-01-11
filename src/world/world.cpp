#include "world.hpp"

World::World(int num_rows, int num_cols, int node_width, int node_height) :
  m_num_rows(num_rows),
  m_num_cols(num_cols),
  m_node_width(node_width),
  m_node_height(node_height),
  m_map(num_rows, std::vector<Node*>(num_cols, nullptr))
{
  for (int y = 0; y < m_num_rows; y++) {
    for (int x = 0; x < m_num_cols; x++) {
      m_map[y][x] = new Node(x, y, m_node_width, m_node_height);
    }
  }
}

World::~World() {
  for (int y = 0; y < m_num_rows; y++) {
    for (int x = 0; x < m_num_cols; x++) {
      delete m_map[y][x];
    }
  }
}

std::vector<std::vector<Node*>> World::GetMap() const {
  return m_map;
}

std::vector<std::shared_ptr<Entity>> World::GetEntities() const {
  return m_entities;
}

void World::Update(float delta) {
  for (auto entity : m_entities) {
    entity->Update(delta);
  }
}

void World::AddEntity(std::shared_ptr<Entity> entity) {
  float entity_x = entity->GetX();
  float entity_y = entity->GetY();
  float entity_width = entity->GetWidth();
  float entity_height = entity->GetHeight();

  int top_left_node_x = entity_x / m_node_width;
  int top_left_node_y = entity_y / m_node_height;

  int bottom_right_node_x = (entity_x + entity_width) / m_node_width;
  int bottom_right_node_y = (entity_y + entity_height) / m_node_height;

  for (int x = top_left_node_x; x <= bottom_right_node_x; x++) {
    for (int y = top_left_node_y; y <= bottom_right_node_y; y++) {
      Node* node = m_map[y][x];
      node->AddEntity(entity);
      entity->AddNode(node);
    }
  }

  m_entities.push_back(entity);
}
