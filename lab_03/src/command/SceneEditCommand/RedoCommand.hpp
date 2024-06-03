#ifndef REDO_COMMAND_HPP
#define REDO_COMMAND_HPP

#include "SceneEditCommand.hpp"
#include <cstdlib>


class RedoCommand : public SceneEditCommand {
private:
  size_t target;

public:
  explicit RedoCommand(size_t id) : target(id) {}
  void exec() override;
};

#endif
