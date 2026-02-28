#include "main.hpp"

#include <gtest/gtest.h>

bool almostEqual(const Point& p1, const Point& p2) {
  static constexpr double EPSILON = numeric_limits<double>::epsilon() * 100;
  return abs(p1.x - p2.x) <= EPSILON && abs(p1.y - p2.y) <= EPSILON;
}

TEST(LineTest, IntersectionNormalCase) {
  Line l1(Point(0, 0), Point(1, 1));
  Line l2(Point(1, 0), Point(0, 1));
  auto result = l1.intersect(l2);
  ASSERT_TRUE(result.second);
  EXPECT_TRUE(almostEqual(result.first, Point(0.5, 0.5)));
}

TEST(LineTest, VerticalHorizontalIntersection) {
  Line horizontal(Point(0, 1), Point(1, 1));
  Line vertical(Point(1, 0), Point(1, 2));
  auto result = horizontal.intersect(vertical);
  ASSERT_TRUE(result.second);
  EXPECT_TRUE(almostEqual(result.first, Point(1, 1)));
}

TEST(LineTest, ParalllLines) {
  Line l1(Point(0, 0), Point(1, 1));
  Line l2(Point(1, 1), Point(2, 2));
  auto result = l1.intersect(l2);
  ASSERT_FALSE(result.second);
}

TEST(LineTest, PerpendicularToNormalLine) {
  Line original(Point(0, 0), Point(1, 1));
  Line perp = original.perpendicular(Point(0, 0), original);
  EXPECT_EQ(perp.getA(), -1.0);
  EXPECT_EQ(perp.getB(), 1.0);
  EXPECT_EQ(perp.getC(), 0.0);
}

TEST(LineTest, PerpendicularToHorizontalLine) {
  Line horizontal(Point(0, 1), Point(1, 1));
  Line perp = horizontal.perpendicular(Point(0, 1), horizontal);
  EXPECT_EQ(perp.getA(), -1.0);
  EXPECT_EQ(perp.getB(), 0.0);
  EXPECT_EQ(perp.getC(), 0.0);
}

TEST(LineTest, PerpendicularToVerticalLine) {
  Line vertical(Point(1, 0), Point(1, 1));
  Line perp = vertical.perpendicular(Point(1, 0), vertical);
  EXPECT_EQ(perp.getA(), 0.0);
  EXPECT_EQ(perp.getB(), -1.0);
  EXPECT_EQ(perp.getC(), 0.0);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
