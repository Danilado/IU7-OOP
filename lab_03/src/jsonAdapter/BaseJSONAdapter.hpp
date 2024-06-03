#ifndef BASE_JSON_ADAPTER_HPP
#define BASE_JSON_ADAPTER_HPP

#include "BaseSource.hpp"
#include "Scene.hpp"
#include "TransformationMatrix.hpp"

class WireframeModel;
class OrthogonalCamera;
class ProjectionCamera;

class BaseModelData;

#include <memory>
#include <string>

class JsonObjDirectorSolution {
public:
  enum class TYPES { WIREFRAME, ORTHOCAM, PROJCAM };
};

class BaseJsonAdapter {
protected:
  virtual std::string
  JsonStringifyTransformMatrix(TransformationMatrix &transform) = 0;

  virtual JsonObjDirectorSolution::TYPES get_type(std::string key);

  std::map<std::string, JsonObjDirectorSolution::TYPES> stmap{
      {"WireframeModel", JsonObjDirectorSolution::TYPES::WIREFRAME},
      {"OrthogonalCamera", JsonObjDirectorSolution::TYPES::ORTHOCAM},
      {"ProjectionCamera", JsonObjDirectorSolution::TYPES::PROJCAM}};

  virtual std::unique_ptr<BaseModelData>
  JsonParseNodeEdgeListData(BaseSource &src) = 0;

  virtual std::unique_ptr<BaseModelData>
  JsonParseAdjacencyListData(BaseSource &src) = 0;

  virtual std::string JsonStringifyObjData(BaseModelData &data) = 0;

public:
  virtual JsonObjDirectorSolution::TYPES JsonParseType(BaseSource &src) = 0;
  virtual std::unique_ptr<Scene> JsonParseScene(BaseSource &src) = 0;

  virtual std::unique_ptr<BaseModelData> JsonParseObjData(BaseSource &src) = 0;
  virtual std::unique_ptr<TransformationMatrix>
  JsonParseTransformMatrix(BaseSource &src) = 0;

  virtual std::string JsonStringifyScene(Scene &scene) = 0;
  virtual std::string JsonStringifyWireframe(WireframeModel &src) = 0;
  virtual std::string JsonStringifyOrthoCam(OrthogonalCamera &src) = 0;
  virtual std::string JsonStringifyProjCam(ProjectionCamera &src) = 0;
};

#endif
