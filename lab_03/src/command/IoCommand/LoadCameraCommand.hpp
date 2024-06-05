#ifndef LOAD_CAMERA_COMMAND_HPP
#define LOAD_CAMERA_COMMAND_HPP

#include "IoCommand.hpp"

class LoadCameraCommand : public LoadCommand {
private:
  size_t &dst;

public:
  explicit LoadCameraCommand(std::string source, size_t &dst)
      : LoadCommand(source), dst(dst) {}
  void exec() override;
};

#endif
