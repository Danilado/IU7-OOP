#ifndef BASE_DRAWER_FACTORY_HPP
#define BASE_DRAWER_FACTORY_HPP

#include "BaseDrawer.hpp"
#include <memory>

class BaseDrawerFactory {
private:
public:
  virtual std::unique_ptr<BaseDrawer> create() = 0;
};

#endif
