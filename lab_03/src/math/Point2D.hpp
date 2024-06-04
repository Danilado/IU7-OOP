#ifndef POINT_2D_HPP
#define POINT_2D_HPP

class Point2D {
protected:
  double x;
  double y;

public:
  Point2D() = default;
  Point2D(double x, double y) noexcept : x(x), y(y) {}
  ~Point2D() = default;

  double get_x() const noexcept;
  void set_x(double n) noexcept;

  double get_y() const noexcept;
  void set_y(double n) noexcept;

  Point2D operator-() const;
};

#endif
