#ifndef BASE_JSON_ADAPTER_HPP
#define BASE_JSON_ADAPTER_HPP

#include "BaseSource.hpp"
#include "Scene.hpp"
#include "TransformationMatrix.hpp"

class WireframeModel;
class OrthogonalCamera;
class ProjectionCamera;

#include <string>

using std::string;

class JsonObjDirectorSolution {
public:
  enum class TYPES { WIREFRAME, ORTHOCAM, PROJCAM };
};

class BaseJsonAdapter {
protected:
  virtual string
  JsonStringifyTransformMatrix(TransformationMatrix &transform) = 0;

public:
  virtual JsonObjDirectorSolution::TYPES JsonParseType(BaseSource src) = 0;
  virtual std::unique_ptr<WireframeModel>
  JsonParseWireframe(BaseSource src) = 0;
  virtual std::unique_ptr<OrthogonalCamera>
  JsonParseOrthoCam(BaseSource src) = 0;
  virtual std::unique_ptr<ProjectionCamera>
  JsonParseProjCam(BaseSource src) = 0;
  virtual std::unique_ptr<Scene> JsonParseScene(BaseSource src) = 0;

  virtual string JsonStringifyScene(Scene &scene) = 0;
  virtual string JsonStringifyWireframe(WireframeModel &src) = 0;
  virtual string JsonStringifyOrthoCam(OrthogonalCamera &src) = 0;
  virtual string JsonStringifyProjCam(ProjectionCamera &src) = 0;
};

#endif
