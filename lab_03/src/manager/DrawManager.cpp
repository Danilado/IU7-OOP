#include "DrawManager.hpp"
#include "BasePTSCAdapter.hpp"
#include "CameraManager.hpp"
#include "RenderVisitor.hpp"
#include "SceneManager.hpp"
#include "SingletonTemplate.hpp"

void DrawManager::setDrawer(std::shared_ptr<BaseDrawer> drawer) {
  ctx = drawer;
}

void DrawManager::renderScene() {
  validateDrawer();

  SceneManager &sm = Singleton<SceneManager>::instance();
  CameraManager &cm = Singleton<CameraManager>::instance();

  std::shared_ptr<Scene> scene = sm.getScene();
  std::shared_ptr<BasePTSCAdapter> PTSCa = cm.getAdapter();

  RenderVisitor rvis(PTSCa, ctx);
  rvis.visit(*scene);
}

void DrawManager::clear() {
  validateDrawer();
  ctx->clear();
}

void DrawManager::validateDrawer() {
  if (ctx == nullptr)
    throw std::exception(); // todo: add exception
}
