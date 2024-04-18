#ifndef TEST_INDEXATION_INL
#define TEST_INDEXATION_INL

#include "vector.hpp"
#include <gtest/gtest.h>

TEST(indexation, test_iterate_through) {
  Vector<double> a({1., 2., 3., 4., 5.});
  Vector<double> b({.5, 1., 1.5, 2., 2.5});

  for (size_t i = 0; i < a.getSize(); ++i)
    EXPECT_DOUBLE_EQ(a[i] / 2., b[i]);

  size_t i = 10;

  EXPECT_ANY_THROW(a[i]);
}

TEST(indexation, test_const_indexes) {
  Vector<double> a({1., 2., 3., 4., 5.});

  EXPECT_DOUBLE_EQ(a[0], 1.);
  EXPECT_DOUBLE_EQ(a[1], 2.);
  EXPECT_DOUBLE_EQ(a[2], 3.);
  EXPECT_DOUBLE_EQ(a[3], 4.);
  EXPECT_DOUBLE_EQ(a[4], 5.);

  EXPECT_ANY_THROW(a[5]);
}

#endif