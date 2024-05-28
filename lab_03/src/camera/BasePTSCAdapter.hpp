#ifndef BASE_PTSC_ADAPTER_HPP
#define BASE_PTSC_ADAPTER_HPP

#include "BaseCamera.hpp"
#include "Point2D.hpp"
#include "Point3D.hpp"
#include <memory>

class BasePTSCAdapter {
  friend BaseCamera;

private:
  std::shared_ptr<BaseCamera> cam;

public:
  virtual std::shared_ptr<Point2D> convert(const Point3D &pt) = 0;
};

#endif
