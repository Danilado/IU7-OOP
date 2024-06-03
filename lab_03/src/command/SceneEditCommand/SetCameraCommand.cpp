#include "SetCameraCommand.hpp"
#include "CameraManager.hpp"
#include "SingletonTemplate.hpp"

void SetCameraCommand::exec() {
  CameraManager &cm = Singleton<CameraManager>::instance();
  cm.setCamera(cam_id);
}
