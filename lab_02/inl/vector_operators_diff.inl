#include "vector.hpp"

template <typename T> Vector<T> Vector<T>::neg() const {
  Vector<T> res(*this);

  for (size_t i = 0; i < size; ++i)
    res[i] = -res[i];

  return res;
}

template <typename T> Vector<T> Vector<T>::operator-() const { return neg(); }

template <typename T>
template <typename U>
Vector<T> Vector<T>::diff(const Vector<U> &val) {
  checkSizeMatch(val, __LINE__);

  Vector<decltype((*this)[0] - val[0])> res(size);

  for (size_t i = 0; i < size; ++i)
    res[i] = (*this)[i] - val[i];

  return res;
}

template <typename T>
template <typename U>
Vector<T> Vector<T>::operator-(const Vector<U> &val) {
  return diff(val);
}

template <typename T>
template <typename U>
Vector<T> Vector<T>::operator-(const U &val) {
  Vector<decltype((*this)[0] - val)> res(size);

  for (size_t i = 0; i < size; ++i)
    res[i] = (*this)[i] - val;

  return res;
}

template <typename T> Vector<T> Vector<T>::operator--(int) {
  Vector<T> res(*this);

  for (size_t i = 0; i < size; ++i)
    --(*this)[i];

  return res;
}

template <typename T>
template <typename U>
Vector<T> &Vector<T>::operator-=(const U &val) {
  for (size_t i = 0; i < size; ++i)
    (*this)[i] -= val;
  return *this;
}

template <typename T>
template <typename U>
Vector<T> &Vector<T>::operator-=(const Vector<U> &val) {
  checkSizeMatch(val, __LINE__);

  for (size_t i = 0; i < size; ++i)
    (*this)[i] -= val[i];
  return *this;
}

template <typename T> Vector<T> &Vector<T>::operator--() {
  for (size_t i = 0; i < size; ++i)
    --(*this)[0];
  return *this;
}
