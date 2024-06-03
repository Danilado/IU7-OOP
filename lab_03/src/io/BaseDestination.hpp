#ifndef BASE_DESTINATION_HPP
#define BASE_DESTINATION_HPP

#include <string>

class BaseDestination {
public:
  virtual void write(const std::string &data) = 0;
  virtual void write(const char *data) = 0;
};

#endif
