#ifndef SCALE_OBJECT_VISITOR_HPP
#define SCALE_OBJECT_VISITOR_HPP

#include "BaseVisitor.hpp"
#include "Point3D.hpp"
#include <memory>

class TransformationMatrix;
class Object;

class ScaleObjectVisitor : public BaseVisitor {
private:
  Point3D scale;
  Point3D origin;

  void scale_object_around_origin(Object &ref);

public:
  ScaleObjectVisitor() = delete;
  ScaleObjectVisitor(double kx, double ky, double kz);
  ScaleObjectVisitor(double ox, double oy, double oz, double kx, double ky,
                     double kz);
  explicit ScaleObjectVisitor(const Point3D &scale);
  ScaleObjectVisitor(const Point3D &offset, const Point3D &scale);

  void visit(WireframeModel &ref) override;
  void visit(OrthogonalCamera &ref) override;
  void visit(ProjectionCamera &ref) override;
  void visit(Scene &ref) override;
};

#endif
