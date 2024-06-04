#include "RotateObjectCommand.hpp"
#include "SingletonTemplate.hpp"
#include "TransformManager.hpp"

void RotateObjectCommand::exec() {
  TransformManager &tm = Singleton<TransformManager>::instance();
  tm.RotateObject(origin, rotation, target, deg);
}
