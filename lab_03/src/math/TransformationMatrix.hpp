#ifndef TRANSFORMATION_MATRIX_HPP
#define TRANSFORMATION_MATRIX_HPP

#include "Point2D.hpp"
#include "Point3D.hpp"
#include <cmath>
#include <memory>

class NlohmannJsonAdapter;

class TransformationMatrix {
  friend NlohmannJsonAdapter;

private:
  static const size_t dim = 3;
  using mat_t = std::shared_ptr<double[dim + 1][dim + 1]>;
  mat_t transform;

  double get_2d_x(const Point2D &pt) const noexcept;
  double get_2d_y(const Point2D &pt) const noexcept;
  double get_2d_x(double x, double y) const noexcept;
  double get_2d_y(double x, double y) const noexcept;

  double get_3d_x(const Point3D &pt) const noexcept;
  double get_3d_y(const Point3D &pt) const noexcept;
  double get_3d_z(const Point3D &pt) const noexcept;
  double get_3d_x(double x, double y, double z) const noexcept;
  double get_3d_y(double x, double y, double z) const noexcept;
  double get_3d_z(double x, double y, double z) const noexcept;

  double get_mul_cell(const TransformationMatrix &other, size_t i,
                      size_t j) const noexcept;

  TransformationMatrix get_rotated_around_x(double angle);
  TransformationMatrix get_rotated_around_y(double angle);
  TransformationMatrix get_rotated_around_z(double angle);

public:
  TransformationMatrix();
  TransformationMatrix(const TransformationMatrix &other);
  TransformationMatrix(TransformationMatrix &&tmp);
  ~TransformationMatrix() = default;

  Point2D apply(const Point2D &pt) const noexcept;
  void apply_in_place(Point2D &pt) const noexcept;

  Point3D apply(const Point3D &pt) const noexcept;
  void apply_in_place(Point3D &pt) const noexcept;

  void translate(const double dx, const double dy, const double dz) noexcept;
  void translate(const Point3D &pt) noexcept;

  void scale(const double kx, const double ky, const double kz) noexcept;
  void scale(const Point3D &pt) noexcept;

  void rotate(const double ax, const double ay, const double az);
  void rotate(const Point3D &pt);

  void rotate_deg(const double ax, const double ay, const double az);
  void rotate_deg(const Point3D &pt);

  void reset(void);

  TransformationMatrix operator*(const TransformationMatrix &other) const;
  TransformationMatrix &operator*=(const TransformationMatrix &other);

  TransformationMatrix operator+(const TransformationMatrix &other) const;
  TransformationMatrix &operator+=(const TransformationMatrix &other);

  TransformationMatrix operator-(const TransformationMatrix &other) const;
  TransformationMatrix &operator-=(const TransformationMatrix &other);

  TransformationMatrix operator-() const;
};

class TranslationMatrix : public TransformationMatrix {
public:
  TranslationMatrix(const double dx, const double dy, const double dz);
};

class ScalingMatrix : public TransformationMatrix {
public:
  ScalingMatrix(const double kx, const double ky, const double kz);
};

class RotationMatrix : public TransformationMatrix {
public:
  RotationMatrix(const double ax, const double ay, const double az,
                 bool deg = false);
};

#endif
