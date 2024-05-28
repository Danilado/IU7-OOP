#ifndef BASE_DESTINATION_HPP
#define BASE_DESTINATION_HPP

#include <string>

class BaseDestination {
public:
  BaseDestination() = default;
  virtual ~BaseDestination() = default;
  virtual int write(std::string &data) = 0;
};

#endif
