#ifndef VISIBLE_OBJECT_HPP
#define VISIBLE_OBJECT_HPP

#include "Object.hpp"

class VisibleObject : public Object {
public:
  bool isVisible(void) const noexcept override;
};

#endif
