#ifndef STRING_DESTINATION_HPP
#define STRING_DESTINATION_HPP

#include "BaseDestination.hpp"
#include <string>

class StringDestination : public BaseDestination {
protected:
  std::string &dst;

public:
  StringDestination() = delete;
  explicit StringDestination(std::string &dst) : dst(dst) {}
  ~StringDestination() = default;

  void write(const std::string &data) override;
  void write(const char *data) override;
};

#endif
