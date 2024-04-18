#include "exceptions.hpp"
#include "iterator.hpp"

template <typename T>
auto Iterator<T>::operator<=>(const Iterator<T> &other) const {
  return this->index <=> other.index;
}

template <typename T>
bool Iterator<T>::operator==(const Iterator<T> &other) const {
  return this->index == other.index;
}

template <typename T>
bool Iterator<T>::operator!=(const Iterator<T> &other) const {
  return !(*this == other);
}

template <typename T> Iterator<T>::operator bool() const {
  checkExpired(__LINE__, "bool()");
  return index < size;
}

template <typename T> T &Iterator<T>::operator*() {
  checkExpired(__LINE__, "operator*");
  checkBounds(__LINE__, "operator*");

  return *getPtr();
}

template <typename T> T *Iterator<T>::operator->() {
  checkExpired(__LINE__, "operator->");
  checkBounds(__LINE__, "operator->");

  return getPtr();
}

template <typename T> T &Iterator<T>::operator[](const size_t offset) {
  checkExpired(__LINE__, "operator[]");
  checkBounds(__LINE__, index, "operator[]");

  return *(getPtr() + index);
}

template <typename T> Iterator<T> &Iterator<T>::operator++() {
  checkExpired(__LINE__, "operator++");

  ++index;
  return *this;
}
template <typename T> Iterator<T> Iterator<T>::operator++(int) {
  checkExpired(__LINE__, "operator++");

  Iterator<T> res(*this);
  ++index;
  return res;
}

template <typename T> Iterator<T> &Iterator<T>::operator--() {
  checkExpired(__LINE__, "operator--");

  --index;
  return *this;
}
template <typename T> Iterator<T> Iterator<T>::operator--(int) {
  checkExpired(__LINE__, "operator--");

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
