#ifndef PROJECTION_CAMERA_HPP
#define PROJECTION_CAMERA_HPP

#include "BaseCamera.hpp"
#include "BaseVisitor.hpp"

class ProjectionCamera : public BaseCamera {
public:
  ProjectionCamera() = default;
  ~ProjectionCamera() = default;
  void accept(BaseVisitor &vis) override;
  std::unique_ptr<Object> clone() const override;
};

#endif
