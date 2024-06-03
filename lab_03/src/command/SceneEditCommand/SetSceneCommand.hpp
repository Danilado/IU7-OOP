#ifndef SET_SCENE_COMMAND_HPP
#define SET_SCENE_COMMAND_HPP

#include "SceneEditCommand.hpp"

class SetSceneCommand : public SceneEditCommand {
  void exec() override;
};

#endif
