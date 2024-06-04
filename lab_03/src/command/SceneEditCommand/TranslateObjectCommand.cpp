#include "TranslateObjectCommand.hpp"
#include "SingletonTemplate.hpp"
#include "TransformManager.hpp"

void TranslateObjectCommand::exec() {
  TransformManager &tm = Singleton<TransformManager>::instance();
  tm.TranslateObject(offset, target);
}
