#ifndef LOAD_MODEL_COMMAND_HPP
#define LOAD_MODEL_COMMAND_HPP

#include "IoCommand.hpp"

class LoadModelCommand : public LoadCommand {
private:
  size_t &dst;

public:
  explicit LoadModelCommand(std::string source, size_t &dst)
      : LoadCommand(source), dst(dst) {}
  void exec() override;
};

#endif
