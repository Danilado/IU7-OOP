#ifndef SCALE_OBJECT_COMMAND_HPP
#define SCALE_OBJECT_COMMAND_HPP

#include "Point3D.hpp"
#include "ScaleObjectVisitor.hpp"
#include "SceneEditCommand.hpp"

class ScaleObjectCommand : public SceneEditCommand {
private:
  std::shared_ptr<ScaleObjectVisitor> vis;
  size_t target;

  void transform_target();
  void transform_all();

public:
  ScaleObjectCommand(double ox, double oy, double oz, double kx, double ky,
                     double kz, size_t target_id = 0)
      : vis(std::make_shared<ScaleObjectVisitor>(ox, oy, oz, kx, ky, kz)),
        target(target_id) {}

  ScaleObjectCommand(double kx, double ky, double kz, size_t target_id = 0)
      : vis(std::make_shared<ScaleObjectVisitor>(kx, ky, kz)),
        target(target_id) {}

  ScaleObjectCommand(Point3D &scales, size_t target_id = 0)
      : vis(std::make_shared<ScaleObjectVisitor>(scales)), target(target_id) {}

  ScaleObjectCommand(Point3D &origin, Point3D &scales, size_t target_id = 0)
      : vis(std::make_shared<ScaleObjectVisitor>(origin, scales)),
        target(target_id) {}

  void exec() override;
};

#endif
