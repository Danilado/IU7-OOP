#ifndef POINT_3D_HPP
#define POINT_3D_HPP

#include "Point2D.hpp"

class Point3D : public Point2D {
private:
  double z;

public:
  Point3D() = default;
  Point3D(double x, double y, double z) noexcept : Point2D(x, y), z(z) {}
  Point3D(const Point2D &pt);
  Point3D(Point2D &&pt);
  ~Point3D() = default;

  double get_z() const noexcept;
  void set_z(double n) const noexcept;
};

#endif
