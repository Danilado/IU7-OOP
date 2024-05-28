#ifndef CLEAN_COMMAND_HPP
#define CLEAN_COMMAND_HPP

#include "DrawCommand.hpp"

class CleanCommand : public DrawCommand {
public:
  CleanCommand() = default;
  ~CleanCommand() = default;
  void exec() override;
};

#endif
