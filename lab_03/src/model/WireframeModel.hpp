#ifndef WIREFRAME_MODEL_HPP
#define WIREFRAME_MODEL_HPP

#include "BaseModel.hpp"

class RenderVisitor;
class RotateObjectVisitor;
class ScaleObjectVisitor;
class TransformObjectVisitor;
class TranslateObjectVisitor;
class WireframeModelDirector;

class WireframeModel : public BaseModel {
  friend RenderVisitor;
  friend RotateObjectVisitor;
  friend ScaleObjectVisitor;
  friend TransformObjectVisitor;
  friend TranslateObjectVisitor;
  friend WireframeModelDirector;

public:
  void accept(BaseVisitor &vis) override;
};

#endif
