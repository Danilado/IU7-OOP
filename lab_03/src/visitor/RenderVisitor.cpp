#include "RenderVisitor.hpp"
#include "Scene.hpp"
#include "WireframeModel.hpp"

void RenderVisitor::visit(WireframeModel &ref) {
  std::shared_ptr<TransformationMatrix> transf = ref.getTransformation();
  BaseModelData &modelData = *ref.data;

  for (const auto &edge : modelData.getEdges()) {
    std::shared_ptr<Point2D> pt1 =
        PTSCAdapter->convert(transf->apply(*(edge->first)));
    std::shared_ptr<Point2D> pt2 =
        PTSCAdapter->convert(transf->apply(*(edge->second)));

    ctx->drawLine(*pt1, *pt2);
  }
}

void RenderVisitor::visit(OrthogonalCamera &ref) {}

void RenderVisitor::visit(ProjectionCamera &ref) {}

void RenderVisitor::visit(Scene &ref) {
  for (auto &[_, i] : ref)
    if (i->isVisible())
      i->accept(*this);
}
