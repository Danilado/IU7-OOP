#ifndef DESTINATION_SOLUTION_HPP
#define DESTINATION_SOLUTION_HPP

#include "BaseDestination.hpp"
#include <memory>

class DestinationSolution {
public:
  static std::shared_ptr<BaseDestination> createFileDst(std::string &filename);
  static std::shared_ptr<BaseDestination> createStringDst(std::string &dst);
};

#endif
