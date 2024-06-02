#ifndef RENDER_VISITOR_HPP
#define RENDER_VISITOR_HPP

#include "BaseDrawer.hpp"
#include "BasePTSCAdapter.hpp"
#include "BaseVisitor.hpp"

class RenderVisitor : public BaseVisitor {
private:
  std::shared_ptr<BasePTSCAdapter> PTSCAdapter;
  std::shared_ptr<BaseDrawer> ctx;

public:
  RenderVisitor(std::shared_ptr<BasePTSCAdapter> PTSCAdapter,
                std::shared_ptr<BaseDrawer> ctx)
      : PTSCAdapter(PTSCAdapter), ctx(ctx) {}
  ~RenderVisitor() = default;

  void visit(WireframeModel &ref) override;
  void visit(OrthogonalCamera &ref) override;
  void visit(ProjectionCamera &ref) override;
  void visit(Scene &ref) override;
};

#endif
