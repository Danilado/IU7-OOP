#include "OrthogonalCamera.hpp"

OrthogonalCamera::OrthogonalCamera() : BaseCamera() {}

void OrthogonalCamera::accept(BaseVisitor &vis) { vis.visit(*this); }

std::unique_ptr<Object> OrthogonalCamera::clone() const {
  std::unique_ptr<OrthogonalCamera> res = std::make_unique<OrthogonalCamera>();
  res->restoreMemento(this->createMemento());
  return std::move(res);
}
