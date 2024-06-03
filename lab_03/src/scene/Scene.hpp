#ifndef SCENE_HPP
#define SCENE_HPP

#include "Object.hpp"
#include "ObjectComposite.hpp"
#include <memory>

class SceneMemento;

class Scene {
  friend SceneMemento;

private:
  std::map<size_t, ObjectPtr> objects;
  size_t object_id_counter = 1;

public:
  Scene() = default;
  ~Scene() = default;

  using SceneIterator = std::map<size_t, ObjectPtr>::const_iterator;
  // Scene(const Scene &origin);
  // Scene(Scene &&origin);
  // Scene(std::unique_ptr<SceneMemento> memento);

  ObjectPtr getObject(size_t id);
  size_t addObject(ObjectPtr obj);
  bool removeObject(size_t id);

  SceneIterator begin();
  SceneIterator end();
};

#endif
