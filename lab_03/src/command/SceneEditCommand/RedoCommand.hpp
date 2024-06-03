#ifndef REDO_COMMAND_HPP
#define REDO_COMMAND_HPP

#include "SceneEditCommand.hpp"

class RedoCommand : public SceneEditCommand {
  void exec() override;
};

#endif
