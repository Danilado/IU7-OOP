#ifndef ROTATE_OBJECT_VISITOR_HPP
#define ROTATE_OBJECT_VISITOR_HPP

#include "BaseVisitor.hpp"
#include "Point3D.hpp"

class RotateObjectVisitor : public BaseVisitor {
private:
  std::unique_ptr<TransformationMatrix> transf;

public:
  RotateObjectVisitor() = delete;
  RotateObjectVisitor(double ax, double ay, double az, bool deg = false);
  RotateObjectVisitor(double ox, double oy, double oz, double ax, double ay,
                      double az, bool deg = false);
  RotateObjectVisitor(const Point3D &angles, bool deg = false);
  RotateObjectVisitor(const Point3D &origin, const Point3D &angles,
                      bool deg = false);

  void visit(Object &ref) override;
  void visit(WireframeModel &ref) override;
  void visit(OrthogonalCamera &ref) override;
  void visit(ProjectionCamera &ref) override;
};

#endif
