#ifndef ORTHOGONAL_CAMERA_BUILDER_HPP
#define ORTHOGONAL_CAMERA_BUILDER_HPP

#include "ObjectBuilder.hpp"

class OrthogonalCameraDirector : public BaseObjectDirector {
public:
  std::unique_ptr<Object> create(BaseSource &src) override;
};

class OrthogonalCameraBuilder : public BaseObjectBuilder {};

#endif
