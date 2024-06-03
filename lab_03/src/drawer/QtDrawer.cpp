#include "QtDrawer.hpp"

void QtDrawer::drawLine(double x1, double y1, double x2, double y2) {
  scene->addLine(x1, y1, x2, y2);
}

void QtDrawer::drawLine(Point2D &pt1, Point2D &pt2) {
  drawLine(pt1.get_x(), pt1.get_y(), pt2.get_x(), pt2.get_y());
}

void QtDrawer::clear() { scene->clear(); }
