#ifndef WIREFRAME_MODEL_DIRECTOR_HPP
#define WIREFRAME_MODEL_DIRECTOR_HPP

#include "ObjectBuilder.hpp"
#include "WireframeModel.hpp"

class WireframeModelDirector : public BaseObjectDirector {
public:
  ObjectPtr create(BaseSource &src) override;
};

class WireframeModelBuilder : public BaseObjectBuilder {
public:
  std::unique_ptr<BaseModelData> buildModelData(BaseSource &src);
};

#endif
