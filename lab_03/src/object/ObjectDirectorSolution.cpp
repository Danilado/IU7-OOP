#include "ObjectDirectorSolution.hpp"
#include "BaseSource.hpp"
#include "JsonAdapterSolution.hpp"
#include "nlohmannJSONAdapter.hpp"

std::shared_ptr<BaseObjectDirector>
ObjectDirectorSolution::create(BaseSource &src) {
  src.reset();
  std::shared_ptr<BaseJsonAdapter> jsonAdapter =
      JsonAdapterSolution::createNlohmannJsonAdapter();

  ObjectDirectorSolution::types type = jsonAdapter->JsonParseType(src);

  return typemap.at(type);
}
