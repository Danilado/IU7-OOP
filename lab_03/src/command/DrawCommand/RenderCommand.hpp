#ifndef RENDER_COMMAND_HPP
#define RENDER_COMMAND_HPP

#include "DrawCommand.hpp"

class RenderCommand : public DrawCommand {
public:
  RenderCommand() = default;
  ~RenderCommand() = default;
  void exec() override;
};

#endif
