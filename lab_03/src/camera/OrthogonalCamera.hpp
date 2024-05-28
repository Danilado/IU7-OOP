#ifndef ORTHOGONAL_CAMERA_HPP
#define ORTHOGONAL_CAMERA_HPP

#include "BaseCamera.hpp"

class OrthogonalCamera : public BaseCamera {
public:
  void accept(std::shared_ptr<BaseVisitor> vis) override;
};

#endif
