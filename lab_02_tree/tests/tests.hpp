#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <algorithm>
#include <iostream>
#include <iterator>
#include <utility>
#include <initializer_list>

template<typename T>
struct AvlNode {
    T element;
    AvlNode *left;
    AvlNode *right;
    AvlNode *parent;
    int height;

    AvlNode(const T &theElement, AvlNode *lt, AvlNode *rt, AvlNode *pt = nullptr, int h = 0)
            : element{theElement}, left{lt}, right{rt}, parent{pt}, height{h}
    {}
};

template<typename T>
class AvlTree {
public:

    class AvlIterator : public std::iterator<std::bidirectional_iterator_tag, T> {
    public:

        typedef T value_type;

        AvlIterator() : nodePtr(nullptr), tree(nullptr)
        {}

        bool operator==(const AvlIterator &rhs) const
        {
            return tree == rhs.tree && nodePtr == rhs.nodePtr;
        }

        bool operator!=(const AvlIterator &rhs) const
        {
            return tree != rhs.tree || nodePtr != rhs.nodePtr;
        }

        const T &operator*() const
        {
            if (nodePtr == nullptr)
                throw std::out_of_range("Dereferencing nullptr");
            return nodePtr->element;
        }

        AvlIterator &operator++();

        AvlIterator operator++(int);

        AvlIterator &operator--();

        AvlIterator operator--(int);

    private:
        friend class AvlTree<T>;

        const AvlNode<T> *nodePtr;
        const AvlTree<T> *tree;

        AvlIterator(const AvlNode<T> *p, const AvlTree<T> *t) : nodePtr(p), tree(t)
        {}
    };

    typedef AvlIterator const_iterator;
    typedef const_iterator iterator;

    AvlTree() : root(nullptr)
    {}

    AvlTree(const AvlTree &rhs) : root(nullptr)
    {
        root = clone(rhs.root, nullptr); // Passing nullptr as parent
    }

    AvlTree(AvlTree &&rhs) noexcept: root(rhs.root)
    {
        if (root != nullptr) root->parent = nullptr;
        rhs.root = nullptr;
    }

    AvlTree(std::initializer_list<T> init_list) : root(nullptr)
    {
        for (const auto &elem: init_list)
            this->insert(elem);
    }

    ~AvlTree()
    {
        makeEmpty();
    }

    AvlTree &operator=(const AvlTree &rhs) noexcept
    {
        AvlTree copy = rhs;
        std::swap(*this, copy);
        return *this;
    }

    AvlTree &operator=(AvlTree &&rhs) noexcept
    {
        std::swap(root, rhs.root);
        if (root != nullptr) root->parent = nullptr;
        return *this;
    }

    const_iterator find(const T &item) const;

    const_iterator begin() const
    {
        return const_iterator(findMin(root), this);
    }

    const_iterator end() const
    {
        return const_iterator(nullptr, this);
    }

    bool contains(const T &x) const
    {
        return contains(x, root);
    }

    bool isEmpty() const
    {
        return root == nullptr;
    }

    void printTree(std::ostream &out = std::cout) const
    {
        if (isEmpty())
            out << "Empty tree" << std::endl;
        else
            printTree(root, out);
    }

    void makeEmpty()
    {
        makeEmpty(root);
    }

    const_iterator insert(const T &x)
    {
        auto t = insert(x, root, nullptr);
        if (t == nullptr)
            return end();
        else
            return const_iterator(t, this);
    }

    void remove(const T &x)
    {
        remove(x, root);
    }

private:

    AvlNode<T> *root;

    AvlNode<T> *insert(const T &x, AvlNode<T> *
    &t, AvlNode<T> *parent);

    bool remove(const T &x, AvlNode<T> *&t);

    const AvlNode<T> *findMin(const AvlNode<T> *t) const;

    const AvlNode<T> *findMax(const AvlNode<T> *t) const;

    bool contains(const T &x, AvlNode<T> *t) const;

    void makeEmpty(AvlNode<T> *&t);

    void printTree(AvlNode<T> *t, std::ostream &out) const;

    AvlNode<T> *clone(AvlNode<T> *t, AvlNode<T> *parent) const;

    int height(AvlNode<T> *t) const;

    void rotateWithLeftChild(AvlNode<T> *&k2);

    void rotateWithRightChild(AvlNode<T> *&k1);

    void doubleWithLeftChild(AvlNode<T> *&k3);

    void doubleWithRightChild(AvlNode<T> *&k1);
};

template<class T>
typename AvlTree<T>::AvlIterator &AvlTree<T>::AvlIterator::operator++()
{
    if (nodePtr == nullptr) {
        nodePtr = tree->findMin(tree->root);
    } else if (nodePtr->right != nullptr) {
        nodePtr = tree->findMin(nodePtr->right);
    } else {
        const AvlNode<T> *parent = nullptr;
        const AvlNode<T> *current = tree->root;
        while (current != nullptr && current != nodePtr) {
            if (nodePtr->element < current->element) {
                parent = current;
                current = current->left;
            } else {
                current = current->right;
            }
        }
        nodePtr = parent;
    }
    return *this;
}

template<class T>
typename AvlTree<T>::AvlIterator AvlTree<T>::AvlIterator::operator++(int)
{
    auto saved = *this;
    operator++();
    return saved;
}

template<class T>
typename AvlTree<T>::AvlIterator &AvlTree<T>::AvlIterator::operator--()
{
    if (nodePtr == nullptr) {
        nodePtr = tree->findMax(tree->root);
    } else if (nodePtr->left != nullptr) {
        nodePtr = tree->findMax(nodePtr->left);
    } else {
        const AvlNode<T> *parent = nullptr;
        const AvlNode<T> *current = tree->root;
        while (current != nullptr && current != nodePtr) {
            if (nodePtr->element > current->element) {
                parent = current;
                current = current->right;
            } else {
                current = current->left;
            }
        }
        nodePtr = parent;
    }
    return *this;
}

