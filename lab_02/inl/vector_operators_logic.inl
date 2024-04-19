#include "vector.hpp"

template <NumType T> //
Vector<T>::operator bool() const {
  return !isZero();
}

template <NumType T>
template <NumType U> //
auto Vector<T>::operator<=>(const Vector<U> &other) const {
  auto res = size <=> other.size;
  if (res == std::strong_ordering::equal)
    res = length() <=> other.length();

  return res;
}

template <NumType T>
template <NumType U> //
bool Vector<T>::operator==(const Vector<U> &other) const {
  bool res = true;

  if (size != other.size) {
    res = false;
  } else {
    auto oth_it = other.begin();

    for (const auto &el : (*this)) {
      if (!res)
        break;

      res = fabs(el - (*oth_it)) < EPS;
      ++oth_it;
    }
  }

  return res;
}

template <NumType T>
template <NumType U> //
bool Vector<T>::operator!=(const Vector<U> &other) const {
  return !(*this == other);
}
