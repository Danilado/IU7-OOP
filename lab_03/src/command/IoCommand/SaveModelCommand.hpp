#ifndef SAVE_MODEL_COMMAND_HPP
#define SAVE_MODEL_COMMAND_HPP

#include "IoCommand.hpp"

class SaveModelCommand : public SaveCommand {
private:
  size_t id;

public:
  SaveModelCommand(std::string dest, size_t id) : SaveCommand(dest), id(id) {}
  void exec() override;
};

#endif
