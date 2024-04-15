#include "vector.hpp"

template <typename T> Vector<T>::Vector() noexcept : BaseContainer(), data() {}

template <typename T>
Vector<T>::Vector(const Vector<T> &vec) : BaseContainer(vec.size) {
  alloc(size);

  for (size_t i = 0; i < size; ++i)
    (*this)[i] = vec[i];
};

template <typename T>
Vector<T>::Vector(Vector<T> &&tmpvec) noexcept : BaseContainer(tmpvec.size) {
  data = tmpvec.data;
  tmpvec.data.reset();
}

template <typename T>
Vector<T>::Vector(const size_t size) : BaseContainer(size) {
  alloc(size);
}

template <typename T>
Vector<T>::Vector(const size_t size, const T &fill) : BaseContainer(size) {
  alloc(size);

  for (size_t i = 0; i < size; ++i)
    (*this)[i] = fill;
}

template <typename T>
Vector<T>::Vector(const size_t size, const T *src) : BaseContainer(size) {
  alloc(size);

  for (size_t i = 0; i < size; ++i)
    (*this)[i] = src[i];
}

template <typename T>
Vector<T>::Vector(std::initializer_list<T> init) : BaseContainer(init.size()) {
  alloc(size);

  size_t i = 0;
  for (auto &el : init) {
    (*this)[i] = el;
    ++i;
  }
}

template <typename T>
template <IterType IterT>
Vector<T>::Vector(IterT ibeg, IterT iend) {
  size_t size_buf = 0;
  for (auto iter = ibeg; iter < iend; ++iter)
    ++size_buf;
  size = size_buf;

  alloc(size);

  size_t i = 0;
  for (auto iter = ibeg; iter < iend; ++iter, ++i)
    data[i] = *iter;
}

template <typename T> Vector<T>::~Vector() = default;
