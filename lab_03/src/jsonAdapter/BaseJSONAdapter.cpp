#include "BaseJSONAdapter.hpp"

ObjectDirectorSolution::types BaseJsonAdapter::get_type(std::string key) {
  if (stmap.contains(key))
    return stmap.at(key);

  // TODO: Add custom Exception
  throw std::exception();
}
