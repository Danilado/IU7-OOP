#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <compare>
#include <memory>

template <typename T> class Vector;

#include "base_iterator.hpp"

template <typename T> class Iterator : public BaseIterator {
  friend class Vector<T>;

public:
  Iterator(const Vector<T> &vec) noexcept;
  Iterator(const Iterator<T> &iter) noexcept;

  ~Iterator();

  auto operator<=>(const Iterator<T> &other) const;
  operator bool() const;

  T &operator*();
  const T &operator*() const;

  T *operator->();
  const T *operator->() const;

  T &operator[](const size_t offset);
  const T &operator[](const size_t offset) const;

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
  void checkExpired(const size_t line);
  void checkBounds(const size_t line, const size_t offset = 0);

protected:
  std::weak_ptr<T> ptr;
};

#include "iterator.inl"

#endif
