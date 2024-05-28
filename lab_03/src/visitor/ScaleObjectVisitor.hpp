#ifndef SCALE_OBJECT_VISITOR_HPP
#define SCALE_OBJECT_VISITOR_HPP

#include "BaseVisitor.hpp"
#include "Point3D.hpp"

class ScaleObjectVisitor : public BaseVisitor {
private:
  std::unique_ptr<TransformationMatrix> transf;
  std::unique_ptr<TransformationMatrix> origin;

public:
  ScaleObjectVisitor() = delete;
  ScaleObjectVisitor(double kx, double ky, double kz);
  ScaleObjectVisitor(double sx, double sy, double sz, double kx, double ky,
                     double kz);
  ScaleObjectVisitor(const Point3D &scale);
  ScaleObjectVisitor(const Point3D &offset, const Point3D &scale);

  void visit(Object &ref) override;
  void visit(WireframeModel &ref) override;
  void visit(OrthogonalCamera &ref) override;
  void visit(ProjectionCamera &ref) override;
};

#endif
