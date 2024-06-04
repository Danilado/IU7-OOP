#include "Point2D.hpp"

double Point2D::get_x() const noexcept { return x; }
void Point2D::set_x(double n) noexcept { x = n; }

double Point2D::get_y() const noexcept { return y; }
void Point2D::set_y(double n) noexcept { y = n; }

Point2D Point2D::operator-() const { return Point2D(-x, -y); }
