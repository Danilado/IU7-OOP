#ifndef BASE_DRAWER_HPP
#define BASE_DRAWER_HPP

#include "Point2D.hpp"

class BaseDrawer {
private:
public:
  virtual void drawLine(Point2D &pt1, Point2D &pt2) = 0;
  virtual void drawLine(double x1, double y1, double x2, double y2) = 0;
  virtual void clear() = 0;
};

#endif
