#include "iterator.hpp"
#include "vector.hpp"

#include <gtest/gtest.h>

int main(int argc, char *argv[]) {
#ifdef LANG_RU
  setlocale(LC_CTYPE, "Russian");
#endif

  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
