#ifndef REMOVE_OBJECT_COMMAND_HPP
#define REMOVE_OBJECT_COMMAND_HPP

#include "SceneEditCommand.hpp"
#include <cstdlib>

class RemoveObjectCommand : public SceneEditCommand {
private:
  size_t target;

public:
  RemoveObjectCommand(size_t id) : target(id) {}
  void exec() override;
};

#endif
