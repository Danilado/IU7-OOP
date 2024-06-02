#ifndef BASE_CAMERA_HPP
#define BASE_CAMERA_HPP

#include "Object.hpp"

class BasePTSCAdapter;

class BaseCamera : public Object {
  friend BasePTSCAdapter;
};

#endif
