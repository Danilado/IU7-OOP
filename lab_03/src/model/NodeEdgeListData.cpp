#include "NodeEdgeListData.hpp"

NodeEdgeListData::NodeEdgeListData() {
  idedges = std::make_shared<std::vector<std::shared_ptr<IdEdge>>>();
}

std::shared_ptr<std::vector<std::shared_ptr<NodeEdgeListData::IdEdge>>>
NodeEdgeListData::getIdEdges() const {
  return idedges;
}

void NodeEdgeListData::addEdge(size_t id1, size_t id2) {
  idedges->push_back(std::make_shared<IdEdge>(id1, id2));
}

std::unique_ptr<BaseModelData> NodeEdgeListData::clone() const {
  std::unique_ptr<NodeEdgeListData> res = std::make_unique<NodeEdgeListData>();

  for (auto &node : nodes)
    res->nodes.push_back(std::make_shared<Point3D>(*node));

  for (auto &idedge : *idedges)
    res->idedges->push_back(std::make_shared<IdEdge>(*idedge));

  return std::move(res);
}
