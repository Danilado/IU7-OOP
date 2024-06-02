#include "nlohmannJSONAdapter.hpp"

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

  return std::string(transmatjson);
}
