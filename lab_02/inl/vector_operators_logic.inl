#include "vector.hpp"

template <typename T> Vector<T>::operator bool() const { return !isZero(); }

template <typename T>
template <typename U>
auto Vector<T>::operator<=>(const Vector<U> &other) const {
  auto res = size <=> other.size;
  if (res == std::strong_ordering::equal)
    res = length() <=> other.length();

  return res;
}

template <typename T>
template <typename U>
bool Vector<T>::operator==(const Vector<U> &other) const {
  bool res = true;

  if (size != other.size) {
    res = false;
  } else {
    for (size_t i = 0; res && (i < size); ++i)
      res = abs((*this)[i] - other[i]) < EPS;
  }

  return res;
}

template <typename T>
template <typename U>
bool Vector<T>::operator!=(const Vector<U> &other) const {
  return !(this == other);
}

template <typename T> Vector<T> &Vector<T>::operator=(const Vector<T> &vec) {
  size = vec.size;
  alloc(size);

  size_t i = 0;
  for (auto &el : vec) {
    (*this)[i] = el;
    ++i;
  }

  return *this;
}
