#include "TransformationMatrix.hpp"

TransformationMatrix::TransformationMatrix() { reset(); }

TransformationMatrix::TransformationMatrix(const TransformationMatrix &other) {
  reset();

  for (size_t i = 0; i < dim + 1; ++i)
    for (size_t j = 0; j < dim + 1; ++j)
      transform[i][j] = other.transform[i][j];
}

TransformationMatrix::TransformationMatrix(TransformationMatrix &&tmp) {
  transform = std::move(tmp.transform);
}

void TransformationMatrix::translate(const double dx, const double dy,
                                     const double dz) noexcept {
  transform[0][dim] += dx;
  transform[1][dim] += dy;
  transform[2][dim] += dz;
}

void TransformationMatrix::translate(const Point3D &pt) noexcept {
  translate(pt.get_x(), pt.get_y(), pt.get_z());
}

void TransformationMatrix::scale(const double kx, const double ky,
                                 const double kz) noexcept {
  transform[0][dim] *= kx;
  transform[1][dim] *= ky;
  transform[2][dim] *= kz;
}

void TransformationMatrix::scale(const Point3D &pt) noexcept {
  scale(pt.get_x(), pt.get_y(), pt.get_z());
}
