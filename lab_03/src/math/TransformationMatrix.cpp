#include "TransformationMatrix.hpp"
#include "MyMath.hpp"

TransformationMatrix::TransformationMatrix() { reset(); }

TransformationMatrix::TransformationMatrix(const TransformationMatrix &other) {
  reset();

  for (size_t i = 0; i < dim + 1; ++i)
    for (size_t j = 0; j < dim + 1; ++j)
      transform[i][j] = other.transform[i][j];
}

TransformationMatrix::TransformationMatrix(TransformationMatrix &&tmp) {
  transform = std::move(tmp.transform);
  tmp.transform = nullptr;
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

double TransformationMatrix::get_2d_x(double x, double y) const noexcept {
  return transform[0][0] * x + transform[0][1] * y + transform[0][2];
}

double TransformationMatrix::get_2d_y(double x, double y) const noexcept {
  return transform[1][0] * x + transform[1][1] * y + transform[1][2];
}

double TransformationMatrix::get_2d_x(const Point2D &pt) const noexcept {
  return get_2d_x(pt.get_x(), pt.get_y());
}

double TransformationMatrix::get_2d_y(const Point2D &pt) const noexcept {
  return get_2d_y(pt.get_x(), pt.get_y());
}

double TransformationMatrix::get_3d_x(double x, double y,
                                      double z) const noexcept {
  return transform[0][0] * x + transform[0][1] * y + transform[0][2] * z +
         transform[0][3];
}
double TransformationMatrix::get_3d_y(double x, double y,
                                      double z) const noexcept {
  return transform[1][0] * x + transform[1][1] * y + transform[1][2] * z +
         transform[1][3];
}
double TransformationMatrix::get_3d_z(double x, double y,
                                      double z) const noexcept {
  return transform[2][0] * x + transform[2][1] * y + transform[2][2] * z +
         transform[2][3];
}

double TransformationMatrix::get_3d_x(const Point3D &pt) const noexcept {
  return get_3d_x(pt.get_x(), pt.get_y(), pt.get_z());
}

double TransformationMatrix::get_3d_y(const Point3D &pt) const noexcept {
  return get_3d_y(pt.get_x(), pt.get_y(), pt.get_z());
}

double TransformationMatrix::get_3d_z(const Point3D &pt) const noexcept {
  return get_3d_z(pt.get_x(), pt.get_y(), pt.get_z());
}

Point2D TransformationMatrix::apply(const Point2D &pt) const noexcept {
  return Point2D(get_2d_x(pt), get_2d_y(pt));
}

void TransformationMatrix::apply_in_place(Point2D &pt) const noexcept {
  double newx = get_2d_x(pt);
  double newy = get_2d_y(pt);

  pt.set_x(newx);
  pt.set_y(newy);
}

Point3D TransformationMatrix::apply(const Point3D &pt) const noexcept {
  return Point3D(get_3d_x(pt), get_3d_y(pt), get_3d_z(pt));
}

void TransformationMatrix::apply_in_place(Point3D &pt) const noexcept {
  double newx = get_3d_x(pt);
  double newy = get_3d_y(pt);
  double newz = get_3d_z(pt);

  pt.set_x(newx);
  pt.set_y(newy);
  pt.set_z(newz);
}

TransformationMatrix TransformationMatrix::get_rotated_around_x(double angle) {
  TransformationMatrix res;

  res.transform[1][1] = cos(angle);
  res.transform[1][2] = -sin(angle);
  res.transform[2][1] = sin(angle);
  res.transform[2][2] = cos(angle);

  return res;
}

TransformationMatrix TransformationMatrix::get_rotated_around_y(double angle) {
  TransformationMatrix res;

  res.transform[0][0] = cos(angle);
  res.transform[0][2] = sin(angle);
  res.transform[2][0] = -sin(angle);
  res.transform[2][2] = cos(angle);

  return res;
}

TransformationMatrix TransformationMatrix::get_rotated_around_z(double angle) {
  TransformationMatrix res;

  res.transform[0][0] = cos(angle);
  res.transform[0][1] = -sin(angle);
  res.transform[1][0] = sin(angle);
  res.transform[1][1] = cos(angle);

  return res;
}

void TransformationMatrix::rotate(const double ax, const double ay,
                                  const double az) {
  (*this) *= get_rotated_around_x(ax) * get_rotated_around_y(ay) *
             get_rotated_around_z(az);
}

void TransformationMatrix::rotate(const Point3D &pt) {
  rotate(pt.get_x(), pt.get_y(), pt.get_z());
}

void TransformationMatrix::rotate_deg(const double ax, const double ay,
                                      const double az) {
  rotate(MyMath::rad(ax), MyMath::rad(ay), MyMath::rad(az));
}

void TransformationMatrix::rotate_deg(const Point3D &pt) {
  rotate_deg(pt.get_x(), pt.get_y(), pt.get_z());
}

void TransformationMatrix::reset(void) {
  transform = std::make_shared<double[dim + 1][dim + 1]>();
  for (size_t i = 0; i <= dim; ++i)
    for (size_t j = 0; j <= dim; ++j)
      transform[i][j] = (i == j) ? 1 : 0;
}

double TransformationMatrix::get_mul_cell(const TransformationMatrix &other,
                                          size_t i, size_t j) const noexcept {
  double res = 0.;
  for (size_t k = 0; k <= dim; k++)
    res += transform[i][k] * other.transform[k][j];

  return res;
}

TransformationMatrix
TransformationMatrix::operator*(const TransformationMatrix &other) const {
  TransformationMatrix res;

  for (size_t i = 0; i < dim; ++i)
    for (size_t j = 0; j < dim; ++j)
      res.transform[i][j] = get_mul_cell(other, i, j);

  return res;
}

TransformationMatrix &
TransformationMatrix::operator*=(const TransformationMatrix &other) {
  TransformationMatrix tmpmat = (*this) * other;
  this->transform = std::move(tmpmat.transform);
  tmpmat.transform = nullptr;
  return *this;
}

TransformationMatrix
TransformationMatrix::operator+(const TransformationMatrix &other) const {
  TransformationMatrix res;

  for (size_t i = 0; i < dim; ++i)
    for (size_t j = 0; j < dim; ++j)
      res.transform[i][j] = transform[i][j] + other.transform[i][j];

  return res;
}

TransformationMatrix &
TransformationMatrix::operator+=(const TransformationMatrix &other) {
  for (size_t i = 0; i < dim; ++i)
    for (size_t j = 0; j < dim; ++j)
      transform[i][j] += other.transform[i][j];

  return *this;
}

TransformationMatrix
TransformationMatrix::operator-(const TransformationMatrix &other) const {
  TransformationMatrix res;

  for (size_t i = 0; i < dim; ++i)
    for (size_t j = 0; j < dim; ++j)
      res.transform[i][j] = transform[i][j] - other.transform[i][j];

  return res;
}

TransformationMatrix &
TransformationMatrix::operator-=(const TransformationMatrix &other) {
  for (size_t i = 0; i < dim; ++i)
    for (size_t j = 0; j < dim; ++j)
      transform[i][j] -= other.transform[i][j];

  return *this;
}

TransformationMatrix TransformationMatrix::operator-() const {
  TransformationMatrix res;

  for (size_t i = 0; i < dim; ++i)
    for (size_t j = 0; j < dim; ++j)
      res.transform[i][j] = -transform[i][j];

  return res;
}
