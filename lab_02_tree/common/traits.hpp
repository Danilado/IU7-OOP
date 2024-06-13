#ifndef _BASE_CONCEPT_H_
#define _BASE_CONCEPT_H_

#include <concepts>

using namespace std;

template <typename T>
concept TreeType = requires(T a, T b) {
  { std::default_initializable<T> };
  { std::copyable<T> };
  { a <=> b };
  { a == b } -> same_as<bool>;
  { a != b } -> same_as<bool>;
};

template <typename T, typename R>
concept common_with_TreeType =
    std::common_with<T, R> && TreeType<std::common_type_t<T, R>>;

template <typename R, typename T>
concept ConvertibleTo = convertible_to<R, T>;

template <typename R, typename T>
concept Constructible = constructible_from<T, R>;

template <typename T>
concept TreeIterator = requires(T &u) {
  { u.begin() } -> std::forward_iterator;
  { u.end() } -> std::sentinel_for<decltype(u.begin())>;
  std::constructible_from<
      T, typename std::iterator_traits<decltype(u.begin())>::reference>;
};

template <typename T, typename U>
concept TreeContainer = requires(U &u) { TreeIterator<U>; };

#endif // _BASE_CONCEPT_H_
