#include "IoManager.hpp"
#include "DestinationSolution.hpp"
#include "JSONStringifyVisitor.hpp"
#include "JsonAdapterSolution.hpp"
#include "Object.hpp"
#include "ObjectDirectorSolution.hpp"
#include "SingletonTemplate.hpp"
#include "SourceSolution.hpp"
#include "nlohmannJSONAdapter.hpp"

void IoManager::saveScene(Scene &scene, BaseDestination &dst) {}

std::unique_ptr<Scene> IoManager::loadScene(BaseSource &src) { return nullptr; }

std::unique_ptr<Object> IoManager::loadObject(BaseSource &src) {
  std::shared_ptr<BaseJsonAdapter> jsonAdapter =
      JsonAdapterSolution::createNlohmannJsonAdapter();
  jsonAdapter->JsonParseType(src);

  ObjectDirectorSolution &objds = Singleton<ObjectDirectorSolution>::instance();

  return std::move(objds.create(src)->create(src));
}

std::unique_ptr<Object> IoManager::loadObject(const std::string &filename) {
  std::shared_ptr<BaseSource> src = SourceSolution::createFileSrc(filename);

  return loadObject(*src);
}

void IoManager::saveObject(Object &obj, BaseDestination &dst) {
  std::shared_ptr<BaseJsonAdapter> jsonAdapter =
      JsonAdapterSolution::createNlohmannJsonAdapter();
  auto vis = std::make_shared<JsonStringifyVisitor>(dst, *jsonAdapter);

  obj.accept(*vis);
}

void IoManager::saveObject(Object &obj, const std::string &filename) {
  std::shared_ptr<BaseDestination> dst =
      DestinationSolution::createFileDst(filename);

  saveObject(obj, *dst);
}
