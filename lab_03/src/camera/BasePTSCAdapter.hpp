#ifndef BASE_PTSC_ADAPTER_HPP
#define BASE_PTSC_ADAPTER_HPP

#include "BaseCamera.hpp"
#include "Point2D.hpp"
#include "Point3D.hpp"
#include <memory>

class BasePTSCAdapter {
  friend BaseCamera;

protected:
  std::weak_ptr<BaseCamera> cam;

  Point3D transformPoint(const Point3D &pt) const;

public:
  void setCamera(std::weak_ptr<BaseCamera> camera) { cam = camera; }
  virtual std::shared_ptr<Point2D> convert(const Point3D &pt) = 0;
};

#endif
