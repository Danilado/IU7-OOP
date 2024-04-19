#include "const_iterator.hpp"
#include "iterator.hpp"
#include "vector.hpp"

template <NumType T> //
Iterator<T> Vector<T>::begin() noexcept {
  return Iterator<T>(*this);
}

template <NumType T> //
Iterator<T> Vector<T>::end() noexcept {
  return Iterator<T>(*this) + size;
}

template <NumType T> //
ConstIterator<T> Vector<T>::begin() const noexcept {
  return ConstIterator<T>(*this);
}

template <NumType T> //
ConstIterator<T> Vector<T>::end() const noexcept {
  return ConstIterator<T>(*this) + size;
}

template <NumType T> //
ConstIterator<T> Vector<T>::cbegin() const noexcept {
  return ConstIterator<T>(*this);
}

template <NumType T> //
ConstIterator<T> Vector<T>::cend() const noexcept {
  return ConstIterator<T>(*this) + size;
}
