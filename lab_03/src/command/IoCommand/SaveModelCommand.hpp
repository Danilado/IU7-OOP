#ifndef SAVE_MODEL_COMMAND_HPP
#define SAVE_MODEL_COMMAND_HPP

#include "IoCommand.hpp"

class SaveModelCommand : public SaveCommand {
  void exec() override;
};

#endif
