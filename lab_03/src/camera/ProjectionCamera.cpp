#include "ProjectionCamera.hpp"

void ProjectionCamera::accept(BaseVisitor &vis) { vis.visit(*this); }

std::unique_ptr<Object> ProjectionCamera::clone() const {
  std::unique_ptr<ProjectionCamera> res = std::make_unique<ProjectionCamera>();
  res->restoreMemento(this->createMemento());
  return std::move(res);
}
