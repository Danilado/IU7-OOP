#ifndef IO_MANAGER_HPP
#define IO_MANAGER_HPP

#include "BaseDestination.hpp"
#include "BaseSource.hpp"
#include "JSONStringifyVisitor.hpp"
#include "Object.hpp"
#include "Scene.hpp"
#include <string>

class IoManager {
private:
public:
  IoManager() = default;
  ~IoManager() = default;

  void saveScene(Scene &scene, BaseDestination &dst);
  std::unique_ptr<Scene> loadScene(BaseSource &src);

  void saveObject(Object &obj, BaseDestination &dst);
  std::unique_ptr<Object> loadObject(BaseSource &src);

  IoManager(const IoManager &) = delete;
  IoManager &operator=(const IoManager &) = delete;

  std::unique_ptr<Object> loadObject(const std::string &filename);
  void saveObject(Object &obj, const std::string &filename);
};

#endif
