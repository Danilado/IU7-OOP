#include "vector.hpp"

template <typename T>
template <typename U>
decltype(auto) Vector<T>::mul(const Vector<U> &val) {
  checkSizeMatch(val, __LINE__);

  Vector<decltype((*this)[0] * val[0])> res(size);

  for (size_t i = 0; i < size; ++i)
    res[i] = (*this)[(i + 1) % size] * val[(i + 2) % size] -
             (*this)[(i + 2) % size] * val[(i + 1) % size];

  return res;
}

template <typename T>
template <typename U>
decltype(auto) Vector<T>::operator%(const Vector<U> &val) {
  return mul(val);
}

template <typename T>
template <typename U>
decltype(auto) Vector<T>::operator*(const U &val) {
  Vector<decltype((*this)[0] * val)> res(size);

  for (size_t i = 0; i < size; ++i)
    res[i] = (*this)[i] * val;

  return res;
}

template <typename T>
template <typename U>
Vector<T> &Vector<T>::operator*=(const U &val) {
  for (size_t i = 0; i < size; ++i)
    (*this)[i] *= val;

  return *this;
}

template <typename T>
template <typename U>
Vector<T> &Vector<T>::operator*=(const Vector<U> &val) {
  for (size_t i = 0; i < size; ++i)
    (*this)[i] *= val;

  return *this;
}

template <typename T> T Vector<T>::scalarProduct(const Vector<T> &val) {
  checkSizeMatch(val, __LINE__);

  T res = 0;
  for (size_t i = 0; i < size; ++i)
    res += (*this)[i] * val[i];

  return res;
}

template <typename T>
template <typename U>
decltype(auto) Vector<T>::scalarProduct(const Vector<U> &val) {
  checkSizeMatch(val, __LINE__);

  decltype((*this)[0] * val[0]) res = 0;
  for (size_t i = 0; i < size; ++i)
    res += (*this)[i] * val[i];

  return res;
}
