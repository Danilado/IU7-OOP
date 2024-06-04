#include "nlohmannJSONAdapter.hpp"
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
    // TODO: add handlers
  } catch (const json::type_error &e) {
    // TODO: add handlers
  }

  return get_type(key);
}

void NlohmannJsonAdapter::validateJTransMat(
    std::vector<std::vector<double>> &transmat) {
  if (transmat.size() != TransformationMatrix::dim + 1)
    throw std::exception();
  for (size_t i = 0; i < TransformationMatrix::dim + 1; ++i) {
    if (transmat[i].size() != TransformationMatrix::dim + 1)
      throw std::exception();
  }

  // todo: add custom exceptions
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
    // TODO: add handlers
  } catch (const json::type_error &e) {
    // TODO: add handlers
  }

  if (type != "TransformationMatrix")
    try {
      data = data.at("transform"); // add custom exceptions
    } catch (const json::out_of_range &e) {
      // TODO: add handlers
    }

  std::vector<std::vector<double>> jtransmat;
  try {
    jtransmat = data.at("data").get<std::vector<std::vector<double>>>();
  } catch (const json::out_of_range &e) {
    // TODO: add handlers
  } catch (const json::type_error &e) {
    // TODO: add handlers
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
    // TODO: add handlers
  } catch (const json::type_error &e) {
    // TODO: add handlers
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
  res["transform"] = JsonStringifyTransformMatrix(*src.getTransformation());
  res["data"] = JsonStringifyObjData(*src.data);

  return res.dump();
}

std::string NlohmannJsonAdapter::JsonStringifyOrthoCam(OrthogonalCamera &src) {
  json res = {{"type", "OrthogonalCamera"}};
  res["transform"] = JsonStringifyTransformMatrix(*src.getTransformation());

  return res.dump();
}

std::string NlohmannJsonAdapter::JsonStringifyProjCam(ProjectionCamera &src) {
  json res = {{"type", "ProjectionCamera"}};
  res["transform"] = JsonStringifyTransformMatrix(*src.getTransformation());

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
    // TODO: add handlers
  } catch (const json::type_error &e) {
    // TODO: add handlers
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
    // TODO: add handlers
  } catch (const json::type_error &e) {
    // TODO: add handlers
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
    // TODO: add handlers
  } catch (const json::type_error &e) {
    // TODO: add handlers
  }

  if (type != "NodeEdgeListData")
    try {
      data = data.at("data"); // add custom exceptions
    } catch (const json::out_of_range &e) {
      // TODO: add handlers
    }

  std::unique_ptr<std::vector<NodeEdgeListData::Node>> nodes;
  try {
    nodes = JsonParseNodes(data.at("nodes").dump());
  } catch (const json::out_of_range &e) {
    // TODO: add handlers
  }

  res->nodes = *nodes;

  std::unique_ptr<std::vector<std::shared_ptr<BaseModelData::IdEdge>>> edges;

  try {
    edges = jsonParseIdEdges(data.at("edges").dump());
  } catch (const json::out_of_range &e) {
    // TODO: add handlers
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

  return json{res}.dump();
}

std::string NlohmannJsonAdapter::JsonStringifyIdEdges(
    const BaseModelData::IdEdgeVector &idEdges) {
  std::vector<std::pair<size_t, size_t>> res;

  for (auto &idedgeptr : *idEdges)
    res.push_back(std::pair<size_t, size_t>(idedgeptr->getFirstId(),
                                            idedgeptr->getSecondId()));

  return json{res}.dump();
}

std::string NlohmannJsonAdapter::JsonStringifyObjData(BaseModelData &data) {
  json res = {{"type", "NodeEdgeListData"}};
  res["nodes"] = JsonStringifyNodes(data.getNodes());
  res["edges"] = JsonStringifyIdEdges(data.getIdEdges());

  return res.dump();
}
