#ifndef LAB2_AVLTREE_H
#define LAB2_AVLTREE_H

#include "AVLIterator.hpp"
#include "AVLNode.hpp"
#include "traits.hpp"
#include <memory>

#include "BaseTree.h"
#include <initializer_list>

template <TreeType T> class AVLTree : public BaseTree {
public:
  using value_type = T;
  using size_type = size_t;
  using const_iterator = AVLTreeIterator<T>;

  AVLTree();

  template <ConvertibleTo<T> R> AVLTree(std::initializer_list<R> init_list);
  AVLTree(std::initializer_list<T> init_list);

  AVLTree(AVLTree<T> &&tree) noexcept;

  template <ConvertibleTo<T> R> explicit AVLTree(const AVLTree<R> &tree);
  explicit AVLTree(const AVLTree<T> &tree);

  template <ConvertibleTo<T> R> AVLTree(const R *arr, size_t size);
  AVLTree(const T *arr, size_t size);

  template <TreeContainer<T> Container> explicit AVLTree(const Container &tree);

  template <ConvertibleTo<T> R, TreeContainer<T> Container>
  explicit AVLTree(const Container &tree)
    requires requires(typename Container::value_type elem) {
      { elem } -> convertible_to<T>;
    };

  template <std::input_iterator Iter, std::sentinel_for<Iter> Iter_e>
    requires std::convertible_to<T, typename Iter::value_type>
  AVLTree(Iter begin, Iter_e end);

  explicit AVLTree(TreeIterator auto range);

  template <ConvertibleTo<T> R>
  AVLTree<T> &operator=(std::initializer_list<R> init_list);
  AVLTree<T> &operator=(std::initializer_list<T> init_list);

  template <ConvertibleTo<T> R> AVLTree<T> &operator=(const AVLTree<R> &tree);
  AVLTree &operator=(const AVLTree &tree);

  AVLTree<T> &operator=(AVLTree &&tree) noexcept;

  template <TreeContainer<T> Container>
  AVLTree<T> &operator=(const Container &tree);

  template <TreeContainer<T> Container>
  AVLTree<T> &operator=(const Container &tree)
    requires requires(typename Container::value_type elem) {
      { elem } -> convertible_to<T>;
    };

  template <common_with_TreeType<T> R>
  AVLTree<common_type_t<T, R>> operator|(const AVLTree<R> &tree) const;
  AVLTree<T> operator|(const AVLTree<T> &tree) const;

  template <common_with_TreeType<T> R>
  AVLTree<common_type_t<T, R>> operator|(const R &element) const;
  AVLTree<T> operator|(const T &element) const;

  template <common_with_TreeType<T> R>
  AVLTree<common_type_t<T, R>> unionTree(const AVLTree<R> &tree) const;
  AVLTree<T> unionTree(const AVLTree &tree) const;

  template <common_with_TreeType<T> R>
  AVLTree<common_type_t<T, R>> unionTree(const R &tree) const;
  AVLTree<T> unionTree(const T &tree) const;

  template <ConvertibleTo<T> R> AVLTree<T> &operator|=(const AVLTree<R> &tree);
  AVLTree<T> &operator|=(const AVLTree<T> &tree);

  template <ConvertibleTo<T> R> AVLTree<T> &operator|=(const R &tree);
  AVLTree<T> &operator|=(const T &tree);

  template <ConvertibleTo<T> R> AVLTree<T> &addEq(const AVLTree<R> &tree) const;
  AVLTree<T> &addEq(const AVLTree<T> &tree) const;

  template <ConvertibleTo<T> R> AVLTree<T> &addEq(const R &tree);
  AVLTree<T> &addEq(const T &tree);

  template <common_with_TreeType<T> R>
  AVLTree<common_type_t<T, R>> operator-(const AVLTree<R> &tree) const;
  AVLTree<T> operator-(const AVLTree<T> &tree) const;

  template <ConvertibleTo<T> R> AVLTree<T> operator-(const R &element) const;
  AVLTree<T> operator-(const T &element) const;

  template <common_with_TreeType<T> R>
  AVLTree<common_type_t<T, R>> substract(const AVLTree<R> &tree) const;
  AVLTree<T> substract(const AVLTree<T> &tree) const;

  template <common_with_TreeType<T> R>
  AVLTree<common_type_t<T, R>> substract(const R &element) const;
  AVLTree<T> substract(const T &element) const;

  template <ConvertibleTo<T> R> AVLTree<T> &operator-=(const AVLTree<R> &tree);
  AVLTree<T> &operator-=(const AVLTree<T> &tree);

  template <ConvertibleTo<T> R> AVLTree<T> &operator-=(const R &element);
  AVLTree<T> &operator-=(const T &element);

  template <ConvertibleTo<T> R> AVLTree<T> &substractEq(const AVLTree<R> &tree);
  AVLTree<T> &substractEq(const AVLTree<T> &tree);

  template <ConvertibleTo<T> R> AVLTree<T> &substractEq(const R &element);
  AVLTree<T> &substractEq(const T &element);

  template <common_with_TreeType<T> R>
  AVLTree<common_type_t<T, R>> operator&(const AVLTree<R> &tree) const;
  AVLTree<T> operator&(const AVLTree<T> &tree) const;

  template <common_with_TreeType<T> R>
  AVLTree<common_type_t<T, R>> operator&(const R &element) const;
  AVLTree<T> operator&(const T &element) const;

  template <common_with_TreeType<T> R>
  AVLTree<common_type_t<T, R>> intersect(const AVLTree<R> &tree) const;
  AVLTree<T> intersect(const AVLTree<T> &tree) const;

  template <common_with_TreeType<T> R>
  AVLTree<common_type_t<T, R>> intersect(const R &element) const;
  AVLTree<T> intersect(const T &element) const;

  template <ConvertibleTo<T> R> AVLTree<T> &operator&=(const AVLTree<R> &tree);
  AVLTree<T> &operator&=(const AVLTree<T> &tree);

  template <ConvertibleTo<T> R> AVLTree<T> &operator&=(const R &element);
  AVLTree<T> &operator&=(const T &element);

  template <ConvertibleTo<T> R> AVLTree<T> &intEq(const AVLTree<R> &tree);
  AVLTree<T> &intEq(const AVLTree<T> &tree);

  template <ConvertibleTo<T> R> AVLTree<T> &intEq(const R &element);
  AVLTree<T> &intEq(const T &element);

  template <common_with_TreeType<T> R>
  AVLTree<common_type_t<T, R>> operator^(const AVLTree<R> &tree) const;
  AVLTree<T> operator^(const AVLTree<T> &tree) const;

  template <common_with_TreeType<T> R>
  AVLTree<common_type_t<T, R>> operator^(const R &element) const;
  AVLTree<T> operator^(const T &element) const;

  template <common_with_TreeType<T> R>
  AVLTree<common_type_t<T, R>>
  symmetricDifference(const AVLTree<R> &tree) const;
  AVLTree<T> symmetricDifference(const AVLTree<T> &tree) const;

  template <common_with_TreeType<T> R>
  AVLTree<common_type_t<T, R>> symmetricDifference(const R &element) const;
  AVLTree<T> symmetricDifference(const T &element) const;

  template <ConvertibleTo<T> R> AVLTree<T> &operator^=(const AVLTree<R> &tree);
  AVLTree<T> &operator^=(const AVLTree<T> &tree);

  template <ConvertibleTo<T> R> AVLTree<T> &operator^=(const R &element);
  AVLTree<T> &operator^=(const T &element);

  template <ConvertibleTo<T> R>
  AVLTree<T> &symmetricDifferenceEq(const AVLTree<R> &tree);
  AVLTree<T> &symmetricDifferenceEq(const AVLTree<T> &tree);

  template <ConvertibleTo<T> R>
  AVLTree<T> &symmetricDifferenceEq(const R &element);
  AVLTree<T> &symmetricDifferenceEq(const T &element);

  ~AVLTree() override;

  const AVLTreeIterator<T> begin() const;
  const AVLTreeIterator<T> end() const;
  const AVLTreeIterator<T> cbegin() const;
  const AVLTreeIterator<T> cend() const;

  bool insert(const T &x);
  template <ConvertibleTo<T> R> bool insert(const R &x);

  bool remove(const T &x);
  template <ConvertibleTo<T> R> bool remove(const R &x);

  std::optional<const T &> treeMax() const;

  std::optional<const T &> treeMin() const;

  bool contains(const T &x) const;

  template <ConvertibleTo<T> R> bool contains(const R &x) const;

  template <TreeType R>
  friend std::ostream &operator<<(std::ostream &out, AVLTree<R> &tree);

private:
  NodePtr<T> root;

  int height(NodePtr<T> t) const;

  int balanceFactor(const NodePtr<T> &t);

  void fixBalance(NodePtr<T> &node);

  NodePtr<T> insert(NodePtr<T> &start, const NodePtr<T> &ptr);

  NodePtr<T> search(const NodePtr<T> &node, const T &data) const;

  NodePtr<T> leftRotate(NodePtr<T> x);

  NodePtr<T> rightRotate(NodePtr<T> y);

  void updateHeight(NodePtr<T> node);

  NodePtr<T> remove(NodePtr<T> &start, const T &key);

  NodePtr<T> find(const T &x) const;

  NodePtr<T> treeMax(NodePtr<T> node) const;

  NodePtr<T> treeMin(NodePtr<T> node) const;
};

template <TreeType T> bool AVLTree<T>::contains(const T &x) const {
  return find(x);
}

#include "AVLTree.inl"

#endif // LAB2_AVLTREE_H
