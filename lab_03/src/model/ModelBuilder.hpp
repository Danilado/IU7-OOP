#ifndef MODEL_BUILDER_HPP
#define MODEL_BUILDER_HPP

#include "BaseModelDataSource.hpp"
#include "ObjectBuilder.hpp"

class ModelDirector : public BaseObjectDirector {
  ObjectPtr create(BaseSource &src) override;
};

class ModelBuilder : public BaseObjectBuilder {
  void buildNodes(BaseModelDataSource &src, Object &dst);
  void buildEdges(BaseModelDataSource &src, Object &dst);
};

#endif
