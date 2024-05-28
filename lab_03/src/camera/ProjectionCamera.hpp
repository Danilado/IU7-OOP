#ifndef PROJECTION_CAMERA_HPP
#define PROJECTION_CAMERA_HPP

#include "BaseCamera.hpp"

class ProjectionCamera : public BaseCamera {
public:
  void accept(std::shared_ptr<BaseVisitor> vis) override;
};

#endif
