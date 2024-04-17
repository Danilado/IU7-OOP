#ifndef TEST_OPERATORS_DIFF_HPP
#define TEST_OPERATORS_DIFF_HPP

#include "vector.hpp"
#include <gtest/gtest.h>

TEST(diff, vec_diff) {
  Vector<int> a = {-100, 0, 6};
  Vector<int> b = {200, 4, -5};

  Vector<int> res(a - b);

  int start_a[3] = {-100, 0, 6};
  int expected[3] = {-300, -4, 11};

  size_t i = 0;
  for (auto elem : a)
    EXPECT_EQ(elem, start_a[i++]);

  i = 0;
  for (auto elem : res)
    EXPECT_EQ(elem, expected[i++]);
}

TEST(diff, vec_diff_other_type) {
  Vector<double> a = {-100.5, 0.5, 6.5};
  Vector<int> b = {200, 4, -5};

  Vector<double> res(a - b);

  double start_a[3] = {-100.5, 0.5, 6.5};
  double expected[3] = {-300.5, -3.5, 11.5};

  size_t i = 0;
  for (auto elem : a)
    EXPECT_EQ(elem, start_a[i++]);

  i = 0;
  for (auto elem : res)
    EXPECT_EQ(elem, expected[i++]);
}

TEST(sub, vec_sub_num) {
  Vector<int> a = {-100, 0, 6};
  int k = 10;

  Vector<int> res(a - k);

  int start_a[3] = {-100, 0, 6};
  int expected[3] = {-110, -10, -4};

  size_t i = 0;
  for (auto elem : a)
    EXPECT_EQ(elem, start_a[i++]);

  i = 0;
  for (auto elem : res)
    EXPECT_EQ(elem, expected[i++]);
}

TEST(sub, vec_sub_num_other_type) {
  Vector<int> a = {100, 15, 36};
  size_t k = 10;

  Vector<size_t> res(a - k);

  int start_a[3] = {100, 15, 36};
  size_t expected[3] = {90, 5, 26};

  size_t i = 0;
  for (auto elem : a)
    EXPECT_EQ(elem, start_a[i++]);

  i = 0;
  for (auto elem : res)
    EXPECT_EQ(elem, expected[i++]);
}

TEST(diff, vec_diff_in_place) {
  Vector<int> a = {-100, 0, 6};
  Vector<int> b = {200, 4, -5};

  Vector<int> res(a -= b);

  int expected[3] = {-300, -4, 11};

  size_t i = 0;
  for (auto elem : a)
    EXPECT_EQ(elem, expected[i++]);

  i = 0;
  for (auto elem : res)
    EXPECT_EQ(elem, expected[i++]);
}

TEST(diff, vec_diff_in_place_other_type) {
  Vector<long double> a = {-100.5, 0.5, 6.5};
  Vector<int> b = {200, 4, -5};

  Vector<long double> res(a -= b);

  long double expected[3] = {-300.5, -3.5, 11.5};

  size_t i = 0;
  for (auto elem : a)
    EXPECT_EQ(elem, expected[i++]);

  i = 0;
  for (auto elem : res)
    EXPECT_EQ(elem, expected[i++]);
}

TEST(sub, vec_sub_in_place) {
  Vector<int> a = {-100, 0, 6};
  int k = 10;

  Vector<int> res(a -= k);

  int expected[3] = {-110, -10, -4};

  size_t i = 0;
  for (auto elem : a)
    EXPECT_EQ(elem, expected[i++]);

  i = 0;
  for (auto elem : res)
    EXPECT_EQ(elem, expected[i++]);
}

TEST(sub, vec_sub_in_place_other_type) {
  Vector<size_t> a = {100, 15, 36};
  size_t k = 10;

  Vector<size_t> res(a -= k);

  size_t expected[3] = {90, 5, 26};

  size_t i = 0;
  for (auto elem : a)
    EXPECT_EQ(elem, expected[i++]);

  i = 0;
  for (auto elem : res)
    EXPECT_EQ(elem, expected[i++]);
}

TEST(diff, vec_diff_exception) {
  Vector<int> a = {-100, 0, 6};
  Vector<int> b = {200, 4};

  EXPECT_ANY_THROW(a - b);
}

TEST(diff, vec_diff_in_place_exception) {
  Vector<int> a = {-100, 0, 6};
  Vector<int> b = {200, 4};

  EXPECT_ANY_THROW(a -= b);
}

#endif
