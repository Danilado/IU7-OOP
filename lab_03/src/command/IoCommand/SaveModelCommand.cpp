#include "SaveModelCommand.hpp"
#include "IoManager.hpp"
#include "SceneManager.hpp"
#include "SingletonTemplate.hpp"

void SaveModelCommand::exec() {
  IoManager &iom = Singleton<IoManager>::instance();
  SceneManager &sm = Singleton<SceneManager>::instance();

  iom.saveObject(*sm.getScene()->getObject(id), dst);
}
