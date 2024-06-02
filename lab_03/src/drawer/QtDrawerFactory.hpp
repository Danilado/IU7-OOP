#ifndef QT_DRAWER_FACTORY_HPP
#define QT_DRAWER_FACTORY_HPP

#include "BaseDrawerFactory.hpp"
#include <QGraphicsScene>

class QtDrawerFactory : public BaseDrawerFactory {
private:
  std::weak_ptr<QGraphicsScene> scene{};

public:
  explicit QtDrawerFactory(std::shared_ptr<QGraphicsScene> scene);
  std::unique_ptr<BaseDrawer> create() override;
};

#endif
