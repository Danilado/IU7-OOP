#include "RedoCommand.hpp"
#include "HistoryManager.hpp"
#include "SingletonTemplate.hpp"

void RedoCommand::exec() {
  HistoryManager &hm = Singleton<HistoryManager>::instance();

  hm.redo(target);
}
