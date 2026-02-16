#include "avl.cpp"
#include <gtest/gtest.h>

TEST(AVLTest, InsertAndSearch) {
  AVLtree tree;
  tree.insert(10);
  tree.insert(20);
  tree.insert(30);
  tree.insert(40);
  tree.insert(50);
  EXPECT_TRUE(tree.search(10));
  EXPECT_FALSE(tree.search(60));
}

TEST(AVLTest, InsertAndRemove) {
  AVLtree tree;
  tree.insert(10);
  tree.insert(20);
  EXPECT_TRUE(tree.search(10));
  tree.remove(10);
  EXPECT_FALSE(tree.search(10));
}
