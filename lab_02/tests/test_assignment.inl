#ifndef TEST_ASSIGNMENT_INL
#define TEST_ASSIGNMENT_INL

#include "vector.hpp"
#include <gtest/gtest.h>
#include <ranges>

TEST(assignment, test_assign_init_list) {
  int expected[5] = {1, 2, 3, 4, 5};
  Vector<int> a;
  a = {1, 2, 3, 4, 5};

  for (size_t i : expected | std::views::filter([](int i) { return i >= 0; }) |
                      std::views::take(5))
    EXPECT_EQ(expected[i - 1], a[i - 1]);
}

TEST(assignment, test_assign_copy) {
  int expected[5] = {1, 2, 3, 4, 5};
  Vector<int> a;
  Vector<int> b(5, expected);

  a = b;

  EXPECT_EQ(b.getSize(), 5);
  EXPECT_EQ(a.getSize(), b.getSize());
  EXPECT_EQ(a.isEmpty(), false);
  EXPECT_EQ(b.isEmpty(), false);

  for (size_t i : expected | std::views::filter([](int i) { return i >= 0; }) |
                      std::views::take(5))
    EXPECT_EQ(b[i - 1], a[i - 1]);
}

TEST(assignment, test_assign_move) {
  int expected[5] = {1, 2, 3, 4, 5};
  Vector<int> a;
  Vector<int> b(5, expected);

  a = std::move(b);

  EXPECT_EQ(b.getSize(), 0);
  EXPECT_EQ(b.isEmpty(), true);

  for (size_t i : expected | std::views::filter([](int i) { return i >= 0; }) |
                      std::views::take(5))
    EXPECT_EQ(expected[i - 1], a[i - 1]);
}

#endif