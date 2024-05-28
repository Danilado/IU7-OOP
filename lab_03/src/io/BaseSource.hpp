#ifndef BASE_SOURCE_HPP
#define BASE_SOURCE_HPP

#include <string>

class BaseSource {
public:
  BaseSource() = default;
  virtual ~BaseSource() = default;
  virtual std::string read(size_t bytes = 0) = 0;
  virtual std::string readline(void) = 0;
};

#endif
