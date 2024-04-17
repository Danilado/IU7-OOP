#include "exceptions.hpp"
#include "iterator.hpp"

template <typename T>
Iterator<T>::Iterator(const Vector<T> &vec) noexcept : BaseIterator() {
  ptr = vec.data;
  size = vec.size;
}

template <typename T>
Iterator<T>::Iterator(const Iterator<T> &iter) noexcept : BaseIterator(iter) {
  ptr = iter.ptr;
}

template <typename T> Iterator<T>::~Iterator() = default;
