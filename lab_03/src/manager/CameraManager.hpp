#ifndef CAMERA_MANAGER_HPP
#define CAMERA_MANAGER_HPP

#include "BaseCamera.hpp"
#include "BasePTSCAdapter.hpp"
#include <memory>

class CameraManager {
private:
  size_t id;
  std::shared_ptr<Object> cam;

public:
  CameraManager();
  ~CameraManager() = default;

  void setCamera(size_t id);
  size_t getActiveId();

  std::shared_ptr<Object> getCamera();
  std::shared_ptr<BasePTSCAdapter> getAdapter();

  CameraManager(const CameraManager &) = delete;
  CameraManager &operator=(const CameraManager &) = delete;
};

#endif
