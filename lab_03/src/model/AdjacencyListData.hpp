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

    std::vector<size_t>::const_iterator
    getAdjacencies(size_t from) const noexcept;
    bool addAdjacency(size_t from, size_t to);
  };
  std::unique_ptr<AdjacencyList> adjlist;

public:
  std::string JSONstringify(void) const;

  std::vector<Edge>::const_iterator getEdges(void) const;

  bool addEdge(const Edge &edge);
  bool addEdge(Edge &&edge);
  bool addEdge(size_t id1, size_t id2);
};

#endif
