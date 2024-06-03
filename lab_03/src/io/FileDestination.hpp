#ifndef FILE_DESTINATION_HPP
#define FILE_DESTINATION_HPP

#include "BaseDestination.hpp"
#include <fstream>

class FileDestination : public BaseDestination {
private:
  std::fstream stream;

public:
  FileDestination() = delete;
  explicit FileDestination(std::string &filename);
  ~FileDestination() = default;

  void write(const std::string &data) override;
  void write(const char *data) override;
};

#endif
