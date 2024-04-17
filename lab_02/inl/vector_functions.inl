#include "exceptions.hpp"
#include "vector.hpp"
#include <cmath>

#ifndef EPS
#define EPS 1e-6
#endif

template <typename T> void Vector<T>::alloc(size_t amount) {
  try {
    data.reset(new T[amount]);
  } catch (std::bad_alloc &error) {
    throw MemoryException(__FILE__, __LINE__, typeid(*this).name, __FUNCTION__);
  }
}

template <typename T>
template <typename U>
void Vector<T>::checkSizeMatch(const Vector<U> &other, const size_t line) {
  if (size != other.size)
    throw SizeMismatchException(__FILE__, line, typeid(*this).name,
                                __FUNCTION__, size, other.size);
}

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
