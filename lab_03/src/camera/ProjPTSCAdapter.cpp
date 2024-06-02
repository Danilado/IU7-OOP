#include "ProjPTSCAdapter.hpp"

std::shared_ptr<Point2D> ProjPTSCAdapter::convert(const Point3D &pt) {
  Point3D tmppt = transformPoint(pt);
  return std::make_shared<Point2D>(tmppt.get_x(), tmppt.get_y());
}
