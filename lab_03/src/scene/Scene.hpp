#ifndef SCENE_HPP
#define SCENE_HPP

#include "Object.hpp"
#include "ObjectComposite.hpp"
#include <memory>

class SceneMemento;

class Scene {
  friend SceneMemento;

private:
  std::unique_ptr<ObjectComposite> objects;
  size_t camera_id;

public:
  Scene();
  Scene(const Scene &origin);
  Scene(Scene &&origin);
  Scene(std::unique_ptr<SceneMemento> memento);
  ~Scene() = default;

  ObjectComposite &getObjects(void);
  ObjectPtr getObject(size_t id);
  bool addObject(ObjectPtr obj);
  bool removeObject(size_t id);
  bool removeObject(ObjectPtr obj);
  bool setCamera(size_t id);

  std::unique_ptr<SceneMemento> createMemento(void) const;
  void restoreMemento(std::unique_ptr<SceneMemento> memento);
};

class SceneMemento {
  friend Scene;

private:
  size_t camera_id;
  std::unique_ptr<ObjectCaretaker> objectsCaretaker;

public:
  SceneMemento(const Scene &s);
  void set(const Scene &s);
  std::unique_ptr<Scene> get(void);
};

class SceneCaretaker {
private:
  std::vector<std::unique_ptr<SceneMemento>> mementos;

public:
  std::unique_ptr<SceneMemento> get(void);
  void set(std::unique_ptr<SceneMemento> memento);
};

#endif
