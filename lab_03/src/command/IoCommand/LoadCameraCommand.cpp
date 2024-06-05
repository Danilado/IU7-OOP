#include "LoadCameraCommand.hpp"
#include "IoManager.hpp"
#include "SceneManager.hpp"
#include "SingletonTemplate.hpp"

void LoadCameraCommand::exec() {
  IoManager &iom = Singleton<IoManager>::instance();
  SceneManager &sm = Singleton<SceneManager>::instance();

  dst = sm.addObject(iom.loadObject(src));
}
