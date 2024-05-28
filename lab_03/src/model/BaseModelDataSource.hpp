#ifndef BASE_MODEL_DATA_SOURCE_HPP
#define BASE_MODEL_DATA_SOURCE_HPP

#include "BaseModelData.hpp"
#include "BaseSource.hpp"

class BaseModelDataSource {
private:
  std::unique_ptr<BaseModelData> data;
  using NodeIterator = std::vector<BaseModelData::Node>::const_iterator;
  using EdgeIterator = std::vector<BaseModelData::Edge>::const_iterator;

public:
  BaseModelData::Node nextNode(void);
  BaseModelData::Edge nextEdge(void);
  virtual std::unique_ptr<BaseModelData> getData(void) = 0;
};

#endif
