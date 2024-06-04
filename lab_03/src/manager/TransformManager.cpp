#include "TransformManager.hpp"
#include "RotateObjectVisitor.hpp"
#include "ScaleObjectVisitor.hpp"
#include "SceneManager.hpp"
#include "SingletonTemplate.hpp"
#include "TranslateObjectVisitor.hpp"

void TransformManager::apply(BaseVisitor &vis, size_t target) {
  SceneManager &sm = Singleton<SceneManager>::instance();
  auto scene = sm.getScene();

  if (target == 0)
    vis.visit(*scene);
  else
    scene->getObject(target)->accept(vis);
}

void TransformManager::TranslateObject(Point3D &offset, size_t target) {
  TranslateObjectVisitor vis(offset);
  apply(vis, target);
}

void TransformManager::ScaleObject(Point3D &origin, Point3D &scale,
                                   size_t target) {
  ScaleObjectVisitor vis(origin, scale);
  apply(vis, target);
}

void TransformManager::RotateObject(Point3D &origin, Point3D &angles,
                                    size_t target, bool deg) {
  RotateObjectVisitor vis(origin, angles, deg);
  apply(vis, target);
}
