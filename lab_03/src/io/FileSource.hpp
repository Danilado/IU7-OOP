#ifndef FILE_SOURCE_HPP
#define FILE_SOURCE_HPP

#include "BaseSource.hpp"
#include <cstdlib>
#include <fstream>
#include <memory>

class FileSource : public BaseSource {
private:
  std::fstream stream;

public:
  FileSource() = delete;
  explicit FileSource(std::string &filename);
  ~FileSource() = default;

  std::string read(size_t bytes = 0) override;
  std::string readall() override;
  void reset() override;
};

#endif
