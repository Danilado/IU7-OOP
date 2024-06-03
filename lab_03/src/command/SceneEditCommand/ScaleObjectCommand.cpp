#include "ScaleObjectCommand.hpp"
#include "ScaleObjectVisitor.hpp"
#include "SceneManager.hpp"
#include "SingletonTemplate.hpp"

void ScaleObjectCommand::transform_target() {
  SceneManager &sm = Singleton<SceneManager>::instance();
  std::shared_ptr<Scene> scene = sm.getScene();

  ObjectPtr objp = scene->getObject(target);
  objp->accept(*vis);
}

void ScaleObjectCommand::transform_all() {
  SceneManager &sm = Singleton<SceneManager>::instance();
  std::shared_ptr<Scene> scene = sm.getScene();
  vis->visit(*scene);
}

void ScaleObjectCommand::exec() {
  if (target == 0)
    transform_all();
  else
    transform_target();
}
