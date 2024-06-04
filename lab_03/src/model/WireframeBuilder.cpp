#include "WireframeBuilder.hpp"
#include "JsonAdapterSolution.hpp"
#include "WireframeModel.hpp"

std::unique_ptr<Object> WireframeModelDirector::create(BaseSource &src) {

  src.reset();
  WireframeModelBuilder builder{};

  std::unique_ptr<WireframeModel> res = std::make_unique<WireframeModel>();
  res->data = std::move(builder.buildModelData(src));
  res->transform =
      std::shared_ptr<TransformationMatrix>(builder.buildTransformMatrix(src));

  return std::move(res);
}

std::unique_ptr<BaseModelData>
WireframeModelBuilder::buildModelData(BaseSource &src) {
  src.reset();
  std::shared_ptr<BaseJsonAdapter> jsonAdapter =
      JsonAdapterSolution::createNlohmannJsonAdapter();

  return jsonAdapter->JsonParseObjData(src);
}
