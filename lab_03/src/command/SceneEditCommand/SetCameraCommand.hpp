#ifndef SET_CAMERA_COMMAND_HPP
#define SET_CAMERA_COMMAND_HPP

#include "SceneEditCommand.hpp"
#include <cstdlib>

class SetCameraCommand : public SceneEditCommand {
private:
  size_t cam_id;

public:
  SetCameraCommand(size_t id) : cam_id(id) {}
  void exec() override;
};

#endif
