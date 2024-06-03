#ifndef BASE_CAMERA_HPP
#define BASE_CAMERA_HPP

#include "InvisibleObject.hpp"

class BasePTSCAdapter;

class BaseCamera : public InvisibleObject {
  friend BasePTSCAdapter;
};

#endif
