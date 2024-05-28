#ifndef PROJECTION_PTSC_ADAPTER_HPP
#define PROJECTION_PTSC_ADAPTER_HPP

#include "BasePTSCAdapter.hpp"

class ProjPTSCAdapter : public BasePTSCAdapter {
public:
  std::shared_ptr<Point2D> convert(const Point3D &pt) override;
};

#endif
