#include "vector.hpp"

template <typename T>
template <typename U>
decltype(auto) Vector<T>::vecMul(const Vector<U> &other) {
  checkSizeMatch(other, __LINE__);

  Vector<decltype((*this)[0] * other[0])> res(size);

  size_t i = 0;
  for (auto &el : res) {
    *el = (*this)[(i + 1) % size] * other[(i + 2) % size] -
          (*this)[(i + 2) % size] * other[(i + 1) % size];
    ++i;
  }

  return res;
}

template <typename T>
template <typename U>
decltype(auto) Vector<T>::operator%(const Vector<U> &other) {
  return vecMul(other);
}

template <typename T>
template <typename U>
decltype(auto) Vector<T>::mul(const U &val) {
  Vector<decltype((*this)[0] * val)> res(size);

  auto &this_it = begin();
  for (auto &el : res) {
    *el = (*this_it) * val;
    ++this_it;
  }

  return res;
}

template <typename T>
template <typename U>
decltype(auto) Vector<T>::operator*(const U &val) {
  return mul(val);
}

template <typename T>
template <typename U>
Vector<T> &Vector<T>::operator*=(const U &val) {
  for (auto &el : this)
    (*el) *= val;

  return *this;
}

template <typename T>
template <typename U>
decltype(auto) Vector<T>::scalarProduct(const Vector<U> &other) {
  checkSizeMatch(other, __LINE__);

  decltype((*this)[0] * other[0]) res = 0;

  auto &oth_it = other.begin();
  for (auto &el : this) {
    res += (*el) * (*oth_it);
    ++oth_it;
  }

  return res;
}

template <typename T>
template <typename U>
decltype(auto) Vector<T>::operator*(const Vector<U> &other) {
  return scalarProduct(other);
}
