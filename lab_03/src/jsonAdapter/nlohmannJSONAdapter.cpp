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

// TODO: Refactor everything (in this file)
// INCLUDING EXCEPTION HANDLING

std::string NlohmannJsonAdapter::JsonStringifyTransformMatrix(
    TransformationMatrix &transform) {
  std::array<std::array<double, TransformationMatrix::dim + 1>,
             TransformationMatrix::dim + 1>
      mat_values;

  for (size_t i = 0; i <= TransformationMatrix::dim; ++i)
    for (size_t j = 0; j <= TransformationMatrix::dim; ++j)
      mat_values[i][j] = transform.transform[i][j];

  json transmatjson = {
      {"type", "TransformationMatrix"},
      {"data", mat_values},
  };

  return transmatjson.dump();
}

ObjectDirectorSolution::types
NlohmannJsonAdapter::JsonParseType(BaseSource &src) {
  src.reset();

  auto data = json::parse(src.readall());

  std::string key;

  try {
    json::reference datatype = data.at("type");
    key = datatype.get_ref<json::string_t &>();
  } catch (const json::out_of_range &e) {
    throw myException(
        BaseException, "JsonParseType",
        "Не удалось определить тип объекта\nПоле type не найдено");
  } catch (const json::type_error &e) {
    throw myException(
        BaseException, "JsonParseType",
        "Не удалось определить тип объекта\nПоле type не является строкой");
  }

  return get_type(key);
}

void NlohmannJsonAdapter::validateJTransMat(
    std::vector<std::vector<double>> &transmat) {
  if (transmat.size() != TransformationMatrix::dim + 1)
    throw myException(BaseException, "validateJTransMat",
                      "Число строк матрицы трансформации в файле некорректно");
  for (size_t i = 0; i < TransformationMatrix::dim + 1; ++i) {
    if (transmat[i].size() != TransformationMatrix::dim + 1)
      throw myException(
          BaseException, "validateJTransMat",
          "Число столбцов на " + std::to_string(i) +
              " строке матрицы трансформации в файле некорректно");
  }
}

std::unique_ptr<TransformationMatrix>
NlohmannJsonAdapter::JsonParseTransformMatrix(BaseSource &src) {
  src.reset();

  std::unique_ptr<TransformationMatrix> res =
      std::make_unique<TransformationMatrix>();

  auto data = json::parse(src.readall());

  std::string type;
  try {
    type = data.at("type").get<std::string>();
  } catch (const json::out_of_range &e) {
    throw myException(BaseException, "JsonParseTransformMatrix",
                      "У считываемого объекта не обнаружено поле type");
  } catch (const json::type_error &e) {
    throw myException(BaseException, "JsonParseTransformMatrix",
                      "Поле type считываемого объекта не является строкой");
  }

  if (type != "TransformationMatrix")
    try {
      data = data.at("transform"); // add custom exceptions
    } catch (const json::out_of_range &e) {
      throw myException(
          BaseException, "JsonParseTransformMatrix",
          "Переданный объект не является матрицей трансформации\n(Тип не "
          "совпал, а поле transform отсутствует)");
    }

  std::vector<std::vector<double>> jtransmat;
  try {
    jtransmat = data.at("data").get<std::vector<std::vector<double>>>();
  } catch (const json::out_of_range &e) {
    throw myException(
        BaseException, "JsonParseTransformMatrix",
        "У матрицы трансформации в файле не обнаружено поле data");
  } catch (const json::type_error &e) {
    throw myException(BaseException, "JsonParseTransformMatrix",
                      "Поле data матрицы трансформации в файле некорректно");
  }

  validateJTransMat(jtransmat);

  for (size_t i = 0; i <= TransformationMatrix::dim; ++i)
    for (size_t j = 0; j <= TransformationMatrix::dim; ++j)
      res->transform[i][j] = jtransmat[i][j];

  return std::move(res);
}

std::unique_ptr<Scene> NlohmannJsonAdapter::JsonParseScene(BaseSource &src) {
  src.reset();
  return nullptr;
}

std::unique_ptr<BaseModelData>
NlohmannJsonAdapter::JsonParseObjData(BaseSource &src) {
  src.reset();
  auto data = json::parse(src.readall());
  data = data.at("data");
  std::string type;
  try {
    type = data.at("type").get<std::string>();
  } catch (const json::out_of_range &e) {
    throw myException(BaseException, "JsonParseObjData",
                      "У считываемого объекта не обнаружено поле type");
  } catch (const json::type_error &e) {
    throw myException(BaseException, "JsonParseObjData",
                      "Поле type считываемого объекта не является строкой");
  }

  if (type == "NodeEdgeListData") {
    return std::move(JsonParseNodeEdgeListData(src));
  } else if (type == "AdjacencyListData") {
  } else
    throw std::exception(); // add custom exceptions

  return nullptr;
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
  res["transform"] =
      json::parse(JsonStringifyTransformMatrix(*src.getTransformation()));
  res["data"] = json::parse(JsonStringifyObjData(*src.data));

  return res.dump();
}

std::string NlohmannJsonAdapter::JsonStringifyOrthoCam(OrthogonalCamera &src) {
  json res = {{"type", "OrthogonalCamera"}};
  res["transform"] =
      json::parse(JsonStringifyTransformMatrix(*src.getTransformation()));

  return res.dump();
}

