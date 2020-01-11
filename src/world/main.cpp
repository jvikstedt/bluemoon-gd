#include <iostream>
#include <chrono>
#include <unistd.h>

#include "world.hpp"
#include "entity.hpp"

const int NUM_ROWS = 3;
const int NUM_COLS = 3;
const int NODE_WIDTH = 10;
const int NODE_HEIGHT = 10;

int main() {
  std::cout << "Hello world" << std::endl;

  World world(NUM_ROWS, NUM_COLS, NODE_WIDTH, NODE_HEIGHT);

  typedef std::chrono::high_resolution_clock Time;
  typedef std::chrono::milliseconds ms;
  typedef std::chrono::duration<float> fsec;
  auto t0 = Time::now();
  auto t1 = Time::now();

  std::shared_ptr<Entity> entity = std::make_shared<Entity>(8.0, 0.0, 5.0, 5.0);
  world.AddEntity(entity);

  while (true) {
    t1 = Time::now();
    fsec fs = t1 - t0;
    ms d = std::chrono::duration_cast<ms>(fs);

    world.Update(fs.count());
    std::printf("Entity new position: x(%f) y(%f)\n", entity->GetX(), entity->GetY());

    for (auto rows : world.GetMap()) {
      for (auto node : rows) {
        std::printf("x:%d,y:%d,e:%d   ", node->m_x, node->m_y, int(node->GetEntities().size()));
      }
      std::printf("\n");
    }

    t0 = t1;
    usleep(100000);
  }


  // while(true) {
  //   auto currentTime = std::chrono::steady_clock::now();
  //   auto elapsed = previousTime - currentTime;

  //   auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();
  //   std::cout << elapsed_ms << std::endl;

  //   previousTime = currentTime;
  // }

  return 0;
}
