#include "exceptions.hpp"
#include "vector.hpp"

template <typename T> void Vector<T>::alloc(size_t amount);

template <typename T>
template <typename U>
void Vector<T>::checkSizeMatch(const Vector<U> &other, const size_t line) {
  if (size != other.size)
    throw SizeMismatchException(__FILE__, line, typeid(*this).name,
                                __FUNCTION__, size, other.size);
}