std::string NlohmannJsonAdapter::JsonStringifyProjCam(ProjectionCamera &src) {
  json res = {{"type", "ProjectionCamera"}};
  res["transform"] =
      json::parse(JsonStringifyTransformMatrix(*src.getTransformation()));

  return res.dump();
}

std::unique_ptr<std::vector<BaseModelData::Node>>
NlohmannJsonAdapter::JsonParseNodes(std::string data) {
  std::unique_ptr<std::vector<BaseModelData::Node>> res =
      std::make_unique<std::vector<BaseModelData::Node>>();

  auto jsondata = json::parse(data);
  std::vector<std::tuple<double, double, double>> jsonnodevector;
  try {
    jsonnodevector =
        jsondata.get<std::vector<std::tuple<double, double, double>>>();
  } catch (const json::out_of_range &e) {
    throw myException(BaseException, "JsonParseNodes",
                      "Считываемый объект что-то типа пуст");
  } catch (const json::type_error &e) {
    throw myException(
        BaseException, "JsonParseNodes",
        "Судя по всему, массив вершин в файле неправильно отформатирован");
  }

  for (auto &entry : jsonnodevector)
    res->push_back(std::make_shared<Point3D>(
        std::get<0>(entry), std::get<1>(entry), std::get<2>(entry)));

  return std::move(res);
}

std::unique_ptr<std::vector<std::shared_ptr<BaseModelData::IdEdge>>>
NlohmannJsonAdapter::jsonParseIdEdges(std::string data) {
  std::unique_ptr<std::vector<std::shared_ptr<BaseModelData::IdEdge>>> res =
      std::make_unique<std::vector<std::shared_ptr<BaseModelData::IdEdge>>>();

  auto jsondata = json::parse(data);
  std::vector<std::pair<size_t, size_t>> jsonedgevector;
  try {
    jsonedgevector = jsondata.get<std::vector<std::pair<size_t, size_t>>>();
  } catch (const json::out_of_range &e) {
    throw myException(BaseException, "JsonParseIdEdges",
                      "Считываемый объект что-то типа пуст");
  } catch (const json::type_error &e) {
    throw myException(
        BaseException, "JsonParseIdEdges",
        "Судя по всему, массив рёбер в файле неправильно отформатирован");
  }

  for (auto &entry : jsonedgevector)
    res->push_back(
        std::make_shared<BaseModelData::IdEdge>(entry.first, entry.second));

  return std::move(res);
}

std::unique_ptr<BaseModelData>
NlohmannJsonAdapter::JsonParseNodeEdgeListData(BaseSource &src) {
  std::unique_ptr<NodeEdgeListData> res = std::make_unique<NodeEdgeListData>();

  src.reset();
  auto data = json::parse(src.readall());

  std::string type;
  try {
    type = data.at("type").get<std::string>();
  } catch (const json::out_of_range &e) {
    throw myException(BaseException, "JsonParseNodeEdgeListData",
                      "У считываемого объекта не обнаружено поле type");
  } catch (const json::type_error &e) {
    throw myException(BaseException, "JsonParseNodeEdgeListData",
                      "Поле type считываемого объекта не является строкой");
  }

  if (type != "NodeEdgeListData")
    try {
      data = data.at("data");
    } catch (const json::out_of_range &e) {
      throw myException(BaseException, "JsonParseNodeEdgeListData",
                        "У считываемого объекта не обнаружено поле data");
    }

  std::unique_ptr<std::vector<NodeEdgeListData::Node>> nodes;
  try {
    nodes = JsonParseNodes(data.at("nodes").dump());
  } catch (const json::out_of_range &e) {
    throw myException(BaseException, "JsonParseNodeEdgeListData",
                      "У считываемого объекта не обнаружено поле nodes");
  }

  res->nodes = *nodes;

  std::unique_ptr<std::vector<std::shared_ptr<BaseModelData::IdEdge>>> edges;

  try {
    edges = jsonParseIdEdges(data.at("edges").dump());
  } catch (const json::out_of_range &e) {
    throw myException(BaseException, "JsonParseNodeEdgeListData",
                      "У считываемого объекта не обнаружено поле edges");
  }

  res->idedges = std::move(edges);

  return std::move(res);
}

std::unique_ptr<BaseModelData>
NlohmannJsonAdapter::JsonParseAdjacencyListData(BaseSource &src) {
  return nullptr;
}

std::string NlohmannJsonAdapter::JsonStringifyNodes(
    const std::vector<BaseModelData::Node> &nodes) {
  std::vector<std::tuple<double, double, double>> res;
  for (auto &node : nodes)
    res.push_back(std::tuple<double, double, double>(
        node->get_x(), node->get_y(), node->get_z()));

  json j = res;
  return j.dump();
}

std::string NlohmannJsonAdapter::JsonStringifyIdEdges(
    const BaseModelData::IdEdgeVector &idEdges) {
  std::vector<std::pair<size_t, size_t>> res;

  for (auto &idedgeptr : *idEdges)
    res.push_back(std::pair<size_t, size_t>(idedgeptr->getFirstId(),
                                            idedgeptr->getSecondId()));

  json j = res;
  return j.dump();
}

std::string NlohmannJsonAdapter::JsonStringifyObjData(BaseModelData &data) {
  json res = {{"type", "NodeEdgeListData"}};
  res["nodes"] = json::parse(JsonStringifyNodes(data.getNodes()));
  res["edges"] = json::parse(JsonStringifyIdEdges(data.getIdEdges()));

  return res.dump();
}
