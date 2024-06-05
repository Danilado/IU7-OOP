#ifndef ORTHOGONAL_CAMERA_HPP
#define ORTHOGONAL_CAMERA_HPP

#include "BaseCamera.hpp"
#include "BaseVisitor.hpp"

class OrthogonalCameraDirector;

class OrthogonalCamera : public BaseCamera {
  friend OrthogonalCameraDirector;

public:
  OrthogonalCamera();
  void accept(BaseVisitor &vis) override;
  std::unique_ptr<Object> clone() const override;
};

#endif
