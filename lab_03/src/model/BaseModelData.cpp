#include "BaseModelData.hpp"

const std::vector<BaseModelData::Node> &
BaseModelData::getNodes(void) const noexcept {
  return nodes;
}

void BaseModelData::addNode(const Point3D &pt) {
  nodes.push_back(std::make_shared<Point3D>(pt));
}

void BaseModelData::addNode(Point3D &&pt) {
  nodes.push_back(std::make_shared<Point3D>(pt));
}

std::shared_ptr<std::vector<BaseModelData::Edge>>
BaseModelData::getEdges() const {
  std::shared_ptr<std::vector<BaseModelData::Edge>> res =
      std::make_shared<std::vector<BaseModelData::Edge>>();

  for (auto &idedge : *getIdEdges())
    res->push_back(
        std::make_shared<std::pair<BaseModelData::Node, BaseModelData::Node>>(
            nodes[idedge->getFirstId()], nodes[idedge->getSecondId()]));

  return res;
}

size_t BaseModelData::IdEdge::getFirstId(void) const noexcept { return id1; }

size_t BaseModelData::IdEdge::getSecondId(void) const noexcept { return id2; }

void BaseModelData::IdEdge::setFirstId(size_t n) noexcept { id1 = n; }

void BaseModelData::IdEdge::setSecondId(size_t n) noexcept { id2 = n; }
