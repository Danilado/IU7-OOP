#ifndef NLOHMANN_JSON_ADAPTER_HPP
#define NLOHMANN_JSON_ADAPTER_HPP

#include "../external/nlohmann_json/single_include/nlohmann/json.hpp"
#include "BaseJSONAdapter.hpp"

class NlohmannJsonAdapter : public BaseJsonAdapter {
private:
  using json = nlohmann::json;
  string JsonStringifyTransformMatrix(TransformationMatrix &transform) override;

public:
  JsonObjDirectorSolution::TYPES JsonParseType(BaseSource src) override;
  std::unique_ptr<WireframeModel> JsonParseWireframe(BaseSource src) override;
  std::unique_ptr<OrthogonalCamera> JsonParseOrthoCam(BaseSource src) override;
  std::unique_ptr<ProjectionCamera> JsonParseProjCam(BaseSource src) override;
  std::unique_ptr<Scene> JsonParseScene(BaseSource src) override;

  string JsonStringifyScene(Scene &scene) override;
  string JsonStringifyWireframe(WireframeModel &src) override;
  string JsonStringifyOrthoCam(OrthogonalCamera &src) override;
  string JsonStringifyProjCam(ProjectionCamera &src) override;
};

#endif
