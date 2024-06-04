#include "CameraManager.hpp"
#include "OrthogonalCamera.hpp"
#include "PTSCSolutionVisitor.hpp"
#include "ProjectionCamera.hpp"
#include "SceneManager.hpp"
#include "SingletonTemplate.hpp"

CameraManager::CameraManager() {
  SceneManager &sm = Singleton<SceneManager>::instance();

  std::shared_ptr<OrthogonalCamera> defaultcam =
      std::make_shared<OrthogonalCamera>();
  cam = defaultcam;
  id = sm.addObject(defaultcam);
}

void CameraManager::setCamera(size_t id) {
  SceneManager &sm = Singleton<SceneManager>::instance();

  ObjectPtr objp = sm.getScene()->getObject(id);
  if (objp == nullptr) {
    throw std::exception(); // todo: add custom exceptoion
  }

  std::shared_ptr<BaseCamera> res = dynamic_pointer_cast<BaseCamera>(res);
  if (res == nullptr) {
    throw std::exception(); // todo: add custom exceptoion
  }

  cam = res;
  this->id = id;
}

size_t CameraManager::getActiveId() { return id; }

std::shared_ptr<BaseCamera> CameraManager::getCamera() { return cam; }

std::shared_ptr<BasePTSCAdapter> CameraManager::getAdapter() {
  std::shared_ptr<BasePTSCAdapter> res;
  PTSCSolutionVisitor ptscvis(res);

  cam->accept(ptscvis);

  return res;
}
