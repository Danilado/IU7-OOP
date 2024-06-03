#include "NodeEdgeListData.hpp"

NodeEdgeListData::NodeEdgeListData() {}

std::shared_ptr<std::vector<std::shared_ptr<NodeEdgeListData::IdEdge>>>
NodeEdgeListData::getIdEdges() const {
  return idedges;
}

void NodeEdgeListData::addEdge(size_t id1, size_t id2) {
  idedges->push_back(std::make_shared<IdEdge>(id1, id2));
}
