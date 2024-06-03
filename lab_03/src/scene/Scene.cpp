#include "Scene.hpp"
#include <algorithm>

ObjectPtr Scene::getObject(size_t id) { return objects.at(id); }

size_t Scene::addObject(ObjectPtr obj) {
  objects[object_id_counter++] = obj;
  return object_id_counter - 1;
}

bool Scene::removeObject(size_t id) { return objects.erase(id) > 0; }

Scene::SceneIterator Scene::begin() { return objects.begin(); }

Scene::SceneIterator Scene::end() { return objects.end(); }
