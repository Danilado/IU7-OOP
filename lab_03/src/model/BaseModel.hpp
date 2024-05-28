#ifndef BASE_MODEL_HPP
#define BASE_MODEL_HPP

#include "BaseModelData.hpp"
#include "Object.hpp"

#include "JSONStringifyVisitor.hpp"

class BaseModel : public Object {
  friend JSONStringifyVisitor;

private:
  std::unique_ptr<BaseModelData> data;

public:
  void accept(BaseVisitor) override;
};

#endif
