#ifndef ROTATE_OBJECT_COMMAND_HPP
#define ROTATE_OBJECT_COMMAND_HPP

#include "Point3D.hpp"
#include "RotateObjectVisitor.hpp"
#include "SceneEditCommand.hpp"

class RotateObjectCommand : public SceneEditCommand {
private:
  std::shared_ptr<RotateObjectVisitor> vis;
  size_t target;

  void transform_target();
  void transform_all();

public:
  RotateObjectCommand(double ox, double oy, double oz, double ax, double ay,
                      double az, size_t target_id = 0, bool deg = false)
      : vis(std::make_shared<RotateObjectVisitor>(ox, oy, oz, ax, ay, az, deg)),
        target(target_id) {}

  RotateObjectCommand(double ax, double ay, double az, size_t target_id = 0,
                      bool deg = false)
      : vis(std::make_shared<RotateObjectVisitor>(ax, ay, az, deg)),
        target(target_id) {}

  RotateObjectCommand(Point3D &angles, size_t target_id = 0, bool deg = false)
      : vis(std::make_shared<RotateObjectVisitor>(angles, deg)),
        target(target_id) {}

  RotateObjectCommand(Point3D &origin, Point3D &angles, size_t target_id = 0,
                      bool deg = false)
      : vis(std::make_shared<RotateObjectVisitor>(origin, angles, deg)),
        target(target_id) {}

  void exec() override;
};

#endif
