#include "QtDrawerFactory.hpp"
#include "QtDrawer.hpp"

QtDrawerFactory::QtDrawerFactory(std::shared_ptr<QGraphicsScene> scene)
    : scene(scene) {}

std::unique_ptr<BaseDrawer> QtDrawerFactory::create() {
  return std::make_unique<QtDrawer>(scene);
}
