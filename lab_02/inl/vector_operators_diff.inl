#include "vector.hpp"

template <NumType T> //
Vector<T> Vector<T>::neg() const {
  Vector<T> res(*this);

  for (auto el : res)
    *el = -*el;

  return res;
}

template <NumType T> //
Vector<T> Vector<T>::operator-() const {
  return neg();
}

template <NumType T>
template <NumType U> //
decltype(auto) Vector<T>::diff(const Vector<U> &other) {
  checkSizeMatch(other, __LINE__, "diff");

  Vector<decltype((*this)[0] - other[0])> res(size);

  auto this_it = begin();
  auto oth_it = other.begin();

  for (auto &el : res) {
    el = *this_it - *oth_it;
    ++this_it;
    ++oth_it;
  }

  return res;
}

template <NumType T>
template <NumType U> //
decltype(auto) Vector<T>::operator-(const Vector<U> &other) {
  return diff(other);
}

template <NumType T>
template <NumType U> //
decltype(auto) Vector<T>::operator-(const U &val) {
  Vector<decltype((*this)[0] - val)> res(size);

  auto this_it = begin();

  for (auto &el : res) {
    el = *this_it - val;
    ++this_it;
  }

  return res;
}

template <NumType T> //
Vector<T> Vector<T>::operator--(int) {
  Vector<T> res(*this);

  for (auto &el : res)
    --el;

  return res;
}

template <NumType T>
template <NumType U> //
Vector<T> &Vector<T>::operator-=(const U &val) {
  for (auto &el : (*this))
    el -= val;

  return *this;
}

template <NumType T>
template <NumType U> //
Vector<T> &Vector<T>::operator-=(const Vector<U> &other) {
  checkSizeMatch(other, __LINE__, "operator-=");

  auto oth_it = other.begin();
  for (auto &el : (*this)) {
    el -= *oth_it;
    ++oth_it;
  }

  return *this;
}

template <NumType T> //
Vector<T> &Vector<T>::operator--() {
  for (auto &el : (*this))
    --el;

  return *this;
}
