#include "PTSCSolutionVisitor.hpp"

void PTSCSolutionVisitor::visit(WireframeModel &ref) {}

void PTSCSolutionVisitor::visit(OrthogonalCamera &ref) {
  dst = std::make_shared<OrthoPTSCAdapter>();
}

void PTSCSolutionVisitor::visit(ProjectionCamera &ref) {
  dst = std::make_shared<ProjPTSCAdapter>();
}

void PTSCSolutionVisitor::visit(Scene &ref) {}
