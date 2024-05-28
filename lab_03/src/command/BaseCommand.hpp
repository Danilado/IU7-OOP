#ifndef BASE_COMMAND_HPP
#define BASE_COMMAND_HPP

class BaseCommand {
public:
  BaseCommand() = default;
  virtual ~BaseCommand() = default;
  virtual void exec() = 0;
};

#endif
