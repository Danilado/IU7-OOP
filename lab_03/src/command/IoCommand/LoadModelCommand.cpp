#include "LoadModelCommand.hpp"
#include "IoManager.hpp"
#include "SceneManager.hpp"
#include "SingletonTemplate.hpp"


void LoadModelCommand::exec() {
  IoManager &iom = Singleton<IoManager>::instance();
  SceneManager &sm = Singleton<SceneManager>::instance();

  sm.addObject(iom.loadObject(src));
}
