#include "exceptions.hpp"
#include "iterator.hpp"

template <typename T> T *Iterator<T>::getPtr() const {
  std::shared_ptr<T[]> res = ptr.lock();
  return res.get() + index;
}

template <typename T>
void Iterator<T>::checkExpired(const size_t line, string funcname) const {
  if (ptr.expired())
    throw PointerExpiredException(__FILE__, line, typeid(*this).name(),
                                  funcname);
}

template <typename T>
void Iterator<T>::checkBounds(const size_t line, string funcname,
                              const size_t offset) const {
  if (index + offset >= size)
    throw IndexOutOfBoundsException(__FILE__, line, typeid(*this).name(),
                                    funcname);
}
