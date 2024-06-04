#include "TranslateObjectVisitor.hpp"
#include "Object.hpp"
#include "OrthogonalCamera.hpp"
#include "ProjectionCamera.hpp"
#include "Scene.hpp"
#include "TransformationMatrix.hpp"
#include "WireframeModel.hpp"

void TranslateObjectVisitor::translate(Object &ref) {
  std::shared_ptr<TransformationMatrix> transf = ref.getTransformation();
  transf->translate(offset);
}

TranslateObjectVisitor::TranslateObjectVisitor(double dx, double dy, double dz)
    : offset(dx, dy, dz) {}

TranslateObjectVisitor::TranslateObjectVisitor(const Point3D &scale)
    : TranslateObjectVisitor(scale.get_x(), scale.get_y(), scale.get_z()) {}

void TranslateObjectVisitor::visit(WireframeModel &ref) { translate(ref); }

void TranslateObjectVisitor::visit(OrthogonalCamera &ref) { translate(ref); }

void TranslateObjectVisitor::visit(ProjectionCamera &ref) { translate(ref); }

void TranslateObjectVisitor::visit(Scene &ref) {
  for (auto &[_, objptr] : ref)
    translate(*objptr);
}
