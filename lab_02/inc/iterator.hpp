#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <compare>
#include <memory>
#include <string>

using std::string;

template <typename T> class Vector;

#include "base_iterator.hpp"

template <typename T> class Iterator : public BaseIterator {
  friend class Vector<T>;

public:
  Iterator(const Vector<T> &vec) noexcept;
  Iterator(const Iterator<T> &iter) noexcept;

  ~Iterator();

  auto operator<=>(const Iterator<T> &other) const;
  bool operator==(const Iterator<T> &other) const;
  bool operator!=(const Iterator<T> &other) const;
  operator bool() const;

  T &operator*();
  T *operator->();
  T &operator[](const size_t offset);

  Iterator<T> &operator++();
  Iterator<T> operator++(int);

  Iterator<T> &operator--();
  Iterator<T> operator--(int);

  template <typename U> Iterator<T> operator+(const U val) const;
  template <typename U> Iterator<T> operator-(const U val) const;
  template <typename U> Iterator<T> &operator+=(const U val);
  template <typename U> Iterator<T> &operator-=(const U val);

private:
  T *getPtr() const;
  void checkExpired(const size_t line, string funcname) const;
  void checkBounds(const size_t line, string funcname,
                   const size_t offset = 0) const;

protected:
  std::weak_ptr<T[]> ptr;
};

#include "iterator_functions.inl"
#include "iterator_lifetime.inl"
#include "iterator_operators.inl"

#endif
