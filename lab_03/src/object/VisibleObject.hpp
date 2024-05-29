#ifndef VISIBLE_OBJECT_HPP
#define VISIBLE_OBJECT_HPP

#include "Object.hpp"

class VisibleObject : public Object {
public:
  bool constexpr isVisible(void) const noexcept override { return true; }
};

#endif
