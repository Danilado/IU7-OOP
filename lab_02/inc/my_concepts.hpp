#ifndef MY_CONCEPTS_HPP
#define MY_CONCEPTS_HPP

#include <concepts>

template <typename T>
concept NumType = std::is_signed<T>::value || std::is_integral<T>::value ||
                  std::is_floating_point<T>::value ||
                  std::is_unsigned<T>::value || std::is_arithmetic<T>::value;

template <typename T>
concept IterType = requires(T a) {
  { a-- };
  { --a };
  { a++ };
  { ++a };
  { *a };
};

#endif