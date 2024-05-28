#ifndef COMMON_USINGS_HPP
#define COMMON_USINGS_HPP

#include <memory>
#include <vector>

class Object;

using ObjectPtr = std::shared_ptr<Object>;
using ObjectVector = std::vector<ObjectPtr>;

#endif
