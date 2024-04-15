#include "vector.hpp"
#include <cmath>

#ifndef EPS
#define EPS 1e-6
#endif

#include "vector_operators_add.inl"
#include "vector_operators_diff.inl"
#include "vector_operators_div.inl"
#include "vector_operators_logic.inl"
#include "vector_operators_mul.inl"

template <typename T> template <typename U> U Vector<T>::length() const {
  if (!size)
    return 0;

  T len = 0;
  for (size_t i = 0; i < size; ++i)
    len += (*this)[i] * (*this)[i];

  return sqrt(len);
};

template <typename T>
template <typename U>
Vector<U> Vector<T>::getUnit() const {
  Vector<U> res(*this);
  U len = length<U>();

  for (size_t i = 0; i < size; ++i)
    res[i] = res[i] / len;

  return res;
}

template <typename T> bool Vector<T>::isZero() const {
  return !size || length<double>() < EPS;
}

template <typename T> bool Vector<T>::isUnit() const {
  return (length<double>() - 1) < EPS;
}

template <typename T>
Vector<T> &Vector<T>::operator=(Vector<T> &&tmpvec) noexcept {
  size = tmpvec.size;
  data.reset(tmpvec.data);
  tmpvec.data.reset();
}

template <typename T>
Vector<T> &Vector<T>::operator=(std::initializer_list<T> init) {
  size = init.size();
  alloc(size);

  size_t i = 0;
  for (auto &el : init) {
    (*this)[i] = el;
    ++i;
  }
}
