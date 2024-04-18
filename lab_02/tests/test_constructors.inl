#ifndef TEST_CONSTRUCTORS_INL
#define TEST_CONSTRUCTORS_INL

#include "vector.hpp"
#include <gtest/gtest.h>

TEST(constructors, test_empty) {
  Vector<int> a;
  Vector<int> b = {};

  EXPECT_EQ(a.getSize(), 0);
  EXPECT_EQ(b.getSize(), 0);

  EXPECT_EQ(a.isEmpty(), true);
  EXPECT_EQ(b.isEmpty(), true);

  EXPECT_EQ(a.begin(), a.end());
  EXPECT_EQ(b.begin(), b.end());

  EXPECT_ANY_THROW(a[0]);
  EXPECT_ANY_THROW(b[0]);
}

TEST(constructors, test_size) {
  Vector<int> a(3);

  EXPECT_EQ(a.getSize(), 3);

  EXPECT_EQ(a.isEmpty(), false);

  EXPECT_NE(a.begin(), a.end());

  for (size_t i = 0; i < a.getSize(); ++i)
    EXPECT_NO_THROW(a[i]);
}

TEST(constructors, test_size_fill) {
  Vector<int> a(3, 5);

  EXPECT_EQ(a.getSize(), 3);

  EXPECT_EQ(a.isEmpty(), false);

  EXPECT_NE(a.begin(), a.end());

  EXPECT_NO_THROW(a[2]);

  for (size_t i = 0; i < a.getSize(); ++i)
    EXPECT_EQ(a[i], 5);
}

TEST(constructors, test_size_fill_dbl) {
  Vector<double> a(3, 5.);

  EXPECT_EQ(a.getSize(), 3);

  EXPECT_EQ(a.isEmpty(), false);

  EXPECT_NE(a.begin(), a.end());

  EXPECT_NO_THROW(a[2]);

  for (size_t i = 0; i < a.getSize(); ++i)
    EXPECT_DOUBLE_EQ(a[i], 5.);
}

TEST(constructors, test_from_arr) {
  int src[3] = {0, 5, 34};
  Vector<int> a(3, src);

  EXPECT_EQ(a.getSize(), 3);

  EXPECT_EQ(a.isEmpty(), false);

  EXPECT_NE(a.begin(), a.end());

  EXPECT_NO_THROW(a[2]);

  for (size_t i = 0; i < a.getSize(); ++i)
    EXPECT_EQ(a[i], src[i]);
}

TEST(constructors, test_init_list) {
  int expected[3] = {0, 5, 34};
  Vector<int> a({0, 5, 34});

  EXPECT_EQ(a.getSize(), 3);

  EXPECT_EQ(a.isEmpty(), false);

  EXPECT_NE(a.begin(), a.end());

  EXPECT_NO_THROW(a[2]);

  for (size_t i = 0; i < a.getSize(); ++i)
    EXPECT_EQ(a[i], expected[i]);
}

TEST(constructors, test_copy) {
  Vector<int> src({0, 5, 34});
  Vector<int> a(src);

  EXPECT_EQ(a.getSize(), src.getSize());

  EXPECT_EQ(a.isEmpty(), false);

  EXPECT_NE(a.begin(), a.end());

  EXPECT_NO_THROW(a[2]);

  for (size_t i = 0; i < a.getSize(); ++i)
    EXPECT_EQ(a[i], src[i]);
}

TEST(constructors, test_copy_iterator) {
  Vector<int> src({0, 5, 34});
  Vector<int> a(src.begin(), src.end());

  EXPECT_EQ(a.getSize(), src.getSize());

  EXPECT_EQ(a.isEmpty(), false);

  EXPECT_NE(a.begin(), a.end());

  EXPECT_NO_THROW(a[2]);

  for (size_t i = 0; i < a.getSize(); ++i)
    EXPECT_EQ(a[i], src[i]);
}

TEST(constructors, test_move) {
  int expected[3] = {0, 5, 34};
  Vector<int> src(3, expected);
  Vector<int> a(std::move(src));

  EXPECT_EQ(a.getSize(), 3);
  EXPECT_EQ(src.getSize(), 0);

  EXPECT_EQ(a.isEmpty(), false);
  EXPECT_EQ(src.isEmpty(), true);

  EXPECT_NE(a.begin(), a.end());
  EXPECT_EQ(src.begin(), src.end());

  EXPECT_NO_THROW(a[2]);
  EXPECT_ANY_THROW(src[2]);

  for (size_t i = 0; i < a.getSize(); ++i)
    EXPECT_EQ(a[i], expected[i]);
}

#endif