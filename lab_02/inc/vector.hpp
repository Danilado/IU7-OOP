#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <compare>
#include <cstdlib>
#include <memory>

#include "base_container.hpp"
#include "iterator.hpp"

template <typename T>
concept IterType = requires(T a) {
  { a.begin() };
  { a.end() };
  { *a };
};

template <typename T> class Vector : public BaseContainer {

  friend Iterator<T>;

public:
#pragma region lifetime
  Vector() noexcept;
  explicit Vector(const Vector<T> &vec);
  Vector(Vector<T> &&tmpvec) noexcept;

  explicit Vector(const size_t size);
  Vector(const size_t size, const T &fill);
  Vector(const size_t size, const T *src);

  Vector(std::initializer_list<T> init);
  template <IterType IterT> Vector(IterT ibeg, IterT iend);

  ~Vector();
#pragma endregion lifetime

#pragma region operations

  operator bool() const;
  Vector<T> neg() const;
  Vector<T> operator-() const;

  template <typename U> U length() const;
  template <typename U> Vector<U> getUnit() const;

  bool isZero() const;
  bool isUnit() const;

  template <typename U> auto operator<=>(const Vector<U> &other) const;
  template <typename U> bool operator==(const Vector<U> &other) const;
  template <typename U> bool operator!=(const Vector<U> &other) const;

  Vector<T> &operator=(const Vector<T> &vec);
  Vector<T> &operator=(Vector<T> &&tmpvec) noexcept;
  Vector<T> &operator=(std::initializer_list<T> init);

  template <typename U> decltype(auto) sum(const Vector<U> &val);
  template <typename U> decltype(auto) operator+(const Vector<U> &val);
  template <typename U> decltype(auto) operator+(const U &val);
  Vector<T> operator++(int);

  template <typename U> Vector<T> diff(const Vector<U> &val);
  template <typename U> Vector<T> operator-(const Vector<U> &val);
  template <typename U> Vector<T> operator-(const U &val);
  Vector<T> operator--(int);

  template <typename U> Vector<T> &operator+=(const U &val);
  template <typename U> Vector<T> &operator+=(const Vector<U> &val);
  Vector<T> &operator++();

  template <typename U> Vector<T> &operator-=(const U &val);
  template <typename U> Vector<T> &operator-=(const Vector<U> &val);
  Vector<T> &operator--();

  template <typename U> decltype(auto) mul(const Vector<U> &val);
  template <typename U> decltype(auto) operator%(const Vector<U> &val);

  template <typename U> decltype(auto) div(const U &val);
  template <typename U> decltype(auto) operator/(const U &val);
  template <typename U> Vector<T> &operator/=(const U &val);

  template <typename U> decltype(auto) operator*(const U &val);
  template <typename U> Vector<T> &operator*=(const U &val);
  template <typename U> Vector<T> &operator*=(const Vector<U> &val);

  T scalarProduct(const Vector<T> &val);
  template <typename U> decltype(auto) scalarProduct(const Vector<U> &val);
  T operator^(const Vector<T> &val);
  template <typename U> decltype(auto) operator*(const Vector<U> &val);

#pragma endregion operations

#pragma region iterators
#pragma endregion iterators

#pragma region functions
#pragma endregion functions
protected:
  void alloc(size_t amount);

  template <typename U>
  void checkSizeMatch(const Vector<U> &other, const size_t line);

private:
  std::shared_ptr<T> data = nullptr;
};

#include "vector_lifetime.inl"
#include "vector_operators.inl"

#endif
