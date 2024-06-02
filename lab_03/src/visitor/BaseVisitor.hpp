#ifndef BASE_VISITOR_HPP
#define BASE_VISITOR_HPP

class WireframeModel;
class OrthogonalCamera;
class ProjectionCamera;
class Scene;

class BaseVisitor {
public:
  ~BaseVisitor() = default;

  virtual void visit(WireframeModel &ref) = 0;
  virtual void visit(OrthogonalCamera &ref) = 0;
  virtual void visit(ProjectionCamera &ref) = 0;
  virtual void visit(Scene &ref) = 0;
};

#endif
