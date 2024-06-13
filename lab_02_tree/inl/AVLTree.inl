#include "AVLTree.h"


template<TreeType T>
template<ConvertibleTo<T> R>
AVLTree<T>& AVLTree<T>::symmetricDifferenceEq(const R& element)
{
	this->remove(element);
	return *this;
}

template<TreeType T>
std::optional<const T&> AVLTree<T>::treeMax() const
{
	auto min = treeMax(root);
	return min->key;
}

template<TreeType T>
std::optional<const T&> AVLTree<T>::treeMin() const
{
	auto min = treeMin(root);
	return min->key;
}


template<TreeType T>
AVLTree<T>::AVLTree()
{
	root = nullptr;
}

template<TreeType T>
template<ConvertibleTo<T> R>
AVLTree<T>::AVLTree(const AVLTree<R>& matrix): AVLTree()
{
	for (const auto& elem: matrix)
		insert(elem);
}

template<TreeType T>
AVLTree<T>::AVLTree(const AVLTree<T>& matrix): AVLTree()
{
	for (const auto& elem: matrix)
		insert(elem);
}

template<TreeType T>
template<ConvertibleTo<T> R>
AVLTree<T>::AVLTree(const R* arr, size_t size)
{
	for (size_t i = 0; i < size; i++)
		insert(arr[i]);
}

template<TreeType T>
template<TreeContainer<T> Container>
AVLTree<T>::AVLTree(const Container& tree)
{
	for (const auto& elem: tree)
		insert(elem);
}

template<TreeType T>
AVLTree<T>::AVLTree(AVLTree<T>&& tree) noexcept
{
	tree.root = root;
}

template<TreeType T>
template<std::input_iterator Iter, std::sentinel_for<Iter> Iter_e>
requires std::convertible_to<T, typename Iter::value_type>
AVLTree<T>::AVLTree(Iter begin, Iter_e end)
{
	for (std::input_iterator auto i = begin; i != end; i++)
		insert(i);
}

template<TreeType T>
template<ConvertibleTo<T> R>
AVLTree<T>& AVLTree<T>::operator|=(const AVLTree<R>& tree)
{
	for (auto a: tree)
		this->insert(a);
	return *this;
}

template<TreeType T>
template<common_with_TreeType<T> R>
AVLTree<common_type_t<T, R>> AVLTree<T>::operator|(const AVLTree<R>& tree) const
{
	AVLTree<common_type_t<T, R>> new_tree;
	for (auto a: tree)
		new_tree.insert(a);
	return new_tree;
}

//template<TreeType T>
//template<TreeType R>
//AVLTree<T> &AVLTree<T>::operator&=(const AVLTree<R> &tree)
//{
//    for (auto a: tree)
//        insert(a);
//    return *this;
//}
//
//template<TreeType T>
//template<TreeType R>
//decltype(auto) AVLTree<T>::operator&(const AVLTree<R> &tree) const
//{
//    AVLTree<common_type_t<T, R>> new_tree;
//    for (auto a: tree)
//        new_tree.insert(a);
//    return new_tree;
//}
//
//template<TreeType T>
//template<TreeType R>
//AVLTree<T> &AVLTree<T>::join(const AVLTree<R> &tree)
//{
//    for (auto a: tree)
//        insert(a);
//    return *this;
//}
//
//template<TreeType T>
//template<TreeType R>
//decltype(auto) AVLTree<T>::join(const AVLTree<R> &tree) const
//{
//    AVLTree<common_type_t<T, R>> new_tree;
//    for (auto a: tree)
//        new_tree.insert(a);
//    return new_tree;
//}

template<TreeType T>
template<common_with_TreeType<T> R>
AVLTree<common_type_t<T, R>> AVLTree<T>::unionTree(const AVLTree<R>& tree) const
{
	AVLTree<common_type_t<T, R>> new_tree(*this);
	for (auto a: tree)
		new_tree.insert(a);
	return new_tree;
}

//template<TreeType T>
//AVLTree<T> AVLTree<T>::unionTree(const AVLTree<T>& tree) const
//{
//	AVLTree<T> new_tree(*this);
//	for (auto x: tree) {
//		new_tree.insert(x);
//	}
//	return new_tree;
//}

template<TreeType T>
template<ConvertibleTo<T> R>
AVLTree<T>& AVLTree<T>::addEq(const AVLTree<R>& tree) const
{
	AVLTree<common_type_t<T, R>> new_tree;
	for (auto a: tree)
		new_tree.insert(a);
	return new_tree;
}


template<TreeType T>
AVLTree<T>::AVLTree(TreeIterator auto range)
{
	for (auto i: range)
		insert(i);
}


