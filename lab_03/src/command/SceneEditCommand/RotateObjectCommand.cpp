#include "RotateObjectCommand.hpp"
#include "RotateObjectVisitor.hpp"
#include "SceneManager.hpp"
#include "SingletonTemplate.hpp"

void RotateObjectCommand::transform_target() {
  SceneManager &sm = Singleton<SceneManager>::instance();
  std::shared_ptr<Scene> scene = sm.getScene();

  ObjectPtr objp = scene->getObject(target);
  objp->accept(*vis);
}

void RotateObjectCommand::transform_all() {
  SceneManager &sm = Singleton<SceneManager>::instance();
  std::shared_ptr<Scene> scene = sm.getScene();
  vis->visit(*scene);
}

void RotateObjectCommand::exec() {
  if (target == 0)
    transform_all();
  else
    transform_target();
}
