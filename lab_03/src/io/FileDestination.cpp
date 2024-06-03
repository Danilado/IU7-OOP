#include "FileDestination.hpp"

FileDestination::FileDestination(std::string &filename) {
  stream = std::fstream(filename, std::fstream::out);
}

void FileDestination::write(const std::string &data) { stream << data; }
void FileDestination::write(const char *data) { stream << data; }
