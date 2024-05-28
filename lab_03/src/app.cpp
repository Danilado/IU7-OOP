#include "app.hpp"

void App::exec(const std::shared_ptr<BaseCommand> &cmd) const { cmd->exec(); }
