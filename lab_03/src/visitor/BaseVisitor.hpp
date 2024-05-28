#ifndef BASE_VISITOR_HPP
#define BASE_VISITOR_HPP

#include "BaseCamera.hpp"
#include "BaseModel.hpp"
#include "Object.hpp"
#include "OrthogonalCamera.hpp"
#include "ProjectionCamera.hpp"
#include "WireframeModel.hpp"

class BaseVisitor {
public:
  ~BaseVisitor() = default;

  virtual void visit(Object &ref) = 0;
  virtual void visit(WireframeModel &ref) = 0;
  virtual void visit(OrthogonalCamera &ref) = 0;
  virtual void visit(ProjectionCamera &ref) = 0;
};

#endif
