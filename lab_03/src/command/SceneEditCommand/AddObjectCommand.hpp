#ifndef ADD_OBJECT_COMMAND_HPP
#define ADD_OBJECT_COMMAND_HPP

#include "Object.hpp"
#include "SceneEditCommand.hpp"
#include <cstdlib>

class AddObjectCommand : public SceneEditCommand {
private:
  ObjectPtr obj;
  size_t &id_dst;

public:
  AddObjectCommand(ObjectPtr obj, size_t &id_dst) : obj(obj), id_dst(id_dst) {}
  void exec() override;
};

#endif