template<TreeType T>
template<ConvertibleTo<T> R>
AVLTree<T>::AVLTree(std::initializer_list<R> init_list): AVLTree()
{
	for (const auto& elem: init_list)
		insert(elem);
}

template<TreeType T>
AVLTree<T>::AVLTree(std::initializer_list<T> init_list): AVLTree()
{
	for (const auto& elem: init_list)
		insert(elem);
}

template<TreeType T>
template<ConvertibleTo<T> R>
AVLTree<T>& AVLTree<T>::operator=(initializer_list<R> init_list)
{
	root = nullptr;
	for (const auto& elem: init_list)
		insert(elem);
	return *this;
}

template<TreeType T>
AVLTree<T>& AVLTree<T>::operator=(initializer_list<T> init_list)
{
	root = nullptr;
	for (const auto& elem: init_list)
		insert(elem);
	return *this;
}

template<TreeType T>
AVLTree<T>::~AVLTree()
{
	root->deleteNode();
}

template<TreeType T>
NodePtr<T> AVLTree<T>::treeMin(NodePtr<T> node) const
{
	if (root == nullptr)
		return root;
	while (node->left() != nullptr)
		node = node->left();
	return node;
}

template<TreeType T>
NodePtr<T> AVLTree<T>::treeMax(NodePtr<T> node) const
{
	if (root == nullptr)
		return root;
	while (node->right != nullptr)
		node = node->right;
	return node;
}

template<TreeType T>
const AVLTreeIterator<T> AVLTree<T>::begin() const
{
	return AVLTreeIterator<T>(treeMin(root));
}

template<TreeType T>
const AVLTreeIterator<T> AVLTree<T>::end() const
{
	return AVLTreeIterator<T>(nullptr);
}

//template<TreeType T>
//AVLTreeIterator<T> AVLTree<T>::begin()
//{
//    return AVLTreeIterator<T>(treeMin(root));
//}
//
//template<TreeType T>
//AVLTreeIterator<T> AVLTree<T>::end()
//{
//    return AVLTreeIterator<T>(treeMax(root));
//}

template<TreeType T>
const AVLTreeIterator<T> AVLTree<T>::cbegin() const
{
	return AVLTreeIterator<T>(treeMin(root));
}

template<TreeType T>
const AVLTreeIterator<T> AVLTree<T>::cend() const
{
	return AVLTreeIterator<T>(treeMax(root));
}

template<TreeType T>
int AVLTree<T>::balanceFactor(const NodePtr<T>& t)
{
	return height(t->left()) - height(t->right());
}

template<TreeType T>
NodePtr<T> AVLTree<T>::insert(NodePtr<T>& start, const NodePtr<T>& ptr)
{
	if (start == nullptr)
		return ptr;

	if (ptr->data() < start->data())
	{
		start->left_ = insert(start->left_, ptr);
		start->left()->parent_ = start;
	}
	else if (ptr->data() > start->data())
	{
		start->right_ = insert(start->right_, ptr);
		start->right()->parent_ = start;
	}
	return start;
}

template<TreeType T>
NodePtr<T> AVLTree<T>::search(const NodePtr<T>& node, const T& data) const
{
	if (node == nullptr or node->key == data)
		return node;
	if (node->key > data)
		return search(node->left(), data);
	return search(node->right(), data);
}

template<TreeType T>
NodePtr<T> AVLTree<T>::remove(NodePtr<T>& start, const T& key)
{
	if (start == nullptr)
		return start;
	if (key < start->key)
		return remove(start->left, key);
	if (key > start->key)
		return remove(start->right, key);
	if (start->left == nullptr || start->right == nullptr)
		return start;

	NodePtr<T> temp = treeMin(start->right);
	start->key = temp->key;
	return remove(start->right, temp->key);
}

template<TreeType T>
void AVLTree<T>::fixBalance(NodePtr<T>& node)
{
	updateHeight(node);
	int balance = balanceFactor(node);

	if (balance > 1 && balanceFactor(node->left()) >= 0)
		rightRotate(node);

	if (balance > 1 && balanceFactor(node->left()) < 0)
	{
		node->left_ = leftRotate(node->left());
		rightRotate(node);
	}
	if (balance < -1 && balanceFactor(node->right()) <= 0)
		leftRotate(node);

	if (balance < -1 && balanceFactor(node->right()) > 0)
	{
		node->right_ = rightRotate(node->right());
		leftRotate(node);
	}
}

template<TreeType T>
int AVLTree<T>::height(NodePtr<T> t) const
{
	return t == nullptr ? -1 : t->height;
}

