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

#include "ObjectDirectorSolution.hpp"

class BaseJsonAdapter {
protected:
  virtual std::string
  JsonStringifyTransformMatrix(TransformationMatrix &transform) = 0;

  virtual ObjectDirectorSolution::types get_type(std::string key);

  std::map<std::string, ObjectDirectorSolution::types> stmap{
      {"WireframeModel", ObjectDirectorSolution::types::WIREFRAME},
      {"OrthogonalCamera", ObjectDirectorSolution::types::ORTHOCAM},
      {"ProjectionCamera", ObjectDirectorSolution::types::PROJCAM}};

  virtual std::unique_ptr<BaseModelData>
  JsonParseNodeEdgeListData(BaseSource &src) = 0;

  virtual std::unique_ptr<BaseModelData>
  JsonParseAdjacencyListData(BaseSource &src) = 0;

  virtual std::string JsonStringifyObjData(BaseModelData &data) = 0;

public:
  virtual ObjectDirectorSolution::types JsonParseType(BaseSource &src) = 0;
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
