#include "ScaleObjectCommand.hpp"
#include "SingletonTemplate.hpp"
#include "TransformManager.hpp"

void ScaleObjectCommand::exec() {
  TransformManager &tm = Singleton<TransformManager>::instance();
  tm.ScaleObject(origin, scale, target);
}
