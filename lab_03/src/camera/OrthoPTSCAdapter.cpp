#include "OrthoPTSCAdapter.hpp"

std::shared_ptr<Point2D> OrthoPTSCAdapter::convert(const Point3D &pt) {
  Point3D tmppt = transformPoint(pt);
  double fovl = 200;
  double persp_coeff = (fovl / (fovl + pt.get_z()));
  double resx = persp_coeff * pt.get_x();
  double resy = persp_coeff * pt.get_y();

  return std::make_shared<Point2D>(resx, resy);
}
