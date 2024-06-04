#include "WireframeBuilder.hpp"
#include "JsonAdapterSolution.hpp"
#include "WireframeModel.hpp"

ObjectPtr WireframeModelDirector::create(BaseSource &src) {
  WireframeModelBuilder builder{};

  std::shared_ptr<WireframeModel> res = std::make_shared<WireframeModel>();
  res->data = std::move(builder.buildModelData(src));
  res->transform =
      std::shared_ptr<TransformationMatrix>(builder.buildTransformMatrix(src));

  return res;
}

std::unique_ptr<BaseModelData>
WireframeModelBuilder::buildModelData(BaseSource &src) {
  std::shared_ptr<BaseJsonAdapter> jsonAdapter =
      JsonAdapterSolution::createNlohmannJsonAdapter();

  return jsonAdapter->JsonParseObjData(src);
}
