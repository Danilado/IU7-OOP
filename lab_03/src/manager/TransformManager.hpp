#ifndef TRANSFORM_MANAGER_HPP
#define TRANSFORM_MANAGER_HPP

#include "Point3D.hpp"
#include <cstdlib>

class BaseVisitor;

class TransformManager {
private:
  void apply(BaseVisitor &vis, size_t target);

public:
  TransformManager() = default;
  ~TransformManager() = default;

  void TranslateObject(Point3D &offset, size_t target);
  void ScaleObject(Point3D &origin, Point3D &scale, size_t target);
  void RotateObject(Point3D &origin, Point3D &angles, size_t target, bool deg);

  TransformManager(const TransformManager &) = delete;
  TransformManager &operator=(const TransformManager &) = delete;
};

#endif
