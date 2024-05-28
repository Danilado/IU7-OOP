#ifndef POINT_2D_HPP
#define POINT_2D_HPP

class Point2D {
private:
  double x;
  double y;

public:
  Point2D() = default;
  Point2D(double x, double y) noexcept : x(x), y(y) {}
  ~Point2D() = default;

  double get_x() const noexcept;
  void set_x(double n) const noexcept;

  double get_y() const noexcept;
  void set_y(double n) const noexcept;
};

#endif
