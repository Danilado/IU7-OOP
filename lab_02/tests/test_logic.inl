#ifndef TEST_LOGIC_INL
#define TEST_LOGIC_INL

#include "vector.hpp"
#include <gtest/gtest.h>

TEST(logic, test_eq_int) {
  Vector<int> a({1, 2, 3});
  Vector<int> b({1, 2, 3});

  EXPECT_EQ(a == b, true);
  EXPECT_EQ(a != b, false);
}

TEST(logic, test_eq_dbl) {
  Vector<double> a({1., 2., 3.});
  Vector<double> b({1.0000001, 2.0000001, 3.0000001});

  EXPECT_EQ(a == b, true);
  EXPECT_EQ(a != b, false);
}

TEST(logic, test_ne_int) {
  Vector<int> a({1, 4, 3});
  Vector<int> b({1, 2, 3});

  EXPECT_EQ(a == b, false);
  EXPECT_EQ(a != b, true);
}

TEST(logic, test_ne_dbl) {
  Vector<double> a({1., 2., 3.});
  Vector<double> b({1.0100011, 2.0000001, 3.0000001});

  EXPECT_EQ(a == b, false);
  EXPECT_EQ(a != b, true);
}

TEST(logic, test_eq_self) {
  Vector<double> a({1., 2., 3.});

  EXPECT_EQ(a == a, true);
  EXPECT_EQ(a != a, false);
}

TEST(logic, test_is_zero_int) {
  Vector<int> a({0, 0, 0});

  EXPECT_EQ(a.isZero(), true);
}

TEST(logic, test_is_zero_dbl) {
  Vector<double> a({0.0000001, 0.0000001, 0.0000001});

  EXPECT_EQ(a.isZero(), true);
}

TEST(logic, test_is_zero_dbl_false) {
  Vector<double> a({0.0000011, 0.0000011, 0.0000011});

  EXPECT_EQ(a.isZero(), false);
}

TEST(logic, test_is_unit_int) {
  Vector<int> a({1, 0, 0});

  EXPECT_EQ(a.isUnit(), true);
}

TEST(logic, test_is_unit_double) {
  Vector<double> a({1., 0., 0.});

  EXPECT_EQ(a.isUnit(), true);
}

TEST(logic, test_bool_zero) {
  Vector<int> a({0, 0, 0});

  EXPECT_EQ(bool(a), false);
}

TEST(logic, test_bool_zero_length) {
  Vector<int> a = {};

  EXPECT_DOUBLE_EQ(bool(a), false);
}

#endif