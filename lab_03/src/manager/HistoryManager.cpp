#include "HistoryManager.hpp"
#include "SceneManager.hpp"
#include "SingletonTemplate.hpp"

HistoryManager::HistoryManager() {
  std::unique_ptr<ObjectCaretaker> past = std::make_unique<ObjectCaretaker>();
  std::unique_ptr<ObjectCaretaker> future = std::make_unique<ObjectCaretaker>();
}

void HistoryManager::save(size_t object_id) {
  if (future->contains(object_id))
    future->clear_id(object_id);

  SceneManager &sm = Singleton<SceneManager>::instance();
  std::shared_ptr<Scene> scene = sm.getScene();

  ObjectPtr objpt = scene->getObject(object_id);

  past->set(object_id, objpt, objpt->createMemento());
}

void HistoryManager::undo(size_t object_id) {
  if (!past->contains(object_id))
    throw std::exception(); // TODO: add custon exceptions

  SceneManager &sm = Singleton<SceneManager>::instance();
  std::shared_ptr<Scene> scene = sm.getScene();

  ObjectPtr objpt = scene->getObject(object_id);

  std::shared_ptr<ObjectMemento> mem = past->get(object_id);

  future->set(object_id, objpt, objpt->createMemento());
  objpt->restoreMemento(mem);
}

void HistoryManager::redo(size_t object_id) {
  if (!future->contains(object_id))
    throw std::exception(); // TODO: add custon exceptions
  save(object_id);

  SceneManager &sm = Singleton<SceneManager>::instance();
  std::shared_ptr<Scene> scene = sm.getScene();

  ObjectPtr objpt = scene->getObject(object_id);

  std::shared_ptr<ObjectMemento> mem = future->get(object_id);

  past->set(object_id, objpt, objpt->createMemento());
  objpt->restoreMemento(mem);
}

void HistoryManager::clear(void) {
  past->clear();
  future->clear();
}
