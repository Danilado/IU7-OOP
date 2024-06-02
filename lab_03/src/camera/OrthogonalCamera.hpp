#ifndef ORTHOGONAL_CAMERA_HPP
#define ORTHOGONAL_CAMERA_HPP

#include "BaseCamera.hpp"
#include "BaseVisitor.hpp"

class OrthogonalCamera : public BaseCamera {
public:
  void accept(BaseVisitor &vis) override;
};

#endif
