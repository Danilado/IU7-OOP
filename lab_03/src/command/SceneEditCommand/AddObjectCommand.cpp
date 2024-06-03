#include "AddObjectCommand.hpp"
#include "SceneManager.hpp"
#include "SingletonTemplate.hpp"

void AddObjectCommand::exec() {
  SceneManager &sm = Singleton<SceneManager>::instance();

  id_dst = sm.addObject(obj);
}
