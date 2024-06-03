#include "SceneManager.hpp"

SceneManager::SceneManager() { scene = std::make_shared<Scene>(); }

std::shared_ptr<Scene> SceneManager::getScene(void) const { return scene; }

void SceneManager::setScene(const std::shared_ptr<Scene> &src) { scene = src; }

size_t SceneManager::addObject(ObjectPtr obj) { return scene->addObject(obj); }

bool SceneManager::removeObject(size_t id) { return scene->removeObject(id); }
