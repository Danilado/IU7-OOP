#ifndef TRANSLATE_OBJECT_COMMAND_HPP
#define TRANSLATE_OBJECT_COMMAND_HPP

#include "Point3D.hpp"
#include "SceneEditCommand.hpp"
#include "TranslateObjectVisitor.hpp"

class TranslateObjectCommand : public SceneEditCommand {
private:
  Point3D offset;
  size_t target;

public:
  TranslateObjectCommand(double dx, double dy, double dz, size_t target_id = 0)
      : offset(dx, dy, dz), target(target_id) {}

  TranslateObjectCommand(Point3D &offset, size_t target_id = 0)
      : offset(offset), target(target_id) {}

  void exec() override;
};

#endif
