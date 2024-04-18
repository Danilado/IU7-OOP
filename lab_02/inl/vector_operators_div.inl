#include "vector.hpp"

template <typename T>
template <typename U>
decltype(auto) Vector<T>::div(const U &val) {
  Vector<decltype((*this)[0] / val)> res(size);

  auto this_it = begin();

  for (auto &el : res) {
    el = *this_it / val;
    ++this_it;
  }

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
  for (auto &el : (*this))
    el /= val;

  return *this;
}
