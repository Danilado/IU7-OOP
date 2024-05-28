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
  objects = std::make_unique<ObjectComposite>();
  std::unique_ptr<ObjectMemento> objmemptr;

  for (objmemptr.reset(memento->objectsCaretaker->get().release());
       objmemptr != nullptr;
       objmemptr.reset(memento->objectsCaretaker->get().release()))
    objects->add(std::make_unique<Object>(objmemptr));

  camera_id = memento->camera_id;
}

ObjectComposite &Scene::getObjects(void) { return *objects.get(); }

ObjectPtr Scene::getObject(size_t id) {
  Object::iterator it = std::find_if(
      objects->begin(), objects->end(),
      [id](const ObjectPtr &objpt) { return id == objpt->getId(); });

  return it == objects->end() ? nullptr : *it;
}

SceneMemento::SceneMemento(const Scene &s) {
  camera_id = s.camera_id;

  objectsCaretaker = std::make_unique<ObjectCaretaker>();

  Object::iterator beg = s.objects->begin();
  Object::iterator end = s.objects->end();

  for (auto it = beg; it != end; ++it)
    objectsCaretaker->set((*it)->createMemento());
}
