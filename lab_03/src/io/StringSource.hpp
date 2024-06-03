#ifndef STRING_SOURCE_HPP
#define STRING_SOURCE_HPP

#include "BaseSource.hpp"
#include <cstdlib>
#include <memory>

class StringSource : public BaseSource {
private:
  std::shared_ptr<std::string> src;
  size_t offset = 0;

  void validate_offset();

public:
  StringSource() = delete;
  explicit StringSource(std::shared_ptr<std::string> src) : src(src) {}
  ~StringSource() = default;

  std::string read(size_t bytes = 0) override;
  std::string readall() override;
  void reset() override;
};

#endif
