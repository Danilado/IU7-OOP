#include "PTSCSolutionVisitor.hpp"

void PTSCSolutionVisitor::visit(WireframeModel &ref) {}

void PTSCSolutionVisitor::visit(OrthogonalCamera &ref) {
  dst.reset(new OrthoPTSCAdapter());
}

void PTSCSolutionVisitor::visit(ProjectionCamera &ref) {
  dst.reset(new ProjPTSCAdapter());
}

void PTSCSolutionVisitor::visit(Scene &ref) {}
