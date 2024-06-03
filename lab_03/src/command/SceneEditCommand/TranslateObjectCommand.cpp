#include "TranslateObjectCommand.hpp"
#include "SceneManager.hpp"
#include "SingletonTemplate.hpp"
#include "TranslateObjectVisitor.hpp"

void TranslateObjectCommand::transform_target() {
  SceneManager &sm = Singleton<SceneManager>::instance();
  std::shared_ptr<Scene> scene = sm.getScene();

  ObjectPtr objp = scene->getObject(target);
  objp->accept(*vis);
}

void TranslateObjectCommand::transform_all() {
  SceneManager &sm = Singleton<SceneManager>::instance();
  std::shared_ptr<Scene> scene = sm.getScene();
  vis->visit(*scene);
}

void TranslateObjectCommand::exec() {
  if (target == 0)
    transform_all();
  else
    transform_target();
}
