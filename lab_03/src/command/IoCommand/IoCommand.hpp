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
};

class SaveCommand : public IoCommand {
private:
  std::shared_ptr<BaseDestination> dst;
};

#endif
