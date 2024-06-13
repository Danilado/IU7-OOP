#include "AVLIterator.h"

template<TreeType T>
AVLTreeIterator<T>::AVLTreeIterator(const AVLTree<T> &tree) noexcept {
	current_node = tree.root;
}

template<TreeType T>
AVLTreeIterator<T>::AVLTreeIterator(AVLTree<T> &tree) noexcept {
	current_node = tree.root;
}

//template<TreeType T>
//AVLTreeIterator<T>::AVLTreeIterator(const AVLTreeIterator<T> &iter) noexcept {
//	current_node = iter.current_node;
//}

template<TreeType T>
AVLTreeIterator<T>::pointer AVLTreeIterator<T>::operator->() const {
	return &(current_node.lock()->data());
}

template<TreeType T>
AVLTreeIterator<T>::reference AVLTreeIterator<T>::operator*() const {
	return current_node.lock()->data();
}

template<TreeType T>
bool AVLTreeIterator<T>::operator==(const AVLTreeIterator &other) const {
	auto this_shared_ptr = current_node.lock();
	auto other_shared_ptr = other.current_node.lock();
	return this_shared_ptr == other_shared_ptr;
}

template<TreeType T>
bool AVLTreeIterator<T>::operator!=(const AVLTreeIterator &other) const {
	return !(*this == other);
}

template<TreeType T>
AVLTreeIterator<T>::operator bool() const {
	return !current_node.expired();
}

template<TreeType T>
AVLTreeIterator<T>::AVLTreeIterator(const NodePtr<T> &node_ptr) noexcept {
	current_node = node_ptr;
}

template<TreeType T>
AVLTreeIterator<T> &AVLTreeIterator<T>::operator++() {
	auto shared_node_ptr = current_node.lock();

	if (shared_node_ptr->right() != nullptr) {
		shared_node_ptr = shared_node_ptr->right();
		while (shared_node_ptr->left() != nullptr)
			shared_node_ptr = shared_node_ptr->left();
		current_node = shared_node_ptr;
	} else {
		auto parent = shared_node_ptr->parent().lock();
		while (parent != nullptr && shared_node_ptr == parent->right()) {
			shared_node_ptr = parent;
			parent = parent->parent().lock();
		}
		current_node = parent;
	}
	return *this;
}

template<TreeType T>
AVLTreeIterator<T> &AVLTreeIterator<T>::operator--() {
	auto shared_node_ptr = current_node.lock();

	if (shared_node_ptr->left() != nullptr) {
		shared_node_ptr = shared_node_ptr->left();
		while (shared_node_ptr->right() != nullptr)
			shared_node_ptr = shared_node_ptr->right();
		current_node = shared_node_ptr;
	} else {
		auto parent = shared_node_ptr->parent().lock();
		while (parent != nullptr && shared_node_ptr == parent->left()) {
			shared_node_ptr = parent;
			parent = parent->parent().lock();
		}
		current_node = parent;
	}
	return *this;
}

template<TreeType T>
AVLTreeIterator<T> &AVLTreeIterator<T>::operator+=(size_type value) {
	for (difference_type i = 0; i < value; ++i) {
		++(*this);
	}
	return *this;
}

template<TreeType T>
AVLTreeIterator<T> &AVLTreeIterator<T>::operator-=(size_type value) {
	for (difference_type i = 0; i < value; ++i) {
		--(*this);
	}
	return *this;
}

template<TreeType T>
AVLTreeIterator<T> AVLTreeIterator<T>::operator++(int) {
	AVLTreeIterator temp = *this;
	++(*this);
	return temp;
}

template<TreeType T>
AVLTreeIterator<T> AVLTreeIterator<T>::operator--(int) {
	AVLTreeIterator temp = *this;
	--(*this);
	return temp;
}

template<TreeType T>
AVLTreeIterator<T>::AVLTreeIterator(AVLTree<T> &&tree) noexcept {
	current_node = tree.root;
}
