#ifndef TEST_OPERATORS_DIFF_HPP
#define TEST_OPERATORS_DIFF_HPP

#include "vector.hpp"
#include <gtest/gtest.h>

TEST(diff, vec_diff) {
  Vector<int> a = {-1, 2, 3};
  Vector<int> b = {4, 5, -6};

  Vector<int> res(a - b);

  int start_a[3] = {-1, 2, 3};
  int expected[3] = {-5, -3, 9};

  size_t i = 0;
  for (auto elem : a)
    EXPECT_EQ(elem, start_a[i++]);

  i = 0;
  for (auto elem : res)
    EXPECT_EQ(elem, expected[i++]);
}

TEST(diff, vec_diff_other_type) {
  Vector<double> a = {-1.5, 2.5, 3.5};
  Vector<int> b = {4, 5, -6};

  Vector<double> res(a - b);

  double start_a[3] = {-1.5, 2.5, 3.5};
  double expected[3] = {-5.5, -2.5, 9.5};

  size_t i = 0;
  for (auto elem : a)
    EXPECT_EQ(elem, start_a[i++]);

  i = 0;
  for (auto elem : res)
    EXPECT_EQ(elem, expected[i++]);
}

TEST(sub, vec_sub_num) {
  Vector<int> a = {-1, 2, 3};
  int k = 10;

  Vector<int> res(a - k);

  int start_a[3] = {-1, 2, 3};
  int expected[3] = {-11, -8, -7};

  size_t i = 0;
  for (auto elem : a)
    EXPECT_EQ(elem, start_a[i++]);

  i = 0;
  for (auto elem : res)
    EXPECT_EQ(elem, expected[i++]);
}

TEST(sub, vec_sub_num_other_type) {
  Vector<int> a = {11, 12, 13};
  size_t k = 10;

  Vector<size_t> res(a - k);

  int start_a[3] = {11, 12, 13};
  size_t expected[3] = {1, 2, 3};

  size_t i = 0;
  for (auto elem : a)
    EXPECT_EQ(elem, start_a[i++]);

  i = 0;
  for (auto elem : res)
    EXPECT_EQ(elem, expected[i++]);
}

TEST(diff, vec_diff_in_place) {
  Vector<int> a = {-1, 2, 3};
  Vector<int> b = {4, 5, -6};

  Vector<int> res(a -= b);

  int expected[3] = {-5, -3, 9};

  size_t i = 0;
  for (auto elem : a)
    EXPECT_EQ(elem, expected[i++]);

  i = 0;
  for (auto elem : res)
    EXPECT_EQ(elem, expected[i++]);
}

TEST(diff, vec_diff_in_place_other_type) {
  Vector<long double> a = {-1.5, 2.5, 3.5};
  Vector<int> b = {4, 5, -6};

  Vector<long double> res(a -= b);

  long double expected[3] = {-5.5, -2.5, 9.5};

  size_t i = 0;
  for (auto elem : a)
    EXPECT_EQ(elem, expected[i++]);

  i = 0;
  for (auto elem : res)
    EXPECT_EQ(elem, expected[i++]);
}

TEST(sub, vec_sub_in_place) {
  Vector<int> a = {-1, 2, 3};
  int k = 10;

  Vector<int> res(a -= k);

  int expected[3] = {-11, -8, -7};

  size_t i = 0;
  for (auto elem : a)
    EXPECT_EQ(elem, expected[i++]);

  i = 0;
  for (auto elem : res)
    EXPECT_EQ(elem, expected[i++]);
}

TEST(sub, vec_sub_in_place_other_type) {
  Vector<size_t> a = {11, 12, 13};
  size_t k = 10;

  Vector<size_t> res(a -= k);

  size_t expected[3] = {1, 2, 3};

  size_t i = 0;
  for (auto elem : a)
    EXPECT_EQ(elem, expected[i++]);

  i = 0;
  for (auto elem : res)
    EXPECT_EQ(elem, expected[i++]);
}

TEST(diff, vec_diff_exception) {
  Vector<int> a = {-1, 2, 3};
  Vector<int> b = {4, 5};

  EXPECT_ANY_THROW(a - b);
}

TEST(diff, vec_diff_in_place_exception) {
  Vector<int> a = {-1, 2, 3};
  Vector<int> b = {4, 5};

  EXPECT_ANY_THROW(a -= b);
}

#endif
