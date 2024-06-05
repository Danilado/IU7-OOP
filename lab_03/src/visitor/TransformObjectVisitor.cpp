#include "TransformObjectVisitor.hpp"
#include "Object.hpp"
#include "OrthogonalCamera.hpp"
#include "ProjectionCamera.hpp"
#include "Scene.hpp"
#include "TransformationMatrix.hpp"
#include "WireframeModel.hpp"

void TransformObjectVisitor::transform(Object &ref) {
  std::shared_ptr<TransformationMatrix> objtransf = ref.getTransformation();
  *objtransf *= *(this->transf);
}

TransformObjectVisitor::TransformObjectVisitor(const Point3D &diagonal) {
  this->transf = std::make_shared<TransformationMatrix>();
  this->transf->scale(diagonal);
}

void TransformObjectVisitor::visit(WireframeModel &ref) { transform(ref); }

void TransformObjectVisitor::visit(OrthogonalCamera &ref) { transform(ref); }

void TransformObjectVisitor::visit(ProjectionCamera &ref) { transform(ref); }

void TransformObjectVisitor::visit(Scene &ref) {
  for (auto &[_, objptr] : ref)
    if (objptr->isVisible())
      transform(*objptr);
}
