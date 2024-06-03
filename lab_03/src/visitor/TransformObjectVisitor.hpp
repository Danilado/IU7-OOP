#ifndef TRANSFORM_OBJECT_VISITOR_HPP
#define TRANSFORM_OBJECT_VISITOR_HPP

#include "BaseVisitor.hpp"
#include "Point3D.hpp"
#include <memory>

class TransformationMatrix;
class Object;

class TransformObjectVisitor : public BaseVisitor {
private:
  std::shared_ptr<TransformationMatrix> transf;

  void transform(Object &ref);

public:
  TransformObjectVisitor() = delete;
  TransformObjectVisitor(std::shared_ptr<TransformationMatrix> transf)
      : transf(transf) {}
  TransformObjectVisitor(const Point3D &diagonal);

  void visit(WireframeModel &ref) override;
  void visit(OrthogonalCamera &ref) override;
  void visit(ProjectionCamera &ref) override;
  void visit(Scene &ref) override;
};

#endif
