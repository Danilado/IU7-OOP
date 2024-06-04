#include "ObjectBuilder.hpp"
#include "BaseJsonAdapter"
#include "JsonAdapterSolution.hpp"
#include <memory>

std::unique_ptr<TransformationMatrix> buildTransformMatrix(BaseSource &src) {
  std::shared_ptr<BaseJsonAdapter> jsonAdapter =
      JsonAdapterSolution::createNlohmannJsonAdapter();

  return jsonAdapter->JsonParseTransformMatrix(src);
}
