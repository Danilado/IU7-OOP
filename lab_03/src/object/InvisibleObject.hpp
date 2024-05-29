#ifndef INVISIBLE_OBJECT_HPP
#define INVISIBLE_OBJECT_HPP

#include "Object.hpp"

class InvisibleObject : public Object {
public:
  bool isVisible(void) const noexcept override { return false; }
};

#endif
