#ifndef ROTATE_OBJECT_COMMAND_HPP
#define ROTATE_OBJECT_COMMAND_HPP

#include "Point3D.hpp"
#include "RotateObjectVisitor.hpp"
#include "SceneEditCommand.hpp"

class RotateObjectCommand : public SceneEditCommand {
private:
  Point3D origin;
  Point3D rotation;
  bool deg;

  size_t target;

public:
  RotateObjectCommand(double ox, double oy, double oz, double ax, double ay,
                      double az, size_t target_id = 0, bool deg = false)
      : origin(oz, oy, oz), rotation(ax, ay, az), target(target_id), deg(deg) {}

  RotateObjectCommand(double ax, double ay, double az, size_t target_id = 0,
                      bool deg = false)
      : rotation(ax, ay, az), target(target_id), deg(deg) {}

  RotateObjectCommand(Point3D &angles, size_t target_id = 0, bool deg = false)
      : rotation(angles), target(target_id), deg(deg) {}

  RotateObjectCommand(Point3D &origin, Point3D &angles, size_t target_id = 0,
                      bool deg = false)
      : origin(origin), rotation(angles), target(target_id), deg(deg) {}

  void exec() override;
};

#endif
