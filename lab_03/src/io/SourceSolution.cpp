#include "SourceSolution.hpp"
#include "FileSource.hpp"
#include "StringSource.hpp"

std::shared_ptr<BaseSource>
SourceSolution::createFileSrc(const std::string &filename) {
  return std::make_shared<FileSource>(filename);
}

std::shared_ptr<BaseSource>
SourceSolution::createStringSrc(std::shared_ptr<std::string> src) {
  return std::make_shared<StringSource>(src);
}
