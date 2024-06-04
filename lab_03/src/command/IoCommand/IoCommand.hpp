#ifndef IO_COMMAND_HPP
#define IO_COMMAND_HPP

#include "BaseCommand.hpp"
#include <memory>

class IoCommand : public BaseCommand {};

class LoadCommand : public IoCommand {
protected:
  std::string src;

public:
  LoadCommand() = delete;
  explicit LoadCommand(std::string source) : src(source) {}
};

class SaveCommand : public IoCommand {
protected:
  std::string dst;

public:
  SaveCommand() = delete;
  explicit SaveCommand(std::string dest) : dst(dest) {}
};

#endif
