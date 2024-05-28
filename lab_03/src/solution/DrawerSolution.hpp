#ifndef DRAWER_SOLUTION_HPP
#define DRAWER_SOLUTION_HPP

#include "BaseDrawer.hpp"
#include "BaseDrawerFactory.hpp"
#include "QtDrawerFactory.hpp"
#include <map>
#include <memory>

class DrawerSolution {
public:
  DrawerSolution();
  ~DrawerSolution() = default;
  enum class DrawerType { QT = 1 };
  BaseDrawer create(DrawerType dtype);

private:
  std::map<DrawerType, std::shared_ptr<BaseDrawerFactory>> FactoryMap;
};

#endif
