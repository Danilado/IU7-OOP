#ifndef SCENE_DATA_HELPER_HPP
#define SCENE_DATA_HELPER_HPP

#include <map>
#include <set>
#include <string>

class MainWindow;

class SceneDataHelper {
private:
  std::map<size_t, std::string> objects;
  std::set<size_t> cameras;
  MainWindow *mw;

  void addObject(size_t id, const std::string &meta);
  void removeObject(size_t id);

public:
  SceneDataHelper(MainWindow *mw);
  ~SceneDataHelper() = default;

  void addModel(size_t id, const std::string &meta);
  void removeModel(size_t id);

  void addCamera(size_t id, const std::string &meta);
  void removeCamera(size_t id);

  std::map<size_t, std::string> &getObjects();

  size_t getObjId();
  size_t getCamId();

  SceneDataHelper(const SceneDataHelper &) = delete;
  SceneDataHelper &operator=(const SceneDataHelper &) = delete;

  size_t getCamLength();
};

#endif
