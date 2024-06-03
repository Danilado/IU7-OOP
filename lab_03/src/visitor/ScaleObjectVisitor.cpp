#include "ScaleObjectVisitor.hpp"
#include "Object.hpp"
#include "OrthogonalCamera.hpp"
#include "ProjectionCamera.hpp"
#include "Scene.hpp"
#include "TransformationMatrix.hpp"
#include "WireframeModel.hpp"

void ScaleObjectVisitor::scale_object_around_origin(Object &ref) {
  std::shared_ptr<TransformationMatrix> transf = ref.getTransformation();
  *transf -= *origin;
  *transf *= *scales;
  *transf += *origin;
}

ScaleObjectVisitor::ScaleObjectVisitor(double kx, double ky, double kz) {
  this->scales->scale(kx, ky, kz);
}

ScaleObjectVisitor::ScaleObjectVisitor(double ox, double oy, double oz,
                                       double kx, double ky, double kz)
    : ScaleObjectVisitor(kx, ky, kz) {
  origin->translate(ox, oy, oz);
}

ScaleObjectVisitor::ScaleObjectVisitor(const Point3D &scale) {
  this->scales->scale(scale.get_x(), scale.get_y(), scale.get_z());
}

ScaleObjectVisitor::ScaleObjectVisitor(const Point3D &offset,
                                       const Point3D &scale)
    : ScaleObjectVisitor(scale) {
  origin->translate(offset);
}

void ScaleObjectVisitor::visit(WireframeModel &ref) {
  scale_object_around_origin(ref);
}

void ScaleObjectVisitor::visit(OrthogonalCamera &ref) {
  scale_object_around_origin(ref);
}

void ScaleObjectVisitor::visit(ProjectionCamera &ref) {
  scale_object_around_origin(ref);
}

void ScaleObjectVisitor::visit(Scene &ref) {
  for (auto &[_, objptr] : ref)
    scale_object_around_origin(*objptr);
}
