#ifndef TEST_OPERATORS_ADD_HPP
#define TEST_OPERATORS_ADD_HPP

#include "vector.hpp"
#include <gtest/gtest.h>

TEST(sum, vec_sum) {
  Vector<int> a = {-1, 2, 3};
  Vector<int> b = {4, 5, -6};

  Vector<int> res(a + b);

  int a_start[3] = {-1, 2, 3};
  int expected[3] = {3, 7, -3};

  size_t i = 0;
  for (auto elem : a)
    EXPECT_EQ(elem, a_start[i++]);

  i = 0;
  for (auto elem : res)
    EXPECT_EQ(elem, expected[i++]);
}

TEST(sum, vec_sum_multi_type) {
  Vector<double> a = {-1.5, 2.5, 3.5};
  Vector<int> b = {4, 5, -6};

  Vector<double> res(a + b);

  double a_start[3] = {-1.5, 2.5, 3.5};
  double expected[3] = {2.5, 7.5, -2.5};

  size_t i = 0;
  for (auto elem : a)
    EXPECT_EQ(elem, a_start[i++]);

  i = 0;
  for (auto elem : res)
    EXPECT_EQ(elem, expected[i++]);
}

TEST(sum, vec_sum_in_place) {
  Vector<int> a = {-1, 2, 3};
  Vector<int> b = {4, 6, -6};

  Vector<int> res(a += b);

  int expected[3] = {3, 8, -3};

  size_t i = 0;
  for (auto elem : a)
    EXPECT_EQ(elem, expected[i++]);

  i = 0;
  for (auto elem : res)
    EXPECT_EQ(elem, expected[i++]);
}

TEST(sum, vec_sum_in_place_multi_type) {
  Vector<double> a = {-1.5, 2.5, 3.5};
  Vector<long long int> b = {4, 5, -6};

  Vector<double> res(a += b);

  double expected[3] = {2.5, 7.5, -2.5};

  size_t i = 0;
  for (auto elem : a)
    EXPECT_EQ(elem, expected[i++]);

  i = 0;
  for (auto elem : res)
    EXPECT_EQ(elem, expected[i++]);
}

TEST(add, num_add) {
  Vector<int> a = {-1, 2, 3};
  int k = 10;

  Vector<int> res(a + k);

  int a_start[3] = {-1, 2, 3};
  int expected[3] = {9, 12, 13};

  size_t i = 0;
  for (auto elem : a)
    EXPECT_EQ(elem, a_start[i++]);

  i = 0;
  for (auto elem : res)
    EXPECT_EQ(elem, expected[i++]);
}

TEST(add, add_num_other_type) {
  Vector<double> a = {-1.5, 2.5, 3.5};
  int k = 10;

  Vector<double> res(a + k);

  double a_start[3] = {-1.5, 2.5, 3.5};
  double expected[3] = {8.5, 12.5, 13.5};

  size_t i = 0;
  for (auto elem : a)
    EXPECT_EQ(elem, a_start[i++]);

  i = 0;
  for (auto elem : res)
    EXPECT_EQ(elem, expected[i++]);
}

TEST(add, add_num_in_place) {
  Vector<int> a = {-1, 2, 3};
  int k = 10;

  Vector<int> res(a += k);

  int expected[3] = {9, 12, 13};

  size_t i = 0;
  for (auto elem : a)
    EXPECT_EQ(elem, expected[i++]);

  i = 0;
  for (auto elem : res)
    EXPECT_EQ(elem, expected[i++]);
}

TEST(add, add_num_in_place_other_type) {
  Vector<double> a = {-1.5, 2.5, 3.5};
  int k = 10;

  Vector<double> res(a += k);

  double expected[3] = {8.5, 12.5, 13.5};

  size_t i = 0;
  for (auto elem : a)
    EXPECT_EQ(elem, expected[i++]);

  i = 0;
  for (auto elem : res)
    EXPECT_EQ(elem, expected[i++]);
}

TEST(sum, vec_sum_exception) {
  Vector<int> a = {-1, 2, 3};
  Vector<int> b = {4, 5};

  EXPECT_ANY_THROW(a + b);
}

TEST(sum, vec_sum_in_place_exception) {
  Vector<int> a = {-1, 2, 3};
  Vector<int> b = {4, 5};

  EXPECT_ANY_THROW(a += b);
}

#endif
