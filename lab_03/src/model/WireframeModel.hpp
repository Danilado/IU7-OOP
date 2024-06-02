#ifndef WIREFRAME_MODEL_HPP
#define WIREFRAME_MODEL_HPP

#include "BaseModel.hpp"
#include "JSONStringifyVisitor.hpp"
#include "RenderVisitor.hpp"
#include "RotateObjectVisitor.hpp"
#include "ScaleObjectVisitor.hpp"
#include "TransformObjectVisitor.hpp"
#include "TranslateObjectVisitor.hpp"

class WireframeModel : public BaseModel {
  friend JsonStringifyVisitor;
  friend RenderVisitor;
  friend RotateObjectVisitor;
  friend ScaleObjectVisitor;
  friend TransformObjectVisitor;
  friend TranslateObjectVisitor;

public:
  void accept(BaseVisitor &vis) override;
};

#endif
