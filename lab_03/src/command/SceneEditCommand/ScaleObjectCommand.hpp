#ifndef SCALE_OBJECT_COMMAND_HPP
#define SCALE_OBJECT_COMMAND_HPP

#include "Point3D.hpp"
#include "ScaleObjectVisitor.hpp"
#include "SceneEditCommand.hpp"

class ScaleObjectCommand : public SceneEditCommand {
private:
  Point3D origin;
  Point3D scale;
  size_t target;

public:
  ScaleObjectCommand(double ox, double oy, double oz, double kx, double ky,
                     double kz, size_t target_id = 0)
      : origin(ox, oy, oz), scale(kx, ky, kz), target(target_id) {}

  ScaleObjectCommand(double kx, double ky, double kz, size_t target_id = 0)
      : ScaleObjectCommand(0., 0., 0., kx, ky, kz, target) {}

  ScaleObjectCommand(Point3D &origin, Point3D &scales, size_t target_id = 0)
      : origin(origin), scale(scales), target(target_id) {}

  ScaleObjectCommand(Point3D &scales, size_t target_id = 0)
      : scale(scales), target(target_id) {}

  void exec() override;
};

#endif
