#ifndef NLOHMANN_JSON_ADAPTER_HPP
#define NLOHMANN_JSON_ADAPTER_HPP

#include "../external/nlohmann_json/single_include/nlohmann/json.hpp"
#include "BaseJSONAdapter.hpp"

class NlohmannJsonAdapter : public BaseJsonAdapter {
private:
  using json = nlohmann::json;

  void validateJTransMat(std::vector<std::vector<double>> &transmat);

protected:
  std::string JsonStringifyObjData(BaseModelData &data) override;
  std::string
  JsonStringifyTransformMatrix(TransformationMatrix &transform) override;
  std::unique_ptr<BaseModelData>
  JsonParseNodeEdgeListData(BaseSource &src) override;
  std::unique_ptr<BaseModelData>
  JsonParseAdjacencyListData(BaseSource &src) override;

public:
  JsonObjDirectorSolution::TYPES JsonParseType(BaseSource &src) override;
  std::unique_ptr<Scene> JsonParseScene(BaseSource &src) override;
  std::unique_ptr<TransformationMatrix>
  JsonParseTransformMatrix(BaseSource &src) override;
  std::unique_ptr<BaseModelData> JsonParseObjData(BaseSource &src) override;

  std::string JsonStringifyScene(Scene &scene) override;
  std::string JsonStringifyWireframe(WireframeModel &src) override;
  std::string JsonStringifyOrthoCam(OrthogonalCamera &src) override;
  std::string JsonStringifyProjCam(ProjectionCamera &src) override;
};

#endif
