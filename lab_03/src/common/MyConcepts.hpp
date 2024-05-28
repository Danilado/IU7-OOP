#ifndef MY_CONCEPTS_HPP
#define MY_CONCEPTS_HPP

#include <concepts>

template <typename T>
concept NotAbstractClass = std::is_class_v<T> && !std::is_abstract_v<T>;

template <typename T>
concept CopyConstructible = requires(T t) { T(t); };

template <typename T>
concept Assignable = requires(T t1, T t2) { t1 = t2; };

template <typename T>
concept OnlyObject =
    NotAbstractClass<T> && !CopyConstructible<T> && !Assignable<T>;

#endif
