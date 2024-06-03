#ifndef LOAD_MODEL_COMMAND_HPP
#define LOAD_MODEL_COMMAND_HPP

#include "IoCommand.hpp"

class LoadModelCommand : public LoadCommand {
  void exec() override;
};

#endif
