#ifndef _TEST_CONSTRUCTORS_HPP_
#define _TEST_CONSTRUCTORS_HPP_

#include <gtest/gtest.h>
#include <iostream>

#include "Tree.h"

TEST(Contructors, DefaultInt)
{
    Tree<int> tree;
    EXPECT_EQ(tree.IsRootEmpty(), true);
}

TEST(Contructors, InitListInt)
{
    Tree<int> tree = {1, 2, 3, -1};
    int arr[] = {1, -1, 2, 3};
    int i = 0;
    for (auto it = tree.begin(); it != tree.end(); ++it, ++i)
        EXPECT_EQ(*it, arr[i]);

    EXPECT_EQ(i, 4);
}

TEST(Contructors, InitListIntNoEq)
{
    Tree<int> tree{1, 2, 3, -1};
    int arr[] = {1, -1, 2, 3};
    int i = 0;

    for (auto it = tree.begin(); it != tree.end(); ++it, ++i)
        EXPECT_EQ(*it, arr[i]);

    EXPECT_EQ(i, 4);
}

TEST(Contructors, InitListInt_2)
{
    Tree<int> tree = {1, 2, 3, -1};
    int arr[] = {1, -1, 2, 3};
    int i = 0;

    for (auto elem : tree)
    {
        EXPECT_EQ(elem, arr[i]);
        i++;
    }

    EXPECT_EQ(i, 4);
}

TEST(Contructors, InitListInt_Same)
{
    Tree<int> tree = {1, 2, 1, -1, 1, 1};
    int arr[] = {1, -1, 2};
    int i = 0;

    for (auto elem : tree)
    {
        EXPECT_EQ(elem, arr[i]);
        i++;
    }

    EXPECT_EQ(i, 3);
}

TEST(Contructors, Tree)
{
    Tree<int> tree = {1, 2, 3, -1};
    Tree<int> tree_2(tree);
    int arr[] = {1, -1, 2, 3};
    int i = 0;

    for (auto it = tree_2.begin(); it != tree_2.end(); ++it, ++i)
        EXPECT_EQ(*it, arr[i]);

    EXPECT_EQ(i, 4);
}

TEST(Contructors, InitListInt_Iter)
{
    Tree<int> tree = {1, 2, 3, -1};
    Tree<int> tree_2(tree.begin(), tree.end());
    int arr[] = {1, -1, 2, 3};
    int i = 0;

    for (auto elem : tree)
    {
        EXPECT_EQ(elem, arr[i]);
        i++;
    }

    EXPECT_EQ(i, 4);
}

TEST(Contructors, EqToTree)
{
    Tree<int> tree = {1, 2, 3, -1};
    Tree<int> tree_2;
    tree_2 = tree;
    int arr[] = {1, -1, 2, 3};
    int i = 0;

    for (auto it = tree_2.begin(); it != tree_2.end(); ++it, ++i)
        EXPECT_EQ(*it, arr[i]);

    EXPECT_EQ(i, 4);
}

TEST(Contructors, EqToInit)
{
    Tree<int> tree_2;
    tree_2 = {1, 2, 3, -1};
    int arr[] = {1, -1, 2, 3};
    int i = 0;
    for (auto it = tree_2.begin(); it != tree_2.end(); ++it, ++i)
        EXPECT_EQ(*it, arr[i]);

    EXPECT_EQ(i, 4);
}

TEST(Contructors, TwoTreesEq)
{
    Tree<int> tree = {1, 2, 3, -1};
    Tree<int> tree_2;
    tree_2 = tree;

    bool res = tree_2.isEqual(tree);

    EXPECT_EQ(res, true);
}

TEST(Contructors, TwoTreesEq_sign)
{
    Tree<int> tree = {1, 2, 3, -1};
    Tree<int> tree_2;
    tree_2 = tree;

    bool res = tree_2 == tree;

    EXPECT_EQ(res, true);
}

TEST(Contructors, TwoTreesNotEq)
{
    Tree<int> tree = {1, 2, 3, -1};
    Tree<int> tree_2 = {1, 2, 3, -1, -2};

    bool res = tree_2.isNotEqual(tree);

    EXPECT_EQ(res, true);
}

TEST(Contructors, TwoTreesNotEq_sign)
{
    Tree<int> tree = {1, 2, 3, -1};
    Tree<int> tree_2 = {1, 2, 3, -2};

    bool res = tree_2 != tree;

    EXPECT_EQ(res, true);
}

TEST(Contructors, TreeSum)
{
    Tree<int> tree = {1, 2, 3, 4};
    Tree<int> tree_2 = {5, 6, 7};
    Tree<int> tree_3 = {1, 2, 3, 4, 5, 6, 7};

    Tree<int> tree_4 = tree.Add(tree_2);

    int i;

    for (auto it = tree_4.begin(), i = tree_3.begin(); it != tree_4.end(); ++it, ++i)
        EXPECT_EQ(*it, *i);
}

TEST(Contructors, TreeSum_Sign)
{
    Tree<int> tree = {1, 2, 3, 4};
    Tree<int> tree_2 = {5, 6, 7};
    Tree<int> tree_3 = {1, 2, 3, 4, 5, 6, 7};

    Tree<int> tree_4 = tree + tree_2;

    int i;

    for (auto it = tree_4.begin(), i = tree_3.begin(); it != tree_4.end(); ++it, ++i)
        EXPECT_EQ(*it, *i);
}

