#ifndef CAMERA_BUILDER_HPP
#define CAMERA_BUILDER_HPP

#include "ObjectBuilder.hpp"

class CameraDirector : public BaseObjectDirector {
public:
  ObjectPtr create(BaseSource &src) override;
};

class CameraBuilder : public BaseObjectBuilder {};

#endif
