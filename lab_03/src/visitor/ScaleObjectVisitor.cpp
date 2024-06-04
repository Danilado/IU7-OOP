#include "ScaleObjectVisitor.hpp"
#include "Object.hpp"
#include "OrthogonalCamera.hpp"
#include "ProjectionCamera.hpp"
#include "Scene.hpp"
#include "TransformationMatrix.hpp"
#include "WireframeModel.hpp"

void ScaleObjectVisitor::scale_object_around_origin(Object &ref) {
  std::shared_ptr<TransformationMatrix> transf = ref.getTransformation();
  transf->translate(-origin);
  transf->scale(scale);
  transf->translate(origin);
}

ScaleObjectVisitor::ScaleObjectVisitor(double kx, double ky, double kz)
    : scale(kz, ky, kz) {}

ScaleObjectVisitor::ScaleObjectVisitor(double ox, double oy, double oz,
                                       double kx, double ky, double kz)
    : scale(kx, ky, kz), origin(ox, oy, oz) {}

ScaleObjectVisitor::ScaleObjectVisitor(const Point3D &scale) : scale(scale) {}

ScaleObjectVisitor::ScaleObjectVisitor(const Point3D &offset,
                                       const Point3D &scale)
    : origin(offset), scale(scale) {}

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
