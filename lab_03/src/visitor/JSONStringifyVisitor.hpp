#ifndef JSON_STRINGIFY_VISITOR_HPP
#define JSON_STRINGIFY_VISITOR_HPP

#include "BaseVisitor.hpp"
#include <string>

class BaseJsonAdapter;
class BaseDestination;

class JsonStringifyVisitor : public BaseVisitor {
private:
  BaseDestination &dst;
  BaseJsonAdapter &json_adapt;
  size_t visit_count;

public:
  JsonStringifyVisitor() = delete;
  JsonStringifyVisitor(BaseDestination &dst, BaseJsonAdapter &json_adapt)
      : dst(dst), json_adapt(json_adapt), visit_count(0) {}

  void visit(WireframeModel &ref) override;
  void visit(OrthogonalCamera &ref) override;
  void visit(ProjectionCamera &ref) override;
  void visit(Scene &ref) override;
};

#endif
