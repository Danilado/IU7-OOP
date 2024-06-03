#include "nlohmannJSONAdapter.hpp"
#include "OrthogonalCamera.hpp"
#include "ProjectionCamera.hpp"
#include "Scene.hpp"
#include "StringDestination.hpp"
#include "WireframeModel.hpp"

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

JsonObjDirectorSolution::TYPES
NlohmannJsonAdapter::JsonParseType(BaseSource &src) {
  auto data = json::parse(src.readall());
  src.reset();

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
    throw std::exception(); // add custom exceptions

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
  return nullptr;
}

std::unique_ptr<BaseModelData>
NlohmannJsonAdapter::JsonParseObjData(BaseSource &src) {
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

std::unique_ptr<BaseModelData>
NlohmannJsonAdapter::JsonParseNodeEdgeListData(BaseSource &src) {
  return nullptr;
}

std::unique_ptr<BaseModelData>
NlohmannJsonAdapter::JsonParseAdjacencyListData(BaseSource &src) {
  return nullptr;
}

std::string NlohmannJsonAdapter::JsonStringifyObjData(BaseModelData &data) {
  return "";
}
