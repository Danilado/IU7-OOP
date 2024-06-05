#include "BaseJSONAdapter.hpp"
#include "BaseException.hpp"

ObjectDirectorSolution::types BaseJsonAdapter::get_type(std::string key) {
  if (stmap.contains(key))
    return stmap.at(key);

  throw myException(BaseException, "get_type", "Unknown Type.");
}
