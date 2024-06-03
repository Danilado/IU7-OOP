#ifndef BASE_MODEL_HPP
#define BASE_MODEL_HPP

#include "BaseVisitor.hpp"
#include "JSONStringifyVisitor.hpp"

#include "BaseModelData.hpp"
#include "Object.hpp"

class RenderVisitor;
class NlohmannJsonAdapter;

class BaseModel : public Object {
  friend JsonStringifyVisitor;
  friend RenderVisitor;
  friend NlohmannJsonAdapter;

protected:
  std::unique_ptr<BaseModelData> data;

public:
};

#endif
