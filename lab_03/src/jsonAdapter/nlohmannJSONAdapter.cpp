#include "nlohmannJSONAdapter.hpp"
#include "BaseException.hpp"
#include "BaseModelData.hpp"
#include "NodeEdgeListData.hpp"
#include "OrthogonalCamera.hpp"
#include "ProjectionCamera.hpp"
#include "Scene.hpp"
#include "StringDestination.hpp"
#include "WireframeModel.hpp"
#include <QDebug>
#include <array>
#include <tuple>
#include <vector>

std::string NlohmannJsonAdapter::JsonStringifyTransformMatrix(
    TransformationMatrix &transform) {
  return JsonifyTransformMatrix(transform).dump();
}

NlohmannJsonAdapter::json
NlohmannJsonAdapter::JsonifyTransformMatrix(TransformationMatrix &transform) {
  std::array<std::array<double, TransformationMatrix::dim + 1>,
             TransformationMatrix::dim + 1>
      mat_values;

  for (size_t i = 0; i <= TransformationMatrix::dim; ++i)
    for (size_t j = 0; j <= TransformationMatrix::dim; ++j)
      mat_values[i][j] = transform.transform[i][j];

  return json({
      {"type", "TransformationMatrix"},
      {"data", mat_values},
  });
}

ObjectDirectorSolution::types
NlohmannJsonAdapter::JsonParseType(BaseSource &src) {
  auto data = myParse(src, __FUNCTION__);
  std::string key = getTypeAt<std::string>(data, "type", __FUNCTION__);

  return get_type(key);
}

void NlohmannJsonAdapter::validateJTransMat(
    std::vector<std::vector<double>> &transmat) {
  if (transmat.size() != TransformationMatrix::dim + 1)
    throw myException(BaseException, __FUNCTION__,
                      "Число строк матрицы трансформации в файле некорректно");
  for (size_t i = 0; i < TransformationMatrix::dim + 1; ++i) {
    if (transmat[i].size() != TransformationMatrix::dim + 1)
      throw myException(
          BaseException, __FUNCTION__,
          "Число столбцов на " + std::to_string(i) +
              " строке матрицы трансформации в файле некорректно");
  }
}

std::unique_ptr<TransformationMatrix>
NlohmannJsonAdapter::JsonParseTransformMatrix(BaseSource &src) {
  auto data = myParse(src, __FUNCTION__);
  std::unique_ptr<TransformationMatrix> res =
      std::make_unique<TransformationMatrix>();

  std::string type = getTypeAt<std::string>(data, "type", __FUNCTION__);

  if (type != "TransformationMatrix")
    try {
      data = data.at("transform"); // add custom exceptions
    } catch (const json::out_of_range &e) {
      throw myException(
          BaseException, __FUNCTION__,
          "Переданный объект не является матрицей трансформации\n(Тип не "
          "совпал, а поле transform отсутствует)");
    }

  return JsonParseTransformMatrix(data);
  return std::move(res);
}

std::unique_ptr<Scene> NlohmannJsonAdapter::JsonParseScene(BaseSource &src) {
  throw myException(BaseException, __FUNCTION__, "\nUNIMPLEMENTED");
  return nullptr;
}

std::unique_ptr<BaseModelData>
NlohmannJsonAdapter::JsonParseObjData(BaseSource &src) {
  auto data = myParse(src, __FUNCTION__);
  data = getReference(data, "data", __FUNCTION__);

  std::string type = getTypeAt<std::string>(data, "type", __FUNCTION__);

  if (type == "NodeEdgeListData")
    return std::move(JsonParseNodeEdgeListData(data));
  else if (type == "AdjacencyListData")
    return std::move(JsonParseAdjacencyListData(data));
  else
    throw myException(BaseException, __FUNCTION__, "UNKNOWN DATA TYPE");

  return JsonParseObjData(data);
}

