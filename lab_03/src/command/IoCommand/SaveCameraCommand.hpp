#ifndef SAVE_CAMERA_COMMAND_HPP
#define SAVE_CAMERA_COMMAND_HPP

#include "IoCommand.hpp"

class SaveCameraCommand : public SaveCommand {
private:
  size_t id;

public:
  SaveCameraCommand(std::string dest, size_t id) : SaveCommand(dest), id(id) {}
  void exec() override;
};

#endif
