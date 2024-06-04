#ifndef JSON_ADAPTER_SOLUTION
#define JSON_ADAPTER_SOLUTION

#include "BaseJSONAdapter.hpp"
#include <memory>

class JsonAdapterSolution {
public:
  static std::shared_ptr<BaseJsonAdapter> createNlohmannJsonAdapter();
};

#endif
