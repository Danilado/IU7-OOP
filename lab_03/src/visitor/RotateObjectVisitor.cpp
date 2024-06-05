#include "RotateObjectVisitor.hpp"
#include "MyMath.hpp"
#include "Object.hpp"
#include "OrthogonalCamera.hpp"
#include "ProjectionCamera.hpp"
#include "Scene.hpp"
#include "TransformationMatrix.hpp"
#include "WireframeModel.hpp"

void RotateObjectVisitor::rotate_object_around_origin(Object &ref) {
  std::shared_ptr<TransformationMatrix> transf = ref.getTransformation();
  transf->translate(-origin);
  if (deg)
    transf->rotate_deg(rotation);
  else
    transf->rotate(rotation);
  transf->translate(origin);
}

RotateObjectVisitor::RotateObjectVisitor(double ax, double ay, double az,
                                         bool deg)
    : rotation(ax, ay, az), deg(deg) {}

RotateObjectVisitor::RotateObjectVisitor(double ox, double oy, double oz,
                                         double ax, double ay, double az,
                                         bool deg)
    : rotation(ax, ay, az), origin(ox, oy, oz), deg(deg) {}

RotateObjectVisitor::RotateObjectVisitor(const Point3D &angles, bool deg)
    : rotation(angles), deg(deg) {}

RotateObjectVisitor::RotateObjectVisitor(const Point3D &origin,
                                         const Point3D &angles, bool deg)
    : origin(origin), rotation(angles), deg(deg) {}

void RotateObjectVisitor::visit(WireframeModel &ref) {
  rotate_object_around_origin(ref);
}

void RotateObjectVisitor::visit(OrthogonalCamera &ref) {
  rotate_object_around_origin(ref);
}

void RotateObjectVisitor::visit(ProjectionCamera &ref) {
  rotate_object_around_origin(ref);
}

void RotateObjectVisitor::visit(Scene &ref) {
  for (auto &[_, objptr] : ref)
    if (objptr->isVisible())
      rotate_object_around_origin(*objptr);
}
