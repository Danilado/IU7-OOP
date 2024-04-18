#include "exceptions.hpp"
#include "vector.hpp"
#include <cmath>

#ifndef EPS
#define EPS 1e-6
#endif

template <typename T> void Vector<T>::alloc(const size_t amount) {
  try {
    data.reset();
    data = std::make_shared<T[]>(amount);
  } catch (std::bad_alloc &error) {
    throw MemoryException(__FILE__, __LINE__, typeid(*this).name(), "alloc");
  }
}

template <typename T>
template <typename U>
void Vector<T>::checkSizeMatch(const Vector<U> &other, const size_t line,
                               string funcname) const {
  if (size != other.getSize())
    throw SizeMismatchException(__FILE__, line, typeid(*this).name(), funcname,
                                size, other.getSize());
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
  data = tmpvec.data;
  tmpvec.data.reset();
  tmpvec.size = 0;

  return *this;
}

template <typename T> Vector<T> &Vector<T>::operator=(const Vector<T> &vec) {
  size = vec.size;
  alloc(size);

  auto oth_it = vec.begin();

  for (auto &el : *this) {
    el = *oth_it;
    ++oth_it;
  }

  return *this;
}

template <typename T>
Vector<T> &Vector<T>::operator=(std::initializer_list<T> init) {
  size = init.size();
  alloc(size);

  size_t i = 0;
  for (auto el : init) {
    (*this)[i] = el;
    ++i;
  }

  return *this;
}

template <typename T> T &Vector<T>::operator[](const size_t index) {
  checkBounds(__LINE__, index, "operator[]");

  return data[index];
}

template <typename T> const T &Vector<T>::operator[](const size_t index) const {
  checkBounds(__LINE__, index, "operator[]");

  return data[index];
}

template <typename T>
void Vector<T>::checkBounds(const size_t line, const size_t index,
                            string funcname) const {
  if (index >= size)
    throw IndexOutOfBoundsException(__FILE__, line, typeid(*this).name(),
                                    funcname);
}

template <typename T>
template <typename U>
void Vector<T>::checkZeroDivision(const size_t line, U value, string funcname) {
  if (fabs(value) < EPS)
    throw ZeroDivisionException(__FILE__, line, typeid(*this).name(), funcname);
}
