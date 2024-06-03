#ifndef UNDO_COMMAND_HPP
#define UNDO_COMMAND_HPP

#include "SceneEditCommand.hpp"

class UndoCommand : public SceneEditCommand {
  void exec() override;
};

#endif
