#ifndef LAB2_AVLTREE_ITERATOR_H
#define LAB2_AVLTREE_ITERATOR_H

#include "AVLNode.hpp"
#include "proxy.hpp"
#include <iterator>
#include <memory>

template <TreeType T> class AVLTree;

template <TreeType T> class AVLTreeIterator {
public:
  using iterator_category = std::bidirectional_iterator_tag;
  using value_type = T;
  using difference_type = std::ptrdiff_t;
  using size_type = size_t;
  using reference = const value_type &;
  using pointer = const value_type *;
  using iterator = AVLTreeIterator<T>;

  AVLTreeIterator() noexcept = default;

  AVLTreeIterator(const AVLTreeIterator<T> &other) noexcept = default;

  explicit AVLTreeIterator(const AVLTree<T> &tree) noexcept;

  explicit AVLTreeIterator(AVLTree<T> &tree) noexcept;

  AVLTreeIterator(AVLTree<T> &&tree) noexcept;

  explicit AVLTreeIterator(const NodePtr<T> &node_ptr) noexcept;

  reference operator*() const;

  pointer operator->() const;

  explicit operator bool() const;

  bool operator==(const iterator &other) const;

  bool operator!=(const iterator &other) const;

  iterator &operator++();

  iterator operator++(int);

  iterator &operator--();

  iterator operator--(int);

  iterator &operator+=(size_type value);

  iterator &operator-=(size_type value);

  ~AVLTreeIterator() = default;

  AVLTreeIterator &operator=(const AVLTreeIterator<T> &other) = default;

  AVLTreeIterator &operator=(AVLTreeIterator<T> &&other) noexcept = default;

private:
  std::weak_ptr<Node<T>> current_node;
};

#include "AVLIterator.inl"

static_assert(std::bidirectional_iterator<AVLTreeIterator<int>>);

#endif // LAB2_AVLTREE_ITERATOR_H
