#ifndef ADJACENCY_LIST_DATA_HPP
#define ADJACENCY_LIST_DATA_HPP

#include "BaseModelData.hpp"
#include <map>

class AdjacencyListData : public BaseModelData {
private:
  class AdjacencyList {
  private:
    std::map<size_t, std::vector<size_t>> adjlist;

  public:
    AdjacencyList() = default;
    ~AdjacencyList() = default;

    std::vector<size_t> getAdjacencies(size_t from) const noexcept;
    void addAdjacency(size_t from, size_t to);
  };

  std::unique_ptr<AdjacencyList> adjlist;

public:
  AdjacencyListData();
  ~AdjacencyListData() override = default;

  std::shared_ptr<std::vector<std::shared_ptr<IdEdge>>>
  getIdEdges() const override;

  void addEdge(size_t id1, size_t id2) override;
  std::unique_ptr<BaseModelData> clone() const override;
};

#endif