template<class T>
typename AvlTree<T>::AvlIterator AvlTree<T>::AvlIterator::operator--(int)
{
    auto saved = *this;
    operator--();
    return saved;
}

template<class T>
AvlNode<T> *
AvlTree<T>::insert(const T &x, AvlNode<T> *&t, AvlNode<T> *parent)
{
    if (t == nullptr) {
        t = new AvlNode<T>{x, nullptr, nullptr, parent};
        return t;
    } else if (x < t->element) {
        auto temp = insert(x, t->left, t);
        if (height(t->left) - height(t->right) == 2) {
            if (x < t->left->element)
                rotateWithLeftChild(t);
            else
                doubleWithLeftChild(t);
        }
        t->height = std::max(height(t->left), height(t->right)) + 1;
        return temp;
    } else if (t->element < x) {
        auto temp = insert(x, t->right, t);
        if (height(t->right) - height(t->left) == 2) {
            if (x > t->right->element)
                rotateWithRightChild(t);
            else
                doubleWithRightChild(t);
        }
        t->height = std::max(height(t->left), height(t->right)) + 1;
        return temp;
    }
    return nullptr;
}

template<class T>
bool AvlTree<T>::remove(const T &x, AvlNode<T> *&t)
{
    if (t == nullptr)
        return false;
    if (x < t->element) {
        if (remove(x, t->left)) {
            if (height(t->right) - height(t->left) == 2) {
                if (height(t->right->left) > height(t->right->right))
                    doubleWithRightChild(t);
                else
                    rotateWithRightChild(t);
            }
            t->height = std::max(height(t->left), height(t->right)) + 1;
            return true;
        }
        return false;
    } else if (t->element < x) {
        if (remove(x, t->right)) {
            if (height(t->left) - height(t->right) == 2) {
                if (height(t->left->right) > height(t->left->left))
                    doubleWithLeftChild(t);
                else
                    rotateWithLeftChild(t);
            }
            t->height = std::max(height(t->left), height(t->right)) + 1;
            return true;
        }
        return false;
    } else if (t->left != nullptr && t->right != nullptr) {
        t->element = findMin(t->right)->element;
        remove(t->element, t->right);
        return true;
    } else {
        AvlNode<T> *oldNode = t;
        t = (t->left != nullptr) ? t->left : t->right;
        if (t != nullptr) t->parent = oldNode->parent;
        delete oldNode;
        return true;
    }
}

template<class T>
const AvlNode<T> *AvlTree<T>::findMin(const AvlNode<T> *t) const
{
    if (t == nullptr)
        return nullptr;
    while (t->left != nullptr)
        t = t->left;
    return t;
}

template<class T>
const AvlNode<T> *AvlTree<T>::findMax(const AvlNode<T> *t) const
{
    if (t == nullptr)
        return nullptr;
    while (t->right != nullptr)
        t = t->right;
    return t;
}

template<class T>
bool AvlTree<T>::contains(const T &x, AvlNode<T> *t) const
{
    if (t == nullptr)
        return false;
    else if (x < t->element)
        return contains(x, t->left);
    else if (t->element < x)
        return contains(x, t->right);
    else
        return true;
}

template<class T>
void AvlTree<T>::makeEmpty(AvlNode<T> *&t)
{
    if (t != nullptr) {
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
    }
    t = nullptr;
}

template<class T>
void AvlTree<T>::printTree(AvlNode<T> *t, std::ostream &out) const
{
    if (t != nullptr) {
        printTree(t->left, out);
        out << t->element << std::endl;
        printTree(t->right, out);
    }
}

template<class T>
AvlNode<T> *AvlTree<T>::clone(AvlNode<T> *t, AvlNode<T> *parent) const
{
    if (t == nullptr)
        return nullptr;
    else
        return new AvlNode<T>{t->element, clone(t->left, t), clone(t->right, t), parent};
}

template<class T>
int AvlTree<T>::height(AvlNode<T> *t) const
{
    return t == nullptr ? -1 : t->height;
}

template<class T>
void AvlTree<T>::rotateWithLeftChild(AvlNode<T> *&k2)
{
    AvlNode<T> *k1 = k2->left;
    k2->left = k1->right;
    if (k1->right != nullptr) k1->right->parent = k2;
    k1->right = k2;
    k1->parent = k2->parent;
    k2->parent = k1;
    k2->height = std::max(height(k2->left), height(k2->right)) + 1;
    k1->height = std::max(height(k1->left), k2->height) + 1;
    k2 = k1;
}

template<class T>
void AvlTree<T>::rotateWithRightChild(AvlNode<T> *&k1)
{
    AvlNode<T> *k2 = k1->right;
    k1->right = k2->left;
    if (k2->left != nullptr) k2->left->parent = k1;
    k2->left = k1;
    k2->parent = k1->parent;
    k1->parent = k2;
    k1->height = std::max(height(k1->left), height(k1->right)) + 1;
    k2->height = std::max(height(k2->right), k1->height) + 1;
    k1 = k2;
}

template<class T>
void AvlTree<T>::doubleWithLeftChild(AvlNode<T> *&k3)
{
    rotateWithRightChild(k3->left);
    rotateWithLeftChild(k3);
}

template<class T>
void AvlTree<T>::doubleWithRightChild(AvlNode<T> *&k1)
{
    rotateWithLeftChild(k1->right);
    rotateWithRightChild(k1);
}

#endif //AVL_TREE_H
