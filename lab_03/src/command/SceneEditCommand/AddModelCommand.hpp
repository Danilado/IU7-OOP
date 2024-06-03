#ifndef ADD_MODEL_COMMAND_HPP
#define ADD_MODEL_COMMAND_HPP

#include "SceneEditCommand.hpp"

class AddModelCommand : public SceneEditCommand {
  void exec() override;
};

#endif
