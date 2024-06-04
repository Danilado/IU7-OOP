#include "IoManager.hpp"
#include "JsonAdapterSolution.hpp"
#include "Object.hpp"
#include "ObjectDirectorSolution.hpp"
#include "SingletonTemplate.hpp"
#include "SourceSolution.hpp"
#include "nlohmannJSONAdapter.hpp"

void IoManager::saveScene(const Scene &scene, BaseDestination &dst) {}

std::unique_ptr<Scene> IoManager::loadScene(BaseSource &src) { return nullptr; }

void IoManager::saveObject(const Object &obj, BaseDestination &dst) {}

std::unique_ptr<Object> IoManager::loadObject(const std::string &filename) {
  std::shared_ptr<BaseJsonAdapter> jsonAdapter =
      JsonAdapterSolution::createNlohmannJsonAdapter();
  std::shared_ptr<BaseSource> src = SourceSolution::createFileSrc(filename);

  jsonAdapter->JsonParseType(*src);

  ObjectDirectorSolution &objds = Singleton<ObjectDirectorSolution>::instance();

  return std::move(objds.create(*src)->create(*src));
}
