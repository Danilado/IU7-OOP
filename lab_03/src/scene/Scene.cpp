#include "Scene.hpp"
#include <algorithm>

Scene::Scene() {
  objects = std::make_unique<ObjectComposite>();
  camera_id = 0;
}

Scene::Scene(const Scene &origin) {
  objects = std::make_unique<ObjectComposite>();
  camera_id = origin.camera_id;

  Object::iterator beg = origin.objects->begin();
  Object::iterator end = origin.objects->end();

  for (auto it = beg; it != end; ++it)
    objects->add((*it)->clone());
}

Scene::Scene(Scene &&origin) {
  objects.reset(origin.objects.release());
  origin.objects = nullptr;

  camera_id = origin.camera_id;
}

Scene::Scene(std::unique_ptr<SceneMemento> memento) {
  restoreMemento(std::move(memento));
}

ObjectComposite &Scene::getObjects(void) { return *objects.get(); }

ObjectPtr Scene::getObject(size_t id) {
  Object::iterator it = std::find_if(
      objects->begin(), objects->end(),
      [id](const ObjectPtr &objpt) { return id == objpt->getId(); });

  return it == objects->end() ? nullptr : *it;
}

bool Scene::addObject(ObjectPtr obj) { return objects->add(obj); }

bool Scene::removeObject(size_t id) {
  return objects->remove(std::find_if(
      objects->begin(), objects->end(),
      [id](const ObjectPtr &objpt) { return id == objpt->getId(); }));
}

bool Scene::removeObject(ObjectPtr obj) {
  return objects->remove(std::find(objects->begin(), objects->end(), obj));
}

bool Scene::setCamera(size_t id) {
  if (getObject(id) != nullptr)
    return bool(camera_id = id);

  return false;
}

std::unique_ptr<SceneMemento> Scene::createMemento(void) const {
  return std::make_unique<SceneMemento>(*this);
}

void Scene::restoreMemento(std::unique_ptr<SceneMemento> memento) {
  objects = std::make_unique<ObjectComposite>();
  std::unique_ptr<ObjectMemento> objmemptr;

  for (objmemptr.reset(memento->objectsCaretaker->get().release());
       objmemptr != nullptr;
       objmemptr.reset(memento->objectsCaretaker->get().release()))
    objects->add(std::make_unique<Object>(objmemptr));

  camera_id = memento->camera_id;
}

SceneMemento::SceneMemento(const Scene &s) { set(s); }

void SceneMemento::set(const Scene &s) {
  camera_id = s.camera_id;

  objectsCaretaker = std::make_unique<ObjectCaretaker>();

  Object::iterator beg = s.objects->begin();
  Object::iterator end = s.objects->end();

  for (auto it = beg; it != end; ++it)
    objectsCaretaker->set((*it)->createMemento());
}

std::unique_ptr<Scene> SceneMemento::get(void) {
  return std::make_unique<Scene>(*this);
}

std::unique_ptr<SceneMemento> SceneCaretaker::get(void) {
  if (!mementos.size())
    return nullptr;

  std::unique_ptr<SceneMemento> last = std::move(mementos.back());
  mementos.pop_back();

  return last;
}

void SceneCaretaker::set(std::unique_ptr<SceneMemento> memento) {
  mementos.push_back(std::move(memento));
}
