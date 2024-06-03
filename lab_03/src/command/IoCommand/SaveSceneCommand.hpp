#ifndef SAVE_SCENE_COMMAND_HPP
#define SAVE_SCENE_COMMAND_HPP

#include "IoCommand.hpp"

class SaveSceneCommand : public SaveCommand {
  void exec() override;
};

#endif
