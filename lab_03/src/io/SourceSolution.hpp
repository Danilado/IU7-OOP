#ifndef SOURCE_SOLUTION_HPP
#define SOURCE_SOLUTION_HPP

#include "BaseSource.hpp"
#include <memory>

class SourceSolution {
public:
  static std::shared_ptr<BaseSource> createFileSrc(std::string &filename);
  static std::shared_ptr<BaseSource>
  createStringSrc(std::shared_ptr<std::string> src);
};

#endif
