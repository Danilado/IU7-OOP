#ifndef CONST_ITERATOR_HPP
#define CONST_ITERATOR_HPP

#include <compare>
#include <memory>
#include <string>

using std::string;

template <typename T> class Vector;

#include "base_iterator.hpp"

template <typename T> class ConstIterator : public BaseIterator {
  friend class Vector<T>;

public:
  ConstIterator(const Vector<T> &vec) noexcept;
  ConstIterator(const ConstIterator<T> &iter) noexcept;

  ~ConstIterator();

  auto operator<=>(const ConstIterator<T> &other) const;
  operator bool() const;

  const T &operator*() const;
  const T *operator->() const;
  const T &operator[](const size_t offset) const;

  ConstIterator<T> &operator++();
  ConstIterator<T> operator++(int);

  ConstIterator<T> &operator--();
  ConstIterator<T> operator--(int);

  template <typename U> ConstIterator<T> operator+(const U val) const;
  template <typename U> ConstIterator<T> operator-(const U val) const;
  template <typename U> ConstIterator<T> &operator+=(const U val);
  template <typename U> ConstIterator<T> &operator-=(const U val);

private:
  T *getPtr() const;
  void checkExpired(const size_t line, string funcname) const;
  void checkBounds(const size_t line, string funcname,
                   const size_t offset = 0) const;

protected:
  std::weak_ptr<T[]> ptr;
};

#include "const_iterator.inl"

#endif
