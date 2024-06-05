#ifndef PROJECTION_CAMERA_BUILDER_HPP
#define PROJECTION_CAMERA_BUILDER_HPP

#include "ObjectBuilder.hpp"

class ProjectionCameraDirector : public BaseObjectDirector {
public:
  std::unique_ptr<Object> create(BaseSource &src) override;
};

class ProjectionCameraBuilder : public BaseObjectBuilder {};

#endif
