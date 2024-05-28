#ifndef WIREFRAME_MODEL_HPP
#define WIREFRAME_MODEL_HPP

#include "BaseModel.hpp"
#include "BaseVisitor.hpp"

class WireframeModel : public BaseModel {
  friend BaseVisitor;

public:
  void accept(std::shared_ptr<BaseVisitor> vis) override;
};

#endif
