#ifndef DST_SOLUTION_HPP
#define DST_SOLUTION_HPP

#include "BaseDestination.hpp"
#include <fstream>
#include <memory>

class DstSolution {
public:
  static std::unique_ptr<BaseDestination> create(std::ofstream &filedst);
  static std::unique_ptr<BaseDestination> create(std::string &stringdst);
};

#endif
