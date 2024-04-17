#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include "base_exception.hpp"

class PointerExpiredException : public BaseException {
public:
  PointerExpiredException(const string &filename, const size_t &line,
                          const string &class_name, const string &method_name,
                          const string &info =
#ifdef LANG_RU
                              "Срок действия указателя истёк."
#else
                              "Pointer expired."
#endif
                          )
      : BaseException(filename, line, class_name, method_name, info){};
};

class IndexOutOfBoundsException : public BaseException {
public:
  IndexOutOfBoundsException(const string &filename, const size_t &line,
                            const string &class_name, const string &method_name,
                            const string &info =
#ifdef LANG_RU
                                "Индекс за пределами структуры."
#else
                                "Index out of bounds."
#endif
                            )
      : BaseException(filename, line, class_name, method_name, info){};
};

using std::to_string;

class SizeMismatchException : public BaseException {
public:
  SizeMismatchException(const string &filename, const size_t &line,
                        const string &class_name, const string &method_name,
                        const size_t size1, const size_t size2,
                        const string &info =
#ifdef LANG_RU
                            "Размеры векторов не совпадают. "
#else
                            "Vector sizes don't match. "
#endif
                        )
      : BaseException(filename, line, class_name, method_name,
                      info + to_string(size1) + " vs " + to_string(size2)){};
};

class MemoryException : public BaseException {
public:
  MemoryException(const string &filename, const size_t &line,
                  const string &class_name, const string &method_name,
                  const string &info =
#ifdef LANG_RU
                      "Ошибка выделения памяти. "
#else
                      "Memory allocation error. "
#endif
                  )
      : BaseException(filename, line, class_name, method_name, info){};
};

#endif