std::string NlohmannJsonAdapter::JsonStringifyScene(Scene &scene) {
  json res = {{"type", "Scene"}};
  std::string objdata = "[";
  StringDestination strdst(objdata);

  JsonStringifyVisitor vis(strdst, *this);
  vis.visit(scene);

  objdata.append("]");

  res["objects"] = objdata;

  return res.dump();
}

std::string NlohmannJsonAdapter::JsonStringifyWireframe(WireframeModel &src) {
  json res = {{"type", "WireframeModel"}};
  res["transform"] = JsonifyTransformMatrix(*src.getTransformation());
  res["data"] = JsonifyObjData(*src.data);

  return res.dump();
}

std::string NlohmannJsonAdapter::JsonStringifyOrthoCam(OrthogonalCamera &src) {
  json res = {{"type", "OrthogonalCamera"}};
  res["transform"] = JsonifyTransformMatrix(*src.getTransformation());

  return res.dump();
}

std::string NlohmannJsonAdapter::JsonStringifyProjCam(ProjectionCamera &src) {
  json res = {{"type", "ProjectionCamera"}};
  res["transform"] = JsonifyTransformMatrix(*src.getTransformation());

  return res.dump();
}

std::unique_ptr<BaseModelData>
NlohmannJsonAdapter::JsonParseNodeEdgeListData(BaseSource &src) {
  auto data = myParse(src, __FUNCTION__);
  return JsonParseNodeEdgeListData(data);
}

std::unique_ptr<BaseModelData>
NlohmannJsonAdapter::JsonParseAdjacencyListData(BaseSource &src) {
  throw myException(BaseException, __FUNCTION__, "UNIMPLEMENTED");
  return nullptr;
}

std::string NlohmannJsonAdapter::JsonStringifyObjData(BaseModelData &data) {
  json res = {{"type", "NodeEdgeListData"}};
  res["nodes"] = JsonifyNodes(data.getNodes());
  res["edges"] = JsonifyIdEdges(data.getIdEdges());

  return res.dump();
}

NlohmannJsonAdapter::json NlohmannJsonAdapter::myParse(BaseSource &src,
                                                       std::string funcname) {
  src.reset();

  try {
    return json::parse(src.readall());
  } catch (const json::parse_error &e) {
    throw myException(
        BaseException, funcname,
        "Файл не содержит объект. (Это не json, или файл повреждён?)");
  }
}

NlohmannJsonAdapter::json::reference
NlohmannJsonAdapter::getReference(json &data, std::string key,
                                  std::string funcname) {
  try {
    return data.at(key);
  } catch (const json::out_of_range &e) {
    throw myException(BaseException, funcname,
                      "У считываемого объекта не обнаружено поле " + key);
  } catch (const json::type_error &e) {
    throw myException(BaseException, funcname,
                      "Считываемый файл не содержит обект");
  }
}

NlohmannJsonAdapter::json NlohmannJsonAdapter::JsonifyNodes(
    const std::vector<BaseModelData::Node> &nodes) {
  std::vector<std::tuple<double, double, double>> res;
  for (auto &node : nodes)
    res.push_back(std::tuple<double, double, double>(
        node->get_x(), node->get_y(), node->get_z()));

  return res;
}

std::unique_ptr<std::vector<BaseModelData::Node>>
NlohmannJsonAdapter::JsonParseNodes(json &data) {
  std::unique_ptr<std::vector<BaseModelData::Node>> res =
      std::make_unique<std::vector<BaseModelData::Node>>();

  std::vector<std::tuple<double, double, double>> jsonnodevector =
      getTypeFromReference<std::vector<std::tuple<double, double, double>>>(
          data, __FUNCTION__);

  for (auto &entry : jsonnodevector)
    res->push_back(std::make_shared<Point3D>(
        std::get<0>(entry), std::get<1>(entry), std::get<2>(entry)));

  return std::move(res);
}

