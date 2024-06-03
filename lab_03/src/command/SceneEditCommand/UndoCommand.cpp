#include "UndoCommand.hpp"
#include "HistoryManager.hpp"
#include "SingletonTemplate.hpp"

void UndoCommand::exec() {
  HistoryManager &hm = Singleton<HistoryManager>::instance();

  hm.undo(target);
}
