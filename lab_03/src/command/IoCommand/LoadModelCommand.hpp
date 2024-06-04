#ifndef LOAD_MODEL_COMMAND_HPP
#define LOAD_MODEL_COMMAND_HPP

#include "IoCommand.hpp"

class LoadModelCommand : public LoadCommand {
public:
  explicit LoadModelCommand(std::string source) : LoadCommand(source) {}
  void exec() override;
};

#endif
