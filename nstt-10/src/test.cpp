#include "main.hpp"

#include <gtest/gtest.h>

class LimitedPair: public InstanceLimiter<LimitedPair, 2> {
public:
  LimitedPair() = default;
};

class Singleton: public InstanceLimiter<Singleton, 1> {
public:
  Singleton() = default;
};

TEST(InstanceLimiter, SingletonTest) {
  EXPECT_NO_THROW({
    Singleton S1;

    EXPECT_THROW({ Singleton S2; }, std::runtime_error);
  });
}

TEST(InstanceLimiter, LimitedPairTest) {
  EXPECT_NO_THROW({
    LimitedPair P1;
    LimitedPair P2;

    EXPECT_THROW({ LimitedPair P3; }, std::runtime_error);
  });
}
