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
    auto oth_it = other.begin();

    for (auto el : (*this)) {
      res = abs((*el) - (*oth_it)) < EPS;
      ++oth_it;
    }
  }

  return res;
}

template <typename T>
template <typename U>
bool Vector<T>::operator!=(const Vector<U> &other) const {
  return !(this == other);
}

template <typename T> Vector<T> &Vector<T>::operator=(const Vector<T> &other) {
  size = other.size;
  alloc(size);

  auto oth_it = other.begin();
  for (auto el : (*this)) {
    *el = *oth_it;
    ++oth_it;
  }

  return *this;
}
