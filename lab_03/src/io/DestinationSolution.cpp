#include "DestinationSolution.hpp"
#include "FileDestination.hpp"
#include "StringDestination.hpp"

std::shared_ptr<BaseDestination>
DestinationSolution::createFileDst(const std::string &filename) {
  return std::make_shared<FileDestination>(filename);
}
std::shared_ptr<BaseDestination>
DestinationSolution::createStringDst(std::string &dst) {
  return std::make_shared<StringDestination>(dst);
}
