#include "exceptions.hpp"
#include "iterator.hpp"

template <typename T>
auto Iterator<T>::operator<=>(const Iterator<T> &other) const {
  return this->index <=> other.index;
}

template <typename T> Iterator<T>::operator bool() const {
  checkExpired(__LINE__);
  return index < size;
}

template <typename T> T &Iterator<T>::operator*() {
  checkExpired(__LINE__);
  checkBounds(__LINE__);

  return *getPtr();
}
template <typename T> const T &Iterator<T>::operator*() const {
  checkExpired(__LINE__);
  checkBounds(__LINE__);

  return *getPtr();
}

template <typename T> T *Iterator<T>::operator->() {
  checkExpired(__LINE__);
  checkBounds(__LINE__);

  return getPtr();
}
template <typename T> const T *Iterator<T>::operator->() const {
  checkExpired(__LINE__);
  checkBounds(__LINE__);

  return getPtr();
}

template <typename T> T &Iterator<T>::operator[](const size_t offset) {
  checkExpired(__LINE__);
  checkBounds(__LINE__, index);

  return *(getPtr() + index);
}
template <typename T>
const T &Iterator<T>::operator[](const size_t offset) const {
  checkExpired(__LINE__);
  checkBounds(__LINE__, index);

  return *(getPtr() + index);
}

template <typename T> Iterator<T> &Iterator<T>::operator++() {
  checkExpired(__LINE__);

  ++index;
  return *this;
}
template <typename T> Iterator<T> Iterator<T>::operator++(int) {
  checkExpired(__LINE__);

  Iterator<T> res(*this);
  ++index;
  return res;
}

template <typename T> Iterator<T> &Iterator<T>::operator--() {
  checkExpired(__LINE__);

  --index;
  return *this;
}
template <typename T> Iterator<T> Iterator<T>::operator--(int) {
  checkExpired(__LINE__);

  Iterator<T> res(*this);
  --index;
  return res;
}

template <typename T>
template <typename U>
Iterator<T> Iterator<T>::operator+(const U val) const {
  Iterator<T> res(*this);
  res.index += val;
  return res;
}

template <typename T>
template <typename U>
Iterator<T> Iterator<T>::operator-(const U val) const {
  Iterator<T> res(*this);
  res.index -= val;
  return res;
}

template <typename T>
template <typename U>
Iterator<T> &Iterator<T>::operator+=(const U val) {
  index += val;
  return *this;
}

template <typename T>
template <typename U>
Iterator<T> &Iterator<T>::operator-=(const U val) {
  index -= val;
  return *this;
}
