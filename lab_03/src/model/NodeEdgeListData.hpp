#ifndef NODE_EDGE_LIST_DATA_HPP
#define NODE_EDGE_LIST_DATA_HPP

#include "BaseModelData.hpp"

class NodeEdgeListData : public BaseModelData {
private:
  std::shared_ptr<std::vector<std::shared_ptr<IdEdge>>> idedges;

public:
  NodeEdgeListData();
  ~NodeEdgeListData() = default;

  std::shared_ptr<std::vector<std::shared_ptr<IdEdge>>>
  getIdEdges() const override;
  void addEdge(size_t id1, size_t id2) override;
};

#endif
