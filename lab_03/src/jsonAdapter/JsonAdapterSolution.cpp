#include "JsonAdapterSolution.hpp"
#include "nlohmannJSONAdapter.hpp"

std::shared_ptr<BaseJsonAdapter>
JsonAdapterSolution::createNlohmannJsonAdapter() {
  return std::make_shared<NlohmannJsonAdapter>();
}
