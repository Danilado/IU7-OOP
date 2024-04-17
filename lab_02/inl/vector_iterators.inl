#include "iterator.hpp"
#include "vector.hpp"

template <typename T> Iterator<T> Vector<T>::begin() noexcept {
  return Iterator<T>(*this);
}

template <typename T> Iterator<T> Vector<T>::end() noexcept {
  return Iterator<T>(*this) + size;
}
