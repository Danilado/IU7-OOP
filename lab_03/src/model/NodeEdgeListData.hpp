#ifndef NODE_EDGE_LIST_DATA_HPP
#define NODE_EDGE_LIST_DATA_HPP

#include "BaseModelData.hpp"

class NodeEdgeListData : public BaseModelData {
private:
  class IdEdge {
  private:
    size_t id1;
    size_t id2;

  public:
    IdEdge() = default;
    IdEdge(size_t id1, size_t id2) : id1(id1), id2(id2) {}
    ~IdEdge() = default;

    size_t getFirstId(void) const noexcept;
    size_t getSecondId(void) const noexcept;
    void setFirstId(size_t n) noexcept;
    void setSecondId(size_t n) noexcept;
  };
  std::vector<std::shared_ptr<IdEdge>> idedges;

public:
  std::string JSONstringify(void) const;

  std::vector<Edge>::const_iterator getEdges(void) const;

  bool addEdge(const Edge &edge);
  bool addEdge(Edge &&edge);
  bool addEdge(size_t id1, size_t id2);
};

#endif
