#include "AdjacencyListData.hpp"

std::shared_ptr<std::vector<std::shared_ptr<AdjacencyListData::IdEdge>>>
AdjacencyListData::getIdEdges() const {
  std::shared_ptr<std::vector<std::shared_ptr<AdjacencyListData::IdEdge>>> res =
      std::make_shared<
          std::vector<std::shared_ptr<AdjacencyListData::IdEdge>>>();

  for (size_t i = 0; i < nodes.size(); ++i)
    for (auto &id : adjlist->getAdjacencies(i))
      res->push_back(std::make_shared<AdjacencyListData::IdEdge>(i, id));

  return res;
}

void AdjacencyListData::addEdge(size_t id1, size_t id2) {
  adjlist->addAdjacency(id1, id2);
}

AdjacencyListData::AdjacencyListData() {
  adjlist = std::make_unique<AdjacencyListData::AdjacencyList>();
}

std::vector<size_t>
AdjacencyListData::AdjacencyList::getAdjacencies(size_t from) const noexcept {
  return adjlist.at(from);
}

void AdjacencyListData::AdjacencyList::addAdjacency(size_t from, size_t to) {
  adjlist[from].push_back(to);
}

std::unique_ptr<BaseModelData> AdjacencyListData::clone() const {
  std::unique_ptr<AdjacencyListData> res =
      std::make_unique<AdjacencyListData>();

  for (auto &node : nodes)
    res->nodes.push_back(std::make_shared<Point3D>(*node));

  for (size_t i = 0; i < nodes.size(); ++i)
    for (auto &adj : adjlist->getAdjacencies(i))
      res->adjlist->addAdjacency(i, adj);

  return std::move(res);
}
