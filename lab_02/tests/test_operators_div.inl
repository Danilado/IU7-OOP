#ifndef TEST_OPERATORS_DIV_HPP
#define TEST_OPERATORS_DIV_HPP

#include "vector.hpp"
#include <gtest/gtest.h>

TEST(div, vec_div) {
  Vector<int> a = {-100, 0, 6};
  int k = 10;

  Vector<int> res(a / k);

  int a_start[3] = {-100, 0, 6};
  int expected[3] = {-10, 0, 0};

  size_t i = 0;
  for (auto elem : a)
    EXPECT_EQ(elem, a_start[i++]);

  i = 0;
  for (auto elem : res)
    EXPECT_EQ(elem, expected[i++]);
}

TEST(div, vec_div_other_type) {
  Vector<int> a = {100, 15, 36};
  double k = 10.0;

  Vector<double> res(a / k);

  int a_start[3] = {100, 15, 36};
  double expected[3] = {10.0, 1.5, 3.6};

  size_t i = 0;
  for (auto elem : a)
    EXPECT_EQ(elem, a_start[i++]);

  i = 0;
  for (auto elem : res)
    EXPECT_EQ(elem, expected[i++]);
}

TEST(div, vec_div_in_place) {
  Vector<int> a = {-100, 0, 6};
  int k = 10;

  Vector<int> res(a /= k);

  int expected[3] = {-10, 0, 0};

  size_t i = 0;
  for (auto elem : a)
    EXPECT_EQ(elem, expected[i++]);

  i = 0;
  for (auto elem : res)
    EXPECT_EQ(elem, expected[i++]);
}

TEST(div, vec_div_in_place_other_type) {
  Vector<long long int> a = {100, 15, 36};
  long long int k = 10;

  Vector<long long int> res(a /= k);

  long long int expected[3] = {10, 1, 3};

  size_t i = 0;
  for (auto elem : a)
    EXPECT_EQ(elem, expected[i++]);

  i = 0;
  for (auto elem : res)
    EXPECT_EQ(elem, expected[i++]);
}

TEST(div, vec_div_zero_division_dbl) {
  Vector<double> a = {-100.5, 0.0000001, 6.7};
  double k = 0.0;

  EXPECT_ANY_THROW(a / k);
}

TEST(div, vec_div_zero_division_int) {
  Vector<int> a = {-100, 0, 6};
  int k = 0;

  EXPECT_ANY_THROW(a /= k);
}

#endif
