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
  *transf -= *origin;
  *transf *= *rotation;
  *transf += *origin;
}

RotateObjectVisitor::RotateObjectVisitor(double ax, double ay, double az,
                                         bool deg) {
  if (deg)
    rotation->rotate_deg(ax, ay, az);
  else
    rotation->rotate(ax, ay, az);
}

RotateObjectVisitor::RotateObjectVisitor(double ox, double oy, double oz,
                                         double ax, double ay, double az,
                                         bool deg) {
  RotateObjectVisitor(ax, ay, az, deg);
  origin->translate(ox, oy, oz);
}

RotateObjectVisitor::RotateObjectVisitor(const Point3D &angles, bool deg) {
  if (deg)
    rotation->rotate_deg(angles);
  else
    rotation->rotate(angles);
}

RotateObjectVisitor::RotateObjectVisitor(const Point3D &origin,
                                         const Point3D &angles, bool deg) {
  RotateObjectVisitor(angles, deg);
  this->origin->translate(origin);
}

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
    rotate_object_around_origin(*objptr);
}
