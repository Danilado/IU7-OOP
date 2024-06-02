#include "JSONStringifyVisitor.hpp"

void JsonStringifyVisitor::visit(WireframeModel &ref) {
  if (visit_count)
    dst->append(",");
  dst->append(json_adapt->JsonStringifyWireframe(ref));

  ++visit_count;
}

void JsonStringifyVisitor::visit(OrthogonalCamera &ref) {
  if (visit_count)
    dst->append(",");
  dst->append(json_adapt->JsonStringifyOrthoCam(ref));

  ++visit_count;
}

void JsonStringifyVisitor::visit(ProjectionCamera &ref) {
  if (visit_count)
    dst->append(",");
  dst->append(json_adapt->JsonStringifyProjCam(ref));

  ++visit_count;
}

void JsonStringifyVisitor::visit(Scene &ref) {}
