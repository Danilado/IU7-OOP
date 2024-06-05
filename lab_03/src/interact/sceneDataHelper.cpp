#include "sceneDataHelper.hpp"
#include "mainwindow.hpp"

SceneDataHelper::SceneDataHelper(MainWindow *mw) : mw(mw) {}

void SceneDataHelper::addObject(size_t id, const std::string &meta) {
  objects[id] = meta;
}

void SceneDataHelper::removeObject(size_t id) {
  objects.erase(objects.find(id));
}

void SceneDataHelper::addCamera(size_t id, const std::string &meta) {
  cameras.insert(id);
  addObject(id, meta);
  mw->addCameraToBox(id, meta);
}

void SceneDataHelper::addModel(size_t id, const std::string &meta) {
  addObject(id, meta);
  mw->addModelToBox(id, meta);
}

void SceneDataHelper::removeCamera(size_t id) {
  cameras.erase(cameras.find(id));
  removeObject(id);
  mw->removeCameraFromBox(id);
}

void SceneDataHelper::removeModel(size_t id) {
  removeObject(id);
  mw->removeModelFromBox(id);
}

std::map<size_t, std::string> &SceneDataHelper::getObjects() { return objects; }

size_t SceneDataHelper::getCamLength() { return cameras.size(); }
