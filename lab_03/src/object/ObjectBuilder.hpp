#ifndef OBJECT_BUILDER_HPP
#define OBJECT_BUILDER_HPP

#include "BaseSource.hpp"
#include "Object.hpp"

class BaseObjectDirector {
public:
  virtual std::unique_ptr<Object> create(BaseSource &src) = 0;
};

class BaseObjectBuilder {
public:
  std::unique_ptr<TransformationMatrix> buildTransformMatrix(BaseSource &src);
};

#endif
