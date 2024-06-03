#include "RemoveObjectCommand.hpp"
#include "SceneManager.hpp"
#include "SingletonTemplate.hpp"

void RemoveObjectCommand::exec() {
  SceneManager &sm = Singleton<SceneManager>::instance();
  std::shared_ptr<Scene> scene = sm.getScene();

  scene->removeObject(target);
}