template<TreeType T>
void AVLTree<T>::updateHeight(NodePtr<T> node)
{
	if (node != nullptr)
	{
		int leftHeight = height(node->left());
		int rightHeight = height(node->right());
		node->height = 1 + std::max(leftHeight, rightHeight);
	}
}

template<TreeType T>
NodePtr<T> AVLTree<T>::rightRotate(NodePtr<T> y)
{
	NodePtr<T> x = y->left();
	NodePtr<T> T2 = x->right();
	x->right_ = y;
	y->left_ = T2;
	if (T2 != nullptr)
		T2->parent_ = y;
	x->parent_ = y->parent();
	y->parent_ = x;
	updateHeight(y);
	updateHeight(x);
	return x;
}

template<TreeType T>
template<ConvertibleTo<T> R>
bool AVLTree<T>::insert(const R& x)
{
	NodePtr<T> node = std::make_shared<Node<T>>(x);
	root = insert(root, node);
	fixBalance(node);
}

template<TreeType T>
bool AVLTree<T>::insert(const T& x)
{
	NodePtr<T> node = std::make_shared<Node<T>>(x);
	root = insert(root, node);
	fixBalance(node);
}

template<TreeType T>
NodePtr<T> AVLTree<T>::find(const T& x) const
{
	const auto node = root;
	return search(node, x);
}

template<TreeType T>
bool AVLTree<T>::remove(const T& x)
{
	NodePtr<T> node = remove(root, x);
	fixBalance(node);
}

template<TreeType T>
NodePtr<T> AVLTree<T>::leftRotate(NodePtr<T> x)
{
	NodePtr<T> y = x->right_;
	NodePtr<T> T2 = y->left_;
	y->left_ = x;
	x->right_ = T2;
	if (T2 != nullptr)
		T2->parent_ = x;
	y->parent_ = x->parent_;
	x->parent_ = y;
	updateHeight(x);
	updateHeight(y);

	return y;
}

template<TreeType T>
std::ostream& operator<<(std::ostream& out, AVLTree<T>& tree)
{
	for (const auto& elem: tree)
		std::cout << elem << std::endl;
	return out;
}

//template<TreeType T>
//template<TreeType R>
//AVLTree<T> &AVLTree<T>::operator&=(const AVLTree<R> &matrix)
//{
//    return *this;
//}

//template<TreeType T>
//template<ConvertibleTo<T> U, TreeContainer<U> Container>
//AVLTree<T> &AVLTree<T>::operator=(const Container &matrix) requires requires(
//        TreeType Container::value_type elem) {{ elem } -> convertible_to<T>; }
//{
//    for (auto &n: matrix)
//        this->insert(n);
//    return *this;
//}

template<TreeType T>
template<TreeContainer<T> Container>
AVLTree<T>& AVLTree<T>::operator=(const Container& tree)
requires
requires(
		typename Container::value_type elem) {{ elem } -> convertible_to<T>; }
{
	for (auto& n: tree)
		this->insert(n);
	return *this;
}

template<TreeType T>
AVLTree<T>& AVLTree<T>::operator=(AVLTree&& tree) noexcept
{
	this->root = tree.root;
	return *this;
}

//template<TreeType T>
//template<TreeType R>
//decltype(auto) AVLTree<T>::operator&=(const AVLTree<R> &matrix) const
//{
//    return nullptr;
//}


template<TreeType T>
template<ConvertibleTo<T> R>
AVLTree<T>& AVLTree<T>::operator=(const AVLTree<R>& tree)
{
	for (auto& n: tree)
		this->insert(n);
	return *this;
}

template<TreeType T>
template<common_with_TreeType<T> R>
AVLTree<common_type_t<T,R>> AVLTree<T>::operator|(const R& element) const
{
	this->insert(element);
	return AVLTree<common_type_t<T,R>>();
}

template<TreeType T>
template<ConvertibleTo<T> R>
AVLTree<T>& AVLTree<T>::operator|=(const R& tree)
{
	this->insert(tree);
	return *this;
}

template<TreeType T>
AVLTree<T>& AVLTree<T>::operator|=(const T& tree)
{
	this->insert(tree);
	return *this;
}

template<TreeType T>
template<ConvertibleTo<T> R>
AVLTree<T>& AVLTree<T>::addEq(const R& tree)
{
	this->insert(tree);
	return *this;
}

template<TreeType T>
template<common_with_TreeType<T> R>
AVLTree<common_type_t<T, R>> AVLTree<T>::unionTree(const R& tree) const
{
	AVLTree<common_type_t<T, R>> res;
	res.insert(tree);
	return res;
}

