#include "CameraManager.hpp"
#include "BaseException.hpp"
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
    throw myException(BaseException, "setCamera",
                      "Object with id " + std::to_string(id) + " not found");
  }

  if (dynamic_cast<const BaseCamera *>(objp.get()) == nullptr)
    throw myException(BaseException, "setCamera",
                      "Object with id " + std::to_string(id) +
                          " is not a camera");

  cam = objp;
  this->id = id;
}

size_t CameraManager::getActiveId() { return id; }

std::shared_ptr<Object> CameraManager::getCamera() { return cam; }

std::shared_ptr<BasePTSCAdapter> CameraManager::getAdapter() {
  std::shared_ptr<BasePTSCAdapter> res;
  PTSCSolutionVisitor ptscvis(res);

  cam->accept(ptscvis);

  return res;
}
