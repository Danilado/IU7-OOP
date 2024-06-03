#include "StringDestination.hpp"

void StringDestination::write(const std::string &data) { dst.append(data); }
void StringDestination::write(const char *data) { dst.append(data); }
