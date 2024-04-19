#include "const_iterator.hpp"
#include "exceptions.hpp"

template <typename T> //
T *ConstIterator<T>::getPtr() const {
  std::shared_ptr<T[]> res = ptr.lock();
  return res.get() + index;
}

template <typename T> //
void ConstIterator<T>::checkExpired(const size_t line,
                                    const string &funcname) const {
  if (ptr.expired())
    throw PointerExpiredException(__FILE__, line, typeid(*this).name(),
                                  funcname);
}

template <typename T> //
void ConstIterator<T>::checkBounds(const size_t line, const string &funcname,
                                   const size_t offset) const {
  if (index + offset >= size)
    throw IndexOutOfBoundsException(__FILE__, line, typeid(*this).name(),
                                    funcname);
}

template <typename T> //
ConstIterator<T>::ConstIterator(const Vector<T> &vec) noexcept
    : BaseIterator() {
  ptr = vec.data;
  size = vec.size;
}

template <typename T> //
ConstIterator<T>::ConstIterator(const ConstIterator<T> &iter) noexcept
    : BaseIterator(iter) {
  ptr = iter.ptr;
}

template <typename T> //
ConstIterator<T>::~ConstIterator() = default;

template <typename T> //
auto ConstIterator<T>::operator<=>(const ConstIterator<T> &other) const {
  return this->index <=> other.index;
}

template <typename T> //
ConstIterator<T>::operator bool() const noexcept {
  return index < size && !ptr.expired();
}

template <typename T> //
const T &ConstIterator<T>::operator*() const {
  checkExpired(__LINE__, "operator*");
  checkBounds(__LINE__, "operator*");

  return *getPtr();
}

template <typename T> //
const T *ConstIterator<T>::operator->() const {
  checkExpired(__LINE__, "operator->");
  checkBounds(__LINE__, "operator->");

  return getPtr();
}

template <typename T> //
const T &ConstIterator<T>::operator[](const size_t offset) const {
  checkExpired(__LINE__, "operator[]");
  checkBounds(__LINE__, index, "operator[]");

  return *(getPtr() + index);
}

template <typename T> //
ConstIterator<T> &ConstIterator<T>::operator++() {
  checkExpired(__LINE__, "operator++");

  ++index;
  return *this;
}

template <typename T> //
ConstIterator<T> ConstIterator<T>::operator++(int) {
  checkExpired(__LINE__, "operator++");

  ConstIterator<T> res(*this);
  ++index;
  return res;
}

template <typename T> //
ConstIterator<T> &ConstIterator<T>::operator--() {
  checkExpired(__LINE__, "operator--");

  --index;
  return *this;
}

template <typename T> //
ConstIterator<T> ConstIterator<T>::operator--(int) {
  checkExpired(__LINE__, "operator--");

  ConstIterator<T> res(*this);
  --index;
  return res;
}

template <typename T>
template <typename U> //
ConstIterator<T> ConstIterator<T>::operator+(const U val) const {
  ConstIterator<T> res(*this);
  res.index += val;
  return res;
}

template <typename T>
template <typename U> //
ConstIterator<T> ConstIterator<T>::operator-(const U val) const {
  ConstIterator<T> res(*this);
  res.index -= val;
  return res;
}

template <typename T>
template <typename U> //
ConstIterator<T> &ConstIterator<T>::operator+=(const U val) {
  index += val;
  return *this;
}

template <typename T>
template <typename U> //
ConstIterator<T> &ConstIterator<T>::operator-=(const U val) {
  index -= val;
  return *this;
}