NlohmannJsonAdapter::json NlohmannJsonAdapter::JsonifyIdEdges(
    const BaseModelData::IdEdgeVector &idEdges) {
  std::vector<std::pair<size_t, size_t>> res;

  for (auto &idedgeptr : *idEdges)
    res.push_back(std::pair<size_t, size_t>(idedgeptr->getFirstId(),
                                            idedgeptr->getSecondId()));

  return res;
}

std::unique_ptr<std::vector<std::shared_ptr<BaseModelData::IdEdge>>>
NlohmannJsonAdapter::jsonParseIdEdges(json &data) {
  std::unique_ptr<std::vector<std::shared_ptr<BaseModelData::IdEdge>>> res =
      std::make_unique<std::vector<std::shared_ptr<BaseModelData::IdEdge>>>();

  std::vector<std::pair<size_t, size_t>> jsonedgevector =
      getTypeFromReference<std::vector<std::pair<size_t, size_t>>>(
          data, __FUNCTION__);

  for (auto &entry : jsonedgevector)
    res->push_back(
        std::make_shared<BaseModelData::IdEdge>(entry.first, entry.second));

  return std::move(res);
}

std::unique_ptr<BaseModelData>
NlohmannJsonAdapter::JsonParseNodeEdgeListData(json &src) {
  std::unique_ptr<NodeEdgeListData> res = std::make_unique<NodeEdgeListData>();

  std::string type = getTypeAt<std::string>(src, "type", __FUNCTION__);

  std::unique_ptr<std::vector<NodeEdgeListData::Node>> nodes =
      JsonParseNodes(getReference(src, "nodes", __FUNCTION__));

  res->nodes = *nodes;

  std::unique_ptr<std::vector<std::shared_ptr<BaseModelData::IdEdge>>> edges =
      jsonParseIdEdges(getReference(src, "edges", __FUNCTION__));

  res->idedges = std::move(edges);

  return std::move(res);
}

std::unique_ptr<BaseModelData>
NlohmannJsonAdapter::JsonParseAdjacencyListData(json &src) {
  throw myException(BaseException, __FUNCTION__, "UNIMPLEMENTED");
  return nullptr;
}

std::unique_ptr<BaseModelData>
NlohmannJsonAdapter::JsonParseObjData(json &src) {
  std::string type = getTypeAt<std::string>(src, "type", __FUNCTION__);

  if (type == "NodeEdgeListData")
    return std::move(JsonParseNodeEdgeListData(src));
  else if (type == "AdjacencyListData")
    return std::move(JsonParseAdjacencyListData(src));
  else
    throw myException(BaseException, __FUNCTION__, "UNKNOWN DATA TYPE");

  return nullptr;
}

std::unique_ptr<TransformationMatrix>
NlohmannJsonAdapter::JsonParseTransformMatrix(json &src) {
  std::unique_ptr<TransformationMatrix> res =
      std::make_unique<TransformationMatrix>();

  std::string type = getTypeAt<std::string>(src, "type", __FUNCTION__);
  if (type != "TransformationMatrix")
    throw myException(BaseException, __FUNCTION__,
                      "Переданный объект не является матрицей трансформации");

  auto jtransmat =
      getTypeAt<std::vector<std::vector<double>>>(src, "data", __FUNCTION__);

  validateJTransMat(jtransmat);

  for (size_t i = 0; i <= TransformationMatrix::dim; ++i)
    for (size_t j = 0; j <= TransformationMatrix::dim; ++j)
      res->transform[i][j] = jtransmat[i][j];

  return std::move(res);
}

NlohmannJsonAdapter::json
NlohmannJsonAdapter::JsonifyObjData(BaseModelData &data) {
  json res = {{"type", "NodeEdgeListData"}};
  res["nodes"] = JsonifyNodes(data.getNodes());
  res["edges"] = JsonifyIdEdges(data.getIdEdges());

  return res;
}