TEST(Contructors, Find)
{
    Tree<int> tree = {1, 2, 3, -1};
    bool res = tree.Find(0);

    EXPECT_EQ(res, false);
}

TEST(Contructors, Indexator_1)
{
    Tree<int> tree = {1, 2, 3, -1};
    int rootData = tree[0];

    EXPECT_EQ(rootData, 1);
}

TEST(Contructors, Indexator_2)
{
    Tree<int> tree = {1, 2, 3, -1};
    int rootData = tree[1];

    EXPECT_EQ(rootData, -1);
}

TEST(Contructors, Delete)
{
    Tree<int> tree = {1, 2, 4, -1, -2, 0, 3};
    Tree<int> tree_1 = {2, -1, -2, 0, 4, 3};
    bool res = tree.Delete(1);

    EXPECT_EQ(res, true);
    EXPECT_EQ(tree.end() - tree.begin(), 6);

    for (auto it = tree.begin(), i = tree_1.begin(); it != tree.end(); ++it, ++i)
        EXPECT_EQ(*it, *i);
}

TEST(Contructors, Insert)
{
    Tree<int> tree = {};
    Tree<int> tree_1 = {5};

    tree.Insert(5);
    for (auto it = tree.begin(), i = tree_1.begin(); it != tree.end(); ++it, ++i)
        EXPECT_EQ(*it, *i);

}

TEST(Contructors, TreeDiff)
{
    Tree<int> tree = {4, 3, 5, -2, 7};
    Tree<int> tree_1 = {1, 3, 5};
    Tree<int> tree_2 = {4, -2, 7};
    Tree<int> tree_3(tree);
    tree_3 -= tree_1;

    for (auto it = tree_2.begin(), i = tree_3.begin(); it != tree_2.end(); ++it, ++i)
        EXPECT_EQ(*it, *i);
}

TEST(Contructors, Intersection)
{
    Tree<int> tree = {4, 9, 0, 3, 5, -2, 7};
    Tree<int> tree_1 = {1, 3, 5, -7, 9};
    Tree<int> tree_2 = {5, 3, 9};

    tree.Intersection(tree_1);

    for (auto it = tree.begin(), i = tree_2.begin(); it != tree.end(); ++it, ++i) {
        EXPECT_EQ(*it, *i);
    }
}

TEST(Contructors, IntersectionSign)
{
    Tree<int> tree = {4, 9, 0, 3, 5, -2, 7};
    Tree<int> tree_1 = {1, 3, 5, -7, 9};
    Tree<int> tree_2 = {5, 3, 9};

    tree &= tree_1;

    for (auto it = tree.begin(), i = tree_2.begin(); it != tree.end(); ++it, ++i) {
        EXPECT_EQ(*it, *i);
    }
}

TEST(Contructors, Container)
{
    std::vector vec = {1, 2, 3, 4};
    Tree<int> tree(vec);

    EXPECT_EQ(std::distance(tree.begin(), tree.end()), 4);

    int i = 0;
    for (auto elem : tree) {
        EXPECT_EQ(elem, vec[i]);
        ++i;
    }

}

TEST(Contructors, OtherTypeInsert)
{
    Tree<int> tree = {1, 3, 4, 5};
    double insert_data = 2.5;
    Tree<int> res_tree = {1, 3, 2, 4, 5};

    bool res = tree.Insert(insert_data);

    EXPECT_EQ(res, true);

    for (auto it = tree.begin(), i = res_tree.begin(); it != tree.end(); ++it, ++i) {
        EXPECT_EQ(*it, *i);
    }
}

TEST(Contructors, IterIndexation)
{
    Tree<int> tree = {4, 3, 5, -2, 7};

    auto iter = tree.begin();

    EXPECT_EQ(tree[2], iter[2]);

}

TEST(Contructors, CheckDataAccess)
{
    Tree<int> tree = {4, 3, 6, 1};
    int test_node_data = *tree.begin();

    tree = {};

    test_node_data += 1;

    EXPECT_EQ(test_node_data, 5);
}

class A {
public:
    A() = default;
    A(int r) {boba = r;}
    size_t size() const { return boba; }
    A &get() {return *this;}
    void set(int h) {boba = h;}
    bool operator==(const A &bob) const {return (size() == bob.size());}
    bool operator!=(const A &bob) const {return (size() != bob.size());}

    bool operator>(const A &bob) const {return (size() > bob.size());}
    bool operator>=(const A &bob) const {return (size() >= bob.size());}

    bool operator<(const A &bob) const {return (size() < bob.size());}
    bool operator<=(const A &bob) const {return (size() <= bob.size());}
private:
    size_t boba;
};

TEST(Contructors, CheckDataAccess_2_2)
{
    A popter(4);
    Tree<A> tree = {popter, A(3), A(6), A(1)};
    A test_node_data = tree.begin()->get();

    tree = {};

    // test_node_data.set(9);

    EXPECT_EQ(test_node_data.size(), 4);
}

TEST(Contructors, TreeOfStacks)
{
    std::stack<int> stack_1;
    stack_1.push(1);
    std::stack<int> stack_2;
    stack_2.push(2);
    Tree<std::stack<int>> tree = {stack_1, stack_2};

    auto boba = tree.begin()->top();
    // tree.begin()->pop();
    // tree = {};
    boba++;
    EXPECT_EQ(boba, 2);

    EXPECT_EQ(tree[0].top(), 1);
}

#endif
