#include "vector.hpp"

template <typename T> Vector<T> Vector<T>::neg() const {
  Vector<T> res(*this);

  for (auto &el : res)
    *el = -*el;

  return res;
}

template <typename T> Vector<T> Vector<T>::operator-() const { return neg(); }

template <typename T>
template <typename U>
Vector<T> Vector<T>::diff(const Vector<U> &other) {
  checkSizeMatch(other, __LINE__);

  Vector<decltype((*this)[0] - other[0])> res(size);

  auto &this_it = begin();
  auto &oth_it = other.begin();

  for (auto &el : res) {
    *el = *this_it - *oth_it;
    ++this_it;
    ++oth_it;
  }

  return res;
}

template <typename T>
template <typename U>
Vector<T> Vector<T>::operator-(const Vector<U> &other) {
  return diff(other);
}

template <typename T>
template <typename U>
Vector<T> Vector<T>::operator-(const U &val) {
  Vector<decltype((*this)[0] - val)> res(size);

  auto &this_it = begin();
  for (auto &el : res) {
    *el = *this_it - val;
    ++this_it;
  }

  return res;
}

template <typename T> Vector<T> Vector<T>::operator--(int) {
  Vector<T> res(*this);

  for (auto &el : res)
    --(*el);

  return res;
}

template <typename T>
template <typename U>
Vector<T> &Vector<T>::operator-=(const U &val) {
  for (auto &el : this)
    (*el) -= val;

  return *this;
}

template <typename T>
template <typename U>
Vector<T> &Vector<T>::operator-=(const Vector<U> &other) {
  checkSizeMatch(other, __LINE__);

  auto &oth_it = other.begin();
  for (auto &el : this) {
    (*el) -= *oth_it;
    ++oth_it;
  }

  return *this;
}

template <typename T> Vector<T> &Vector<T>::operator--() {
  for (auto &el : this)
    --(*el);

  return *this;
}
