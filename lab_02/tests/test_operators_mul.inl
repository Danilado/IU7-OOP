#ifndef TEST_OPERATORS_MUL_HPP
#define TEST_OPERATORS_MUL_HPP

#include "vector.hpp"
#include <gtest/gtest.h>

TEST(mul, vec_mul_num) {
  Vector<int> a = {-100, 0, 6};
  int k = 10;

  Vector<int> res(a * k);

  int a_start[3] = {-100, 0, 6};
  int expected[3] = {-1000, 0, 60};

  size_t i = 0;
  for (auto elem : a)
    EXPECT_EQ(elem, a_start[i++]);

  i = 0;
  for (auto elem : res)
    EXPECT_EQ(elem, expected[i++]);
}

TEST(mul, vec_mul_num_other_type) {
  Vector<int> a = {100, 15, 36};
  double k = 10.0;

  Vector<double> res(a * k);

  int a_start[3] = {100, 15, 36};
  double expected[3] = {1000.0, 150.0, 360.0};

  size_t i = 0;
  for (auto elem : a)
    EXPECT_EQ(elem, a_start[i++]);

  i = 0;
  for (auto elem : res)
    EXPECT_EQ(elem, expected[i++]);
}

TEST(mul, vec_mul_num_in_place) {
  Vector<int> a = {-100, 0, 6};
  int k = 10;

  Vector<int> res(a *= k);

  int expected[3] = {-1000, 0, 60};

  size_t i = 0;
  for (auto elem : a)
    EXPECT_EQ(elem, expected[i++]);

  i = 0;
  for (auto elem : res)
    EXPECT_EQ(elem, expected[i++]);
}

TEST(mul, vec_mul_num_in_place_other_type) {
  Vector<size_t> a = {100, 15, 36};
  size_t k = 10;

  Vector<size_t> res(a *= k);

  size_t expected[3] = {1000, 150, 360};

  size_t i = 0;
  for (auto elem : a)
    EXPECT_EQ(elem, expected[i++]);

  i = 0;
  for (auto elem : res)
    EXPECT_EQ(elem, expected[i++]);
}

TEST(mul, vec_product) {
  Vector<int> a = {-100, 0, 6};
  Vector<int> b = {200, 4, -5};

  Vector<int> res(a % b);

  int start_a[3] = {-100, 0, 6};
  int start_b[3] = {200, 4, -5};
  int expected[3] = {-24, 700, -400};

  size_t i = 0;
  for (auto elem : a)
    EXPECT_EQ(elem, start_a[i++]);

  i = 0;
  for (auto elem : b)
    EXPECT_EQ(elem, start_b[i++]);

  i = 0;
  for (auto elem : res)
    EXPECT_EQ(elem, expected[i++]);
}

TEST(mul, vec_scalar_mul) {
  Vector<int> a = {-100, 0, 6};
  Vector<int> b = {200, 4, -5};

  int res = a * b;

  int start_a[3] = {-100, 0, 6};
  int start_b[3] = {200, 4, -5};
  int expected = -20030;

  size_t i = 0;
  for (auto elem : a)
    EXPECT_EQ(elem, start_a[i++]);

  i = 0;
  for (auto elem : b)
    EXPECT_EQ(elem, start_b[i++]);

  EXPECT_EQ(res, expected);
}

#endif
