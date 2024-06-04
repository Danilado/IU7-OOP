#include "ObjectBuilder.hpp"
#include "BaseJSONAdapter.hpp"
#include "JsonAdapterSolution.hpp"
#include <memory>

std::unique_ptr<TransformationMatrix>
BaseObjectBuilder::buildTransformMatrix(BaseSource &src) {
  std::shared_ptr<BaseJsonAdapter> jsonAdapter =
      JsonAdapterSolution::createNlohmannJsonAdapter();

  return jsonAdapter->JsonParseTransformMatrix(src);
}
