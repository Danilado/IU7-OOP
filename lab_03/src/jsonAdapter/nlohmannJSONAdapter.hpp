#ifndef NLOHMANN_JSON_ADAPTER_HPP
#define NLOHMANN_JSON_ADAPTER_HPP

#include "../external/nlohmann_json/single_include/nlohmann/json.hpp"
#include "BaseJSONAdapter.hpp"
#include "BaseModelData.hpp"

class NlohmannJsonAdapter : public BaseJsonAdapter {
private:
  using json = nlohmann::json;

  void validateJTransMat(std::vector<std::vector<double>> &transmat);

  json myParse(BaseSource &src, std::string funcname);

  json::reference getReference(json &data, std::string key,
                               std::string funcname);
  template <typename T>
  T getTypeFromReference(json::reference &ref, std::string funcname);
  template <typename T>
  T getTypeAt(json &data, std::string key, std::string funcname);

  json JsonifyNodes(const std::vector<BaseModelData::Node> &nodes);
  std::unique_ptr<std::vector<BaseModelData::Node>> JsonParseNodes(json &data);

  json JsonifyIdEdges(const BaseModelData::IdEdgeVector &idEdges);
  std::unique_ptr<std::vector<std::shared_ptr<BaseModelData::IdEdge>>>
  jsonParseIdEdges(json &data);
  json JsonifyTransformMatrix(TransformationMatrix &transform);

  json JsonifyObjData(BaseModelData &data);

  std::unique_ptr<BaseModelData> JsonParseNodeEdgeListData(json &src);
  std::unique_ptr<BaseModelData> JsonParseAdjacencyListData(json &src);
  std::unique_ptr<BaseModelData> JsonParseObjData(json &src);
  std::unique_ptr<TransformationMatrix> JsonParseTransformMatrix(json &src);

protected:
  std::string JsonStringifyObjData(BaseModelData &data) override;
  std::string
  JsonStringifyTransformMatrix(TransformationMatrix &transform) override;
  std::unique_ptr<BaseModelData>
  JsonParseNodeEdgeListData(BaseSource &src) override;
  std::unique_ptr<BaseModelData>
  JsonParseAdjacencyListData(BaseSource &src) override;

public:
  ObjectDirectorSolution::types JsonParseType(BaseSource &src) override;
  std::unique_ptr<Scene> JsonParseScene(BaseSource &src) override;
  std::unique_ptr<TransformationMatrix>
  JsonParseTransformMatrix(BaseSource &src) override;
  std::unique_ptr<BaseModelData> JsonParseObjData(BaseSource &src) override;

  std::string JsonStringifyScene(Scene &scene) override;
  std::string JsonStringifyWireframe(WireframeModel &src) override;
  std::string JsonStringifyOrthoCam(OrthogonalCamera &src) override;
  std::string JsonStringifyProjCam(ProjectionCamera &src) override;
};

#include "nlohmannJSONAdapter.inl"

#endif
