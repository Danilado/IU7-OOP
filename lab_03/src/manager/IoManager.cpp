#include "IoManager.hpp"

void IoManager::saveScene(const Scene &scene, BaseDestination &dst) {}

std::unique_ptr<Scene> IoManager::loadScene(BaseSource &src) {}

void IoManager::saveObject(const Object &obj, BaseDestination &dst) {}

std::unique_ptr<Object> IoManager::loadObject(const std::string &filename) {}