template<TreeType T>
AVLTree<T> AVLTree<T>::unionTree(const T& tree) const
{
	AVLTree<T> res(*this);
	res.insert(tree);
	return res;
}


template<TreeType T>
template<common_with_TreeType<T> R>
AVLTree<common_type_t<T, R>> AVLTree<T>::operator&(const AVLTree<R>& tree) const
{
	AVLTree<common_type_t<T, R>> result(*this);
	result &= tree;
	return result;
}


template<TreeType T>
template<common_with_TreeType<T> R>
AVLTree<common_type_t<T,R>> AVLTree<T>::operator&(const R& element) const
{
	AVLTree<common_type_t<T,R>> result;
	if (contains(element))
	{
		result.insert(element);
	}
	return result;
}


template<TreeType T>
template<common_with_TreeType<T> R>
AVLTree<common_type_t<T,R>> AVLTree<T>::operator-(const AVLTree<R>& tree) const
{
	AVLTree<common_type_t<T,R>> result(*this);
	result -= tree;
	return result;
}


template<TreeType T>
template<ConvertibleTo<T> R>
AVLTree<T> AVLTree<T>::operator-(const R& element) const
{
	AVLTree<T> result(*this);
	result -= element;
	return result;
}

template<TreeType T>
template<common_with_TreeType<T> R>
AVLTree<common_type_t<T, R>> AVLTree<T>::substract(const AVLTree<R>& tree) const
{
	AVLTree<common_type_t<T, R>> result(*this);
	result -= tree;
	return result;
}


template<TreeType T>
template<common_with_TreeType<T> R>
AVLTree<common_type_t<T,R>> AVLTree<T>::substract(const R& element) const
{
	AVLTree<common_type_t<T,R>> result(*this);
	result -= element;
	return result;
}


template<TreeType T>
template<ConvertibleTo<T> R>
AVLTree<T>& AVLTree<T>::operator-=(const AVLTree<R>& tree)
{
	for (const auto& elem: tree)
	{
		this->remove(elem);
	}
	return *this;
}


template<TreeType T>
template<ConvertibleTo<T> R>
AVLTree<T>& AVLTree<T>::operator-=(const R& element)
{
	this->remove(element);
	return *this;
}


template<TreeType T>
template<ConvertibleTo<T> R>
AVLTree<T>& AVLTree<T>::substractEq(const AVLTree<R>& tree)
{
	*this -= tree;
	return *this;
}


template<TreeType T>
template<ConvertibleTo<T> R>
AVLTree<T>& AVLTree<T>::substractEq(const R& element)
{
	*this -= element;
	return *this;
}









// avltree_operations.hpp

template<TreeType T>
template<common_with_TreeType<T> R>
AVLTree<common_type_t<T, R>> AVLTree<T>::intersect(const AVLTree<R>& tree) const
{
	AVLTree<common_type_t<T, R>> result;
	for (const auto& elem: tree)
	{
		if (this->find(elem))
		{
			result.insert(elem);
		}
	}
	return result;
}


template<TreeType T>
template<common_with_TreeType<T> R>
AVLTree<common_type_t<T,R>> AVLTree<T>::intersect(const R& element) const
{
	AVLTree<common_type_t<T,R>> result;
	if (contains(element))
	{
		result.insert(element);
	}
	return result;
}


template<TreeType T>
template<ConvertibleTo<T> R>
AVLTree<T>& AVLTree<T>::operator&=(const AVLTree<R>& tree)
{
	AVLTree<T> result;
	for (const auto& elem: *this)
	{
		if (tree.contains(elem))
		{
			result.insert(elem);
		}
	}
	*this = result;
	return *this;
}

template<TreeType T>
template<common_with_TreeType<T> R>
AVLTree<common_type_t<T, R>> AVLTree<T>::operator^(const AVLTree<R>& tree) const
{
	return this->symmetricDifference(tree);
}

template<TreeType T>
AVLTree<T> AVLTree<T>::operator^(const AVLTree<T>& tree) const
{
	return this->symmetricDifference(tree);
}

template<TreeType T>
template<common_with_TreeType<T> R>
AVLTree<common_type_t<T,R>> AVLTree<T>::operator^(const R& element) const
{
	AVLTree<common_type_t<T,R>> result = *this;
	result.remove(element);
	return result;
}

