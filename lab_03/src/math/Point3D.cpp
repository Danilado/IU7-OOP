#include "Point3D.hpp"

Point3D::Point3D(const Point2D &pt) : Point2D(pt), z(0.) {}
Point3D::Point3D(Point2D &&pt) : Point2D(pt), z(0.) {}

double Point3D::get_z() const noexcept { return z; }
void Point3D::set_z(double n) noexcept { z = n; }

Point3D Point3D::operator-() const { return Point3D(-x, -y, -z); }
