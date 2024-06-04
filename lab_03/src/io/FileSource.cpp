#include "FileSource.hpp"
#include <sstream>

FileSource::FileSource(const std::string &filename) {
  stream = std::fstream(filename, std::fstream::in);
}

std::string FileSource::read(size_t bytes) {
  char *buf = new char[bytes];

  stream.read(buf, bytes);

  std::string res(buf);
  delete[] buf;

  return res;
}

std::string FileSource::readall() {
  std::stringstream buf;

  std::string line;
  while (std::getline(stream, line))
    buf << line;

  reset();

  return buf.str();
}

void FileSource::reset() {
  stream.clear();
  stream.seekg(0, stream.beg);
}