template<TreeType T>
template<common_with_TreeType<T> R>
AVLTree<common_type_t<T, R>> AVLTree<T>::symmetricDifference(const AVLTree<R>& tree) const
{
	AVLTree<common_type_t<T, R>> result;

	std::function<void(NodePtr<T>, AVLTree<common_type_t<T, R>>&)> traverse =
			[&](NodePtr<T> node, AVLTree<common_type_t<T, R>>& result)
			{
				if (!node) return;

				if (!tree.contains(node->key))
				{
					result.insert(node->key);
				}

				traverse(node->left(), result);
				traverse(node->right(), result);
			};

	traverse(root, result);
	traverse(tree.root, result);

	return result;
}

template<TreeType T>
AVLTree<T> AVLTree<T>::symmetricDifference(const AVLTree<T>& tree) const
{
	AVLTree<T> result;

	std::function<void(NodePtr<T>, AVLTree<T>&)> traverse =
			[&](NodePtr<T> node, AVLTree<T>& result)
			{
				if (!node) return;

				if (!tree.find(node->key))
				{
					result.insert(node->key);
				}

				traverse(node->left(), result);
				traverse(node->right(), result);
			};

	traverse(root, result);

	return result;
}

template<TreeType T>
template<common_with_TreeType<T> R>
AVLTree<common_type_t<T, R>> AVLTree<T>::symmetricDifference(const R& element) const
{
	AVLTree<common_type_t<T, R>> result = *this;
	result.remove(element);
	return result;
}

template<TreeType T>
template<ConvertibleTo<T> R>
AVLTree<T>& AVLTree<T>::operator^=(const AVLTree<R>& tree)
{
	*this = this->symmetricDifference(tree);
	return *this;
}

template<TreeType T>
AVLTree<T>& AVLTree<T>::operator^=(const AVLTree<T>& tree)
{
	*this = this->symmetricDifference(tree);
	return *this;
}

template<TreeType T>
template<ConvertibleTo<T> R>
AVLTree<T>& AVLTree<T>::operator^=(const R& element)
{
	this->remove(element);
	return *this;
}


template<TreeType T>
template<ConvertibleTo<T> R>
AVLTree<T>& AVLTree<T>::operator&=(const R& element)
{
	if (!contains(element))
	{
		this->remove(element);
	}
	return *this;
}


template<TreeType T>
template<ConvertibleTo<T> R>
AVLTree<T>& AVLTree<T>::intEq(const AVLTree<R>& tree)
{
	*this &= tree;
	return *this;
}


template<TreeType T>
template<ConvertibleTo<T> R>
AVLTree<T>& AVLTree<T>::intEq(const R& element)
{
	*this &= element;
	return *this;
}


//template<TreeType T>
//AVLTree<T> AVLTree<T>::symmetricDifference(const AVLTree<T>& tree) const
//{
//	AVLTree<T> result;
//
//	std::function<void(NodePtr<T>, AVLTree<T>&)> traverse =
//			[&](NodePtr<T> node, AVLTree<T>& result)
//			{
//				if (!node) return;
//
//				if (!tree.search(node->key))
//				{
//					result.insert(node->key);
//				}
//
//				traverse(node->left, result);
//				traverse(node->right, result);
//			};
//
//	traverse(root, result);
//	traverse(tree.root, result);
//
//	return result;
//}
//
//template<TreeType T>
//template<common_with_TreeType<T> R>
//AVLTree<common_type_t<T,R>> AVLTree<T>::symmetricDifference(const AVLTree<R>& tree) const
//{
//	AVLTree<common_type_t<T,R>> result;
//
//	std::function<void(NodePtr<T>, AVLTree<T>&)> traverse =
//			[&](NodePtr<T> node, AVLTree<T>& result)
//			{
//				if (!node) return;
//
//				if (!tree.search(node->key))
//				{
//					result.insert(node->key);
//				}
//
//				traverse(node->left, result);
//				traverse(node->right, result);
//			};
//
//	traverse(root, result);
//
//	return result;
//}

template<TreeType T>
AVLTree<T>& AVLTree<T>::symmetricDifferenceEq(const AVLTree<T>& tree)
{
	*this = this->symmetricDifference(tree);
	return *this;
}

template<TreeType T>
template<ConvertibleTo<T> R>
AVLTree<T>& AVLTree<T>::symmetricDifferenceEq(const AVLTree<R>& tree)
{
	*this = this->symmetricDifference(tree);
	return *this;
}

template<TreeType T>
AVLTree<T> operator^(const AVLTree<T>& lhs, const AVLTree<T>& rhs)
{
	return lhs.symmetricDifference(rhs);
}
//
//template<ConvertibleTo<T> R>
//AVLTree<T> operator^(const AVLTree<T>& lhs, const AVLTree<R>& rhs) {
//	return lhs.symmetricDifference(rhs);
//}










