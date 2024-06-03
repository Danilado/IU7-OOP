#ifndef DRAWER_SOLUTION_HPP
#define DRAWER_SOLUTION_HPP

#include "BaseDrawerFactory.hpp"
#include <memory>

class DrawerSolution {
public:
  template <class Tfactory, class... Args>
  static std::unique_ptr<BaseDrawer> create(Args &&...args) {
    static_assert(std::is_base_of<BaseDrawerFactory, Tfactory>::value,
                  "Tfactory must be derived from AbstractFactory");
    std::shared_ptr<BaseDrawerFactory> factory =
        std::make_shared<Tfactory>(std::forward<Args>(args)...);
    return factory->create();
  }
};

#endif
