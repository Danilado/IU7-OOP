#ifndef DRAW_MANAGER_HPP
#define DRAW_MANAGER_HPP

#include "BaseDrawer.hpp"
#include "DrawerSolution.hpp"

class DrawManager {
private:
  std::unique_ptr<BaseDrawer> ctx;

public:
  void renderScene();
  void clear();
};

#endif
