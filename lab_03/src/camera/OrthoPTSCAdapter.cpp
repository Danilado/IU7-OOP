#include "OrthoPTSCAdapter.hpp"

double OrthoPTSCAdapter::shadyExpFunc(double x) {
  if (x >= 1)
    return x;

  return exp((x - 1) / 2.71828);
}

std::shared_ptr<Point2D> OrthoPTSCAdapter::convert(const Point3D &pt) {
  Point3D tmppt = transformPoint(pt);
  double fovl = 1600;
  double persp_coeff = (fovl / shadyExpFunc(fovl + pt.get_z()));
  double resx = persp_coeff * pt.get_x();
  double resy = persp_coeff * pt.get_y();

  return std::make_shared<Point2D>(resx, resy);
}
