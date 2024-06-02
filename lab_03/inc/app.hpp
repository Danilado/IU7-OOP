#ifndef APP_HPP
#define APP_HPP

#include "BaseCommand.hpp"
#include <memory>

class App {
private:
public:
  void exec(const std::shared_ptr<BaseCommand> &cmd) const;
};

#endif
