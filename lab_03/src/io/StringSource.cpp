#include "StringSource.hpp"

void StringSource::validate_offset() {
  if (offset > src->length())
    offset = src->length();
}

std::string StringSource::read(size_t bytes) {
  std::string res = src->substr(offset, bytes);

  offset += bytes;
  validate_offset();

  return res;
}

std::string StringSource::readall() {
  std::string res = src->substr(offset);

  offset = SIZE_MAX;
  validate_offset();

  return res;
}

void StringSource::reset() { offset = 0; }
