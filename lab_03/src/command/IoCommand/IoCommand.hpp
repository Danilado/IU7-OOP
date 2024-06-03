#ifndef IO_COMMAND_HPP
#define IO_COMMAND_HPP

#include "BaseDestination.hpp"
#include "BaseSource.hpp"

#include "BaseCommand.hpp"
#include <memory>

class IoCommand : public BaseCommand {};

class LoadCommand : public IoCommand {
private:
  std::shared_ptr<BaseSource> src;

public:
  LoadCommand() = delete;
  explicit LoadCommand(std::shared_ptr<BaseSource> source) : src(source) {}
};

class SaveCommand : public IoCommand {
private:
  std::shared_ptr<BaseDestination> dst;

public:
  SaveCommand() = delete;
  explicit SaveCommand(std::shared_ptr<BaseDestination> dest) : dst(dest) {}
};

#endif
