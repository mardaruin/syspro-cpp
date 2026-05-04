#include "main.hpp"

#include <cstdint>
#include <gtest/gtest.h>

TEST(VariadicTemplates, BasicEvenFunc) {
  auto isEven = [](int n) { return n % 2 == 0; };
  //std::cout << getIndexOfFirstMatch(isEven, 3, 15, 1, 2, 4) << std::endl;
  EXPECT_EQ(3, getIndexOfFirstMatch(isEven, 3, 15, 1, 2, 4, 7));
  EXPECT_EQ(0, getIndexOfFirstMatch(isEven, 2, 15, 1, 2, 4, 7));
  EXPECT_EQ(-1, getIndexOfFirstMatch(isEven, 3, 15, 1, 5, 5, 7));
}
