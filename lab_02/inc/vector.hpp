#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <compare>
#include <cstdlib>
#include <memory>

#include "base_container.hpp"
#include "const_iterator.hpp"
#include "iterator.hpp"
#include "my_concepts.hpp"

template <NumType T> class Vector : public BaseContainer {

  friend Iterator<T>;
  friend ConstIterator<T>;

public:
#pragma region lifetime
  Vector() noexcept;
  explicit Vector(const Vector<T> &vec);
  Vector(Vector<T> &&tmpvec) noexcept;

  explicit Vector(const size_t size);
  Vector(const size_t size, const T &fill);
  Vector(const size_t size, const T *src);

  Vector(const std::initializer_list<T> &init);
  template <IterType IterT> Vector(IterT ibeg, IterT iend);

  ~Vector();
#pragma endregion lifetime

#pragma region operations

  operator bool() const;
  Vector<T> neg() const;
  Vector<T> operator-() const;

  double length() const;
  template <NumType U> Vector<U> getUnit() const;

  bool isZero() const;
  bool isUnit() const;

  template <NumType U> auto operator<=>(const Vector<U> &other) const;
  template <NumType U> bool operator==(const Vector<U> &other) const;
  template <NumType U> bool operator!=(const Vector<U> &other) const;

  Vector<T> &operator=(const Vector<T> &vec);
  Vector<T> &operator=(Vector<T> &&tmpvec) noexcept;
  Vector<T> &operator=(const std::initializer_list<T> &init);

  template <NumType U> decltype(auto) sum(const Vector<U> &val);
  template <NumType U> decltype(auto) operator+(const Vector<U> &val);
  template <NumType U> decltype(auto) operator+(const U &val);
  Vector<T> operator++(int);

  template <NumType U> decltype(auto) diff(const Vector<U> &val);
  template <NumType U> decltype(auto) operator-(const Vector<U> &val);
  template <NumType U> decltype(auto) operator-(const U &val);
  Vector<T> operator--(int);

  template <NumType U> Vector<T> &operator+=(const U &val);
  template <NumType U> Vector<T> &operator+=(const Vector<U> &val);
  Vector<T> &operator++();

  template <NumType U> Vector<T> &operator-=(const U &val);
  template <NumType U> Vector<T> &operator-=(const Vector<U> &val);
  Vector<T> &operator--();

  template <NumType U> decltype(auto) vecMul(const Vector<U> &val);
  template <NumType U> decltype(auto) operator%(const Vector<U> &val);

  template <NumType U> decltype(auto) div(const U &val);
  template <NumType U> decltype(auto) operator/(const U &val);
  template <NumType U> Vector<T> &operator/=(const U &val);

  template <NumType U> decltype(auto) mul(const U &val);
  template <NumType U> decltype(auto) operator*(const U &val);
  template <NumType U> Vector<T> &operator*=(const U &val);

  template <NumType U> decltype(auto) scalarProduct(const Vector<U> &other);
  template <NumType U> decltype(auto) operator*(const Vector<U> &other);

  T &operator[](const size_t index);
  const T &operator[](const size_t index) const;

#pragma endregion operations

#pragma region iterators
  Iterator<T> begin() noexcept;
  Iterator<T> end() noexcept;
  ConstIterator<T> begin() const noexcept;
  ConstIterator<T> end() const noexcept;
  ConstIterator<T> cbegin() const noexcept;
  ConstIterator<T> cend() const noexcept;
#pragma endregion iterators

protected:
  void alloc(const size_t amount);

  template <NumType U>
  void checkSizeMatch(const Vector<U> &other, const size_t line,
                      const string &funcname) const;
  void checkBounds(const size_t line, const size_t index,
                   const string &funcname) const;
  template <NumType U>
  void checkZeroDivision(const size_t line, U value, const string &funcname);

private:
  std::shared_ptr<T[]> data = nullptr;
};

#include "vector_functions.inl"
#include "vector_iterators.inl"
#include "vector_lifetime.inl"
#include "vector_operators_add.inl"
#include "vector_operators_diff.inl"
#include "vector_operators_div.inl"
#include "vector_operators_logic.inl"
#include "vector_operators_mul.inl"

#endif
