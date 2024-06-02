#ifndef TRANSLATE_OBJECT_VISITOR_HPP
#define TRANSLATE_OBJECT_VISITOR_HPP

#include "BaseVisitor.hpp"
#include "Point3D.hpp"
#include "TransformationMatrix.hpp"

class TranslateObjectVisitor : public BaseVisitor {
private:
  std::unique_ptr<TransformationMatrix> transf;

public:
  TranslateObjectVisitor() = delete;
  TranslateObjectVisitor(double dx, double dy, double dz);
  TranslateObjectVisitor(const Point3D &offset);

  void visit(WireframeModel &ref) override;
  void visit(OrthogonalCamera &ref) override;
  void visit(ProjectionCamera &ref) override;
  void visit(Scene &ref) override;
};

#endif
