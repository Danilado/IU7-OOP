#include "vector.hpp"
#include <iostream>

template <NumType T> //
Vector<T>::Vector() noexcept : BaseContainer(), data() {}

template <NumType T> //
Vector<T>::Vector(const Vector<T> &other) : BaseContainer(other.size) {
  alloc(size);

  size_t i = 0;

  for (auto &el : *this) {
    el = other[i];
    ++i;
  }
};

template <NumType T> //
Vector<T>::Vector(Vector<T> &&tmpvec) noexcept : BaseContainer(tmpvec.size) {
  data = tmpvec.data;
  tmpvec.data.reset();
  tmpvec.size = 0;
}

template <NumType T> //
Vector<T>::Vector(const size_t size) : BaseContainer(size) {
  alloc(size);
}

template <NumType T> //
Vector<T>::Vector(const size_t size, const T &fill) : BaseContainer(size) {
  alloc(size);

  for (auto &el : *this)
    el = fill;
}

template <NumType T> //
Vector<T>::Vector(const size_t size, const T *src) : BaseContainer(size) {
  alloc(size);

  size_t i = 0;

  for (auto &el : *this) {
    el = src[i];
    ++i;
  }
}

template <NumType T> //
Vector<T>::Vector(const std::initializer_list<T> &init)
    : BaseContainer(init.size()) {
  alloc(size);

  size_t i = 0;

  for (auto &el : init) {
    (*this)[i] = el;
    ++i;
  }
}

template <NumType T>
template <IterType IterT> //
Vector<T>::Vector(IterT ibeg, IterT iend) {
  size_t size_buf = 0;
  for (auto iter = ibeg; iter < iend; ++iter)
    ++size_buf;

  size = size_buf;
  alloc(size);

  auto it = begin();
  for (auto iter = ibeg; iter < iend; ++iter, ++it)
    *it = *iter;
}

template <NumType T> //
Vector<T>::~Vector() = default;
