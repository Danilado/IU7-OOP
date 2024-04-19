#include "vector.hpp"

template <NumType T>
template <NumType U> //
decltype(auto) Vector<T>::div(const U &val) {
  checkZeroDivision(__LINE__, val, "div");

  Vector<decltype((*this)[0] / val)> res(size);

  auto this_it = begin();

  for (auto &el : res) {
    el = *this_it / val;
    ++this_it;
  }

  return res;
}

template <NumType T>
template <NumType U> //
decltype(auto) Vector<T>::operator/(const U &val) {
  return div(val);
}

template <NumType T>
template <NumType U> //
Vector<T> &Vector<T>::operator/=(const U &val) {
  checkZeroDivision(__LINE__, val, "operator/=");

  for (auto &el : (*this))
    el /= val;

  return *this;
}
