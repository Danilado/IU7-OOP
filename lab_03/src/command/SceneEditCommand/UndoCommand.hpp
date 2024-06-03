#ifndef UNDO_COMMAND_HPP
#define UNDO_COMMAND_HPP

#include "SceneEditCommand.hpp"
#include <cstdlib>


class UndoCommand : public SceneEditCommand {
private:
  size_t target;

public:
  explicit UndoCommand(size_t id) : target(id) {}
  void exec() override;
};

#endif
