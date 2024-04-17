#ifndef TEST_OPERATORS_ADD_HPP
#define TEST_OPERATORS_ADD_HPP

#include "vector.hpp"
#include <gtest/gtest.h>

TEST(sum, vec_sum) {
  Vector<int> a = {-100, 0, 6};
  Vector<int> b = {200, 4, -5};

  Vector<int> res(a + b);

  int a_start[3] = {-100, 0, 6};
  int expected[3] = {100, 4, 1};

  size_t i = 0;
  for (auto elem : a)
    EXPECT_EQ(elem, a_start[i++]);

  i = 0;
  for (auto elem : res)
    EXPECT_EQ(elem, expected[i++]);
}

TEST(sum, vec_sum_multi_type) {
  Vector<double> a = {-100.5, 0.5, 6.5};
  Vector<int> b = {200, 4, -5};

  Vector<double> res(a + b);

  double a_start[3] = {-100.5, 0.5, 6.5};
  double expected[3] = {99.5, 4.5, 1.5};

  size_t i = 0;
  for (auto elem : a)
    EXPECT_EQ(elem, a_start[i++]);

  i = 0;
  for (auto elem : res)
    EXPECT_EQ(elem, expected[i++]);
}

TEST(sum, vec_sum_in_place) {
  Vector<int> a = {-100, 0, 6};
  Vector<int> b = {200, 4, -5};

  Vector<int> res(a += b);

  int expected[3] = {100, 4, 1};

  size_t i = 0;
  for (auto elem : a)
    EXPECT_EQ(elem, expected[i++]);

  i = 0;
  for (auto elem : res)
    EXPECT_EQ(elem, expected[i++]);
}

TEST(sum, vec_sum_in_place_multi_type) {
  Vector<double> a = {-100.5, 0.5, 6.5};
  Vector<long long int> b = {200, 4, -5};

  Vector<double> res(a += b);

  double expected[3] = {99.5, 4.5, 1.5};

  size_t i = 0;
  for (auto elem : a)
    EXPECT_EQ(elem, expected[i++]);

  i = 0;
  for (auto elem : res)
    EXPECT_EQ(elem, expected[i++]);
}

TEST(add, num_add) {
  Vector<int> a = {-100, 0, 6};
  int k = 10;

  Vector<int> res(a + k);

  int a_start[3] = {-100, 0, 6};
  int expected[3] = {-90, 10, 16};

  size_t i = 0;
  for (auto elem : a)
    EXPECT_EQ(elem, a_start[i++]);

  i = 0;
  for (auto elem : res)
    EXPECT_EQ(elem, expected[i++]);
}

TEST(add, add_num_other_type) {
  Vector<double> a = {-100.5, 0.5, 6.5};
  int k = 10;

  Vector<double> res(a + k);

  double a_start[3] = {-100.5, 0.5, 6.5};
  double expected[3] = {-90.5, 10.5, 16.5};

  size_t i = 0;
  for (auto elem : a)
    EXPECT_EQ(elem, a_start[i++]);

  i = 0;
  for (auto elem : res)
    EXPECT_EQ(elem, expected[i++]);
}

TEST(add, add_num_in_place) {
  Vector<int> a = {-100, 0, 6};
  int k = 10;

  Vector<int> res(a += k);

  int expected[3] = {-90, 10, 16};

  size_t i = 0;
  for (auto elem : a)
    EXPECT_EQ(elem, expected[i++]);

  i = 0;
  for (auto elem : res)
    EXPECT_EQ(elem, expected[i++]);
}

TEST(add, add_num_in_place_other_type) {
  Vector<double> a = {-100.5, 0.5, 6.5};
  int k = 10;

  Vector<double> res(a += k);

  double expected[3] = {-90.5, 10.5, 16.5};

  size_t i = 0;
  for (auto elem : a)
    EXPECT_EQ(elem, expected[i++]);

  i = 0;
  for (auto elem : res)
    EXPECT_EQ(elem, expected[i++]);
}

TEST(sum, vec_sum_exception) {
  Vector<int> a = {-100, 0, 6};
  Vector<int> b = {200, 4};

  EXPECT_ANY_THROW(a + b);
}

TEST(sum, vec_sum_in_place_exception) {
  Vector<int> a = {-100, 0, 6};
  Vector<int> b = {200, 4};

  EXPECT_ANY_THROW(a += b);
}

#endif
