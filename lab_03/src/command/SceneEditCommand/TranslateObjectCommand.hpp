#ifndef TRANSLATE_OBJECT_COMMAND_HPP
#define TRANSLATE_OBJECT_COMMAND_HPP

#include "Point3D.hpp"
#include "SceneEditCommand.hpp"
#include "TranslateObjectVisitor.hpp"

class TranslateObjectCommand : public SceneEditCommand {
private:
  std::shared_ptr<TranslateObjectVisitor> vis;
  size_t target;

  void transform_target();
  void transform_all();

public:
  TranslateObjectCommand(double dx, double dy, double dz, size_t target_id = 0)
      : vis(std::make_shared<TranslateObjectVisitor>(dx, dy, dz)),
        target(target_id) {}

  TranslateObjectCommand(Point3D &offset, size_t target_id = 0)
      : vis(std::make_shared<TranslateObjectVisitor>(offset)),
        target(target_id) {}

  void exec() override;
};

#endif
