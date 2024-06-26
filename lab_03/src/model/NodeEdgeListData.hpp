#ifndef NODE_EDGE_LIST_DATA_HPP
#define NODE_EDGE_LIST_DATA_HPP

#include "BaseModelData.hpp"

class NlohmannJsonAdapter;

class NodeEdgeListData : public BaseModelData {
  friend NlohmannJsonAdapter;

private:
  std::shared_ptr<std::vector<std::shared_ptr<IdEdge>>> idedges;

public:
  NodeEdgeListData();
  ~NodeEdgeListData() override = default;

  std::shared_ptr<std::vector<std::shared_ptr<IdEdge>>>
  getIdEdges() const override;
  void addEdge(size_t id1, size_t id2) override;
  std::unique_ptr<BaseModelData> clone() const override;
};

#endif
