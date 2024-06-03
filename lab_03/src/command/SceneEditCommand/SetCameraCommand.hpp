#ifndef SET_CAMERA_COMMAND_HPP
#define SET_CAMERA_COMMAND_HPP

#include "SceneEditCommand.hpp"

class SetCameraCommand : public SceneEditCommand {
  void exec() override;
};

#endif
