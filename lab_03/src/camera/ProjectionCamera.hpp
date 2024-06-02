#ifndef PROJECTION_CAMERA_HPP
#define PROJECTION_CAMERA_HPP

#include "BaseCamera.hpp"
#include "BaseVisitor.hpp"

class ProjectionCamera : public BaseCamera {
public:
  void accept(BaseVisitor &vis) override;
};

#endif
