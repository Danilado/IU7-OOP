#include "BasePTSCAdapter.hpp"

Point3D BasePTSCAdapter::transformPoint(const Point3D &pt) const {
  TransformationMatrix tmptransform = -(*(cam.lock()->getTransformation()));
  return tmptransform.apply(pt);
}
