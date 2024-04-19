#ifndef TEST_FUNCTIONS_INL
#define TEST_FUNCTIONS_INL

#include "vector.hpp"
#include <gtest/gtest.h>

TEST(funcs, test_vec_length_int) {
  Vector<int> a({1, 2, 3});

  EXPECT_EQ(a.length(), sqrt(14));
}

TEST(funcs, test_vec_length_dbl) {
  Vector<double> a({1., -2., 3.});

  EXPECT_EQ(a.length(), sqrt(14.));
}

TEST(funcs, test_unit) {
  Vector<double> a({1., -2., 3.});
  double expected[3] = {1. / sqrt(14.), -2. / sqrt(14.), 3. / sqrt(14.)};

  Vector<double> res(a.getUnit<double>());

  for (size_t i = 0; i < a.getSize(); ++i)
    EXPECT_DOUBLE_EQ(res[i], expected[i]);
}

TEST(unary, neg) {
  double src[3] = {1., 2., 3.};
  Vector<double> a(3, src);

  for (size_t i = 0; i < a.getSize(); ++i)
    a[i] = -a[i];

  for (size_t i = 0; i < a.getSize(); ++i)
    EXPECT_DOUBLE_EQ(a[i], -src[i]);
}

#endif