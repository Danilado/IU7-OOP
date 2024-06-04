#include "RenderVisitor.hpp"
#include "CameraManager.hpp"
#include "Scene.hpp"
#include "SingletonTemplate.hpp"
#include "WireframeModel.hpp"

void RenderVisitor::visit(WireframeModel &ref) {
  std::shared_ptr<TransformationMatrix> transf = ref.getTransformation();
  BaseModelData &modelData = *ref.data;

  CameraManager &cm = Singleton<CameraManager>::instance();

  PTSCAdapter->setCamera(cm.getCamera());

  std::shared_ptr<std::vector<BaseModelData::Edge>> edges =
      modelData.getEdges();

  for (size_t i = 0; i < edges->size(); ++i) {
    std::shared_ptr<Point2D> pt1 =
        PTSCAdapter->convert(transf->apply(*((*edges)[i]->first)));
    std::shared_ptr<Point2D> pt2 =
        PTSCAdapter->convert(transf->apply(*((*edges)[i]->second)));

    ctx->drawLine(*pt1, *pt2);
  }
}

void RenderVisitor::visit(OrthogonalCamera &ref) {}

void RenderVisitor::visit(ProjectionCamera &ref) {}

void RenderVisitor::visit(Scene &ref) {
  for (auto &[_, i] : ref) {
    if (i->isVisible())
      i->accept(*this);
  }
}
