#ifndef TRANSFORMATION_MATRIX_HPP
#define TRANSFORMATION_MATRIX_HPP

#include "Point2D.hpp"
#include "Point3D.hpp"
#include <memory>

class TransformationMatrix {
private:
  static const size_t dim = 3;
  using mat_t = std::shared_ptr<double[dim + 1][dim + 1]>;
  mat_t transform;

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

  void rotate(const double ax, const double ay, const double az) noexcept;
  void rotate(const Point3D &pt) noexcept;

  void rotate_deg(const double ax, const double ay, const double az) noexcept;
  void rotate_deg(const Point3D &pt) noexcept;

  void reset(void) noexcept;

  TransformationMatrix operator*(const TransformationMatrix &other) const;
  TransformationMatrix &operator*=(const TransformationMatrix &other);

  TransformationMatrix operator+(const TransformationMatrix &other) const;
  TransformationMatrix &operator+=(const TransformationMatrix &other);

  TransformationMatrix operator-() const;

  TransformationMatrix operator-(const TransformationMatrix &other) const;
  TransformationMatrix &operator-=(const TransformationMatrix &other);
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
