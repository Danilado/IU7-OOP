#include "BaseException.hpp"

BaseException::BaseException(const string &filename, const size_t &line,
                             const string &class_name,
                             const string &method_name, const string &info) {
  msg = "Exception occured:" + info + "\n" +                  //
        "In " + class_name + "." + method_name + "\n" +       //
        "In " + filename + ":" + std::to_string(line) + "\n"; //
}

const char *BaseException::what() const noexcept { return msg.c_str(); }
