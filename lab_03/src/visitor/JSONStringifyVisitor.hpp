#ifndef JSON_STRINGIFY_VISITOR_HPP
#define JSON_STRINGIFY_VISITOR_HPP

#include "BaseVisitor.hpp"
#include <string>

class JSONStringifyVisitor : public BaseVisitor {
private:
  std::shared_ptr<std::string> dst;

public:
  JSONStringifyVisitor() = delete;
  JSONStringifyVisitor(std::shared_ptr<std::string> dst) : dst(dst) {}

  void visit(Object &ref) override;
  void visit(WireframeModel &ref) override;
  void visit(OrthogonalCamera &ref) override;
  void visit(ProjectionCamera &ref) override;
};

#endif
