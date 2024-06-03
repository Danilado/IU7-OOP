#include "CleanCommand.hpp"
#include "DrawManager.hpp"
#include "SingletonTemplate.hpp"

void CleanCommand::exec() {
  DrawManager &dm = Singleton<DrawManager>::instance();
  dm.clear();
}
