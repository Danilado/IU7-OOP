#ifndef BASE_MANAGER_HPP
#define BASE_MANAGER_HPP

#include "Scene.hpp"
#include <memory>

class SceneManager {
private:
  std::unique_ptr<Scene> scene;

public:
  SceneManager() = default;
  ~SceneManager() = default;

  std::shared_ptr<Scene> getScene(void) const;
  void setScene(const std::unique_ptr<Scene> &src);
  bool addObject(ObjectPtr obj);
  bool removeObject(size_t id);
  bool removeObject(ObjectPtr obj);
  bool setCamera(size_t id);
};

#endif
