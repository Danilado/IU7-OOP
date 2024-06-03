#ifndef DRAW_MANAGER_HPP
#define DRAW_MANAGER_HPP

#include "BaseDrawer.hpp"
#include "DrawerSolution.hpp"

class DrawManager {
private:
  std::shared_ptr<BaseDrawer> ctx;
  void validateDrawer();

public:
  DrawManager() : ctx(nullptr) {}
  explicit DrawManager(std::shared_ptr<BaseDrawer> drawer) : ctx(drawer) {}

  void setDrawer(std::shared_ptr<BaseDrawer>);
  void renderScene();
  void clear();

  DrawManager(const DrawManager &) = delete;
  DrawManager &operator=(const DrawManager &) = delete;
};

#endif
