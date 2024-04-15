#include "vector.hpp"

template <typename T>
template <typename U>
decltype(auto) Vector<T>::div(const U &val) {
  Vector<decltype((*this)[0] / val)> res(size);

  for (size_t i = 0; i < size; ++i)
    res[i] = (*this)[i] / val;

  return res;
}

template <typename T>
template <typename U>
decltype(auto) Vector<T>::operator/(const U &val) {
  return div(val);
}

template <typename T>
template <typename U>
Vector<T> &Vector<T>::operator/=(const U &val) {
  for (size_t i = 0; i < size; ++i)
    (*this)[i] /= val;

  return *this;
}
