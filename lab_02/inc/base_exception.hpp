#ifndef BASE_EXCEPTION_HPP
#define BASE_EXCEPTION_HPP

#include <exception>
#include <string>

using std::string;

class BaseException : public std::exception {
public:
  BaseException(const string &filename, const size_t &line,
                const string &class_name, const string &method_name,
                const string &info);

  virtual const char *what() const noexcept override;

protected:
  string msg;
};

#endif
