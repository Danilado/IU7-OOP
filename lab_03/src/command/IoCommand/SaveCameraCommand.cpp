#include "SaveCameraCommand.hpp"
#include "IoManager.hpp"
#include "SceneManager.hpp"
#include "SingletonTemplate.hpp"

void SaveCameraCommand::exec() {
  IoManager &iom = Singleton<IoManager>::instance();
  SceneManager &sm = Singleton<SceneManager>::instance();

  iom.saveObject(*sm.getScene()->getObject(id), dst);
}
