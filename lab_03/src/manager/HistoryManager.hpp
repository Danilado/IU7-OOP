#ifndef HISTORY_MANAGER_HPP
#define HISTORY_MANAGER_HPP

#include "Scene.hpp"
#include <memory>

class HistoryManager {
private:
  std::unique_ptr<SceneCaretaker> past;
  std::unique_ptr<SceneCaretaker> future;

  void clear_future(void);

public:
  void save(std::unique_ptr<Scene> scene);
  bool undo(std::unique_ptr<Scene> scene);
  bool redo(std::unique_ptr<Scene> scene);
  void clear(void);
};

#endif
