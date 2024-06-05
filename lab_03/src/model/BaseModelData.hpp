#ifndef BASE_MODEL_DATA_HPP
#define BASE_MODEL_DATA_HPP

#include "Point3D.hpp"
#include <memory>
#include <string>
#include <vector>

class BaseModelData {
public:
  using Node = std::shared_ptr<Point3D>;
  using Edge = std::shared_ptr<std::pair<Node, Node>>;
  class IdEdge {
  private:
    size_t id1;
    size_t id2;

  public:
    IdEdge() = default;
    IdEdge(size_t id1, size_t id2) : id1(id1), id2(id2) {}
    virtual ~IdEdge() = default;

    size_t getFirstId(void) const noexcept;
    size_t getSecondId(void) const noexcept;
    void setFirstId(size_t n) noexcept;
    void setSecondId(size_t n) noexcept;
  };

  using IdEdgeVector = std::shared_ptr<std::vector<std::shared_ptr<IdEdge>>>;

protected:
  std::vector<Node> nodes;

public:
  virtual ~BaseModelData() = default;

  const std::vector<Node> &getNodes() const noexcept;
  virtual std::shared_ptr<std::vector<Edge>> getEdges() const;
  virtual IdEdgeVector getIdEdges() const = 0;

  void addNode(const Point3D &pt);
  void addNode(Point3D &&pt);

  virtual void addEdge(size_t id1, size_t id2) = 0;
  virtual std::unique_ptr<BaseModelData> clone() const = 0;
};

#endif
