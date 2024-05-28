#ifndef SRC_SOLUTION_HPP
#define SRC_SOLUTION_HPP

#include "BaseSource.hpp"
#include <fstream>
#include <memory>

class DstSolution {
public:
  static std::unique_ptr<BaseSource> create(std::ifstream &filesrc);
  static std::unique_ptr<BaseSource> create(const std::string &stringsrc);
};

#endif
