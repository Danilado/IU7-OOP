#ifndef HISTORY_MANAGER_HPP
#define HISTORY_MANAGER_HPP

#include "Object.hpp"
#include <memory>

class HistoryManager {
private:
  std::unique_ptr<ObjectCaretaker> past;
  std::unique_ptr<ObjectCaretaker> future;

public:
  HistoryManager();
  ~HistoryManager() = default;

  void save(size_t object_id);
  void undo(size_t object_id);
  void redo(size_t object_id);
  void clear(void);

  HistoryManager(const HistoryManager &) = delete;
  HistoryManager &operator=(const HistoryManager &) = delete;
};

#endif
