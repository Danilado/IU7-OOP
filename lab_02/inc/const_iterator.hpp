#ifndef CONST_ITERATOR_HPP
#define CONST_ITERATOR_HPP

#include "base_iterator.hpp"
#include "my_concepts.hpp"
#include <compare>
#include <memory>
#include <string>

using std::string;

template <NumType T> //
class Vector;

template <typename T> //
class ConstIterator : public BaseIterator {

public:
  ConstIterator(const Vector<T> &vec) noexcept;
  ConstIterator(const ConstIterator<T> &iter) noexcept;

  ~ConstIterator();

  auto operator<=>(const ConstIterator<T> &other) const;
  operator bool() const noexcept;

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
  void checkExpired(const size_t line, const string &funcname) const;
  void checkBounds(const size_t line, const string &funcname,
                   const size_t offset = 0) const;

protected:
  std::weak_ptr<T[]> ptr;
};

#include "const_iterator.inl"

#endif
