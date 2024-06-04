#include "WireframeModel.hpp"

void WireframeModel::accept(BaseVisitor &vis) { return vis.visit(*this); }

std::unique_ptr<Object> WireframeModel::clone() const {
  std::unique_ptr<WireframeModel> res = std::make_unique<WireframeModel>();
  res->restoreMemento(this->createMemento());
  res->data = std::move(data->clone());
  return std::move(res);
}
