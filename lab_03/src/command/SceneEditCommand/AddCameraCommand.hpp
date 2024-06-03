#ifndef ADD_CAMERA_COMMAND_HPP
#define ADD_CAMERA_COMMAND_HPP

#include "SceneEditCommand.hpp"

class AddCameraCommand : public SceneEditCommand {
  void exec() override;
};

#endif
