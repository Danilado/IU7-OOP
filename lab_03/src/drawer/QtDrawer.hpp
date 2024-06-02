#ifndef QT_DRAWER_HPP
#define QT_DRAWER_HPP

#include "BaseDrawer.hpp"
#include <QGraphicsScene>
#include <memory>

class QtDrawer : public BaseDrawer {
private:
  std::weak_ptr<QGraphicsScene> scene;

public:
  QtDrawer() = delete;
  explicit QtDrawer(std::weak_ptr<QGraphicsScene> &scene) : scene(scene){};

  void drawLine(Point2D &pt1, Point2D &pt2) override;
  void drawLine(double x1, double y1, double x2, double y2) override;
  void clear() override;
};

#endif
