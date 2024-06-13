// #include <iostream>
#include <gtest/gtest.h>

#include "AVLTree.hpp"
// #include "unit_tests/tests.hpp"

#include <initializer_list>

int main(int argc, char **argv) {
  AVLTree<int> tree = {0, 6};
  AVLTree<double> tree2 = {2.9, 6.9};
  auto res = tree.unionTree(tree2);
  for (const auto &a : res)
    std::cout << a << std::endl;
  return 0;
}
