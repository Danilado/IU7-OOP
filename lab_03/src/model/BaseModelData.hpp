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

private:
  std::vector<Node> nodes;

public:
  std::vector<Node>::const_iterator getNodes(void) const noexcept;
  virtual std::vector<Edge>::const_iterator getEdges(void) const = 0;

  bool addNode(const Point3D &pt);
  bool addNode(Point3D &&pt);

  virtual bool addEdge(const Edge &edge);
  virtual bool addEdge(Edge &&edge);
  virtual bool addEdge(size_t id1, size_t id2);

  virtual std::string JSONstringify(void) = 0;
};

#endif
