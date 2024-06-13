#ifndef LAB2_AVLTREE_NODE_H
#define LAB2_AVLTREE_NODE_H

#include "BaseTree.hpp"
#include "traits.hpp"
#include <memory>

template <TreeType T> class AVLTreeIterator;

template <TreeType T> class AVLTree;

template <TreeType T> class Node {
  friend class AVLTreeIterator<T>;

  friend class AVLTree<T>;

public:
  explicit Node() = default;

  explicit Node(T value) : key(value) {}

  void deleteNode() {
    if (left_)
      left_->deleteNode();
    if (right_)
      right_->deleteNode();
    left_.reset();
    right_.reset();
  }

  const T &data() { return key; }

  const std::shared_ptr<Node<T>> &right() { return right_; }

  const std::shared_ptr<Node<T>> &left() { return left_; }

  const std::weak_ptr<Node<T>> &parent() { return parent_; }

private:
  T key;
  std::weak_ptr<Node<T>> parent_;
  std::shared_ptr<Node<T>> left_ = nullptr;
  std::shared_ptr<Node<T>> right_ = nullptr;
  size_t height = 0;
};

template <TreeType T> using NodePtr = std::shared_ptr<Node<T>>;

#endif // LAB2_AVLTREE_NODE_H
