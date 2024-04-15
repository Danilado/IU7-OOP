#include "exceptions.hpp"
#include "iterator.hpp"

#pragma region lifetime

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

#pragma endregion lifetime

#pragma region operators

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

#pragma endregion operators

#pragma region functions

template <typename T> T *Iterator<T>::getPtr() const {
  std::shared_ptr<T> res = ptr.lock();
  return res.get() + index;
}

template <typename T> void Iterator<T>::checkExpired(const size_t line) {
  if (ptr.expired())
    throw PointerExpiredException(__FILE__, line, typeid(*this).name,
                                  __FUNCTION__);
}

template <typename T>
void Iterator<T>::checkBounds(const size_t line, const size_t offset) {
  if (index + offset >= size)
    throw IndexOutOfBoundsException(__FILE__, line, typeid(*this).name,
                                    __FUNCTION__);
}

#pragma endregion functions
