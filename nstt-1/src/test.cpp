#include "avl.hpp"

#include <gtest/gtest.h>

TEST(AVLTest, InsertAndSearch) {
  AVLtree<int> tree;
  tree.insert(10);
  tree.insert(20);
  tree.insert(30);
  EXPECT_TRUE(tree.search(10));
  //EXPECT_FALSE(tree.search(20));
}

TEST(AVLTest, InsertAndRemove) {
  AVLtree<int> tree;
  tree.insert(10);
  tree.insert(20);
  EXPECT_TRUE(tree.search(10));
  tree.remove(10);
  EXPECT_FALSE(tree.search(10));
}

TEST(AVLTest, CopyConstructor) {
  AVLtree<int> original_tree;
  original_tree.insert(10);
  original_tree.insert(20);
  original_tree.insert(30);

  AVLtree<int> copied_tree(original_tree);

  EXPECT_TRUE(copied_tree.search(10));
  EXPECT_TRUE(copied_tree.search(20));
  EXPECT_TRUE(copied_tree.search(30));

  copied_tree.remove(30);
  EXPECT_TRUE(original_tree.search(20));
}

TEST(AVLTest, AssignmentOperator) {
  AVLtree<int> original_tree;
  AVLtree<int> copied_tree;
  copied_tree.insert(10);
  copied_tree.insert(20);
  copied_tree.insert(30);

  original_tree = copied_tree;

  copied_tree.remove(20);
  EXPECT_TRUE(original_tree.search(20));
}

TEST(AVLTest, MoveConstructor) {
  AVLtree<int> original_tree;
  original_tree.insert(10);
  original_tree.insert(20);
  original_tree.insert(30);

  AVLtree<int> moved_tree(std::move(original_tree));

  EXPECT_TRUE(moved_tree.search(10));
  EXPECT_TRUE(moved_tree.search(20));
  EXPECT_TRUE(moved_tree.search(30));

  EXPECT_FALSE(original_tree.search(10));
  EXPECT_FALSE(original_tree.search(20));
  EXPECT_FALSE(original_tree.search(30));
}

TEST(AVLTest, MoveOperator) {
  AVLtree<int> original_tree;
  original_tree.insert(10);
  original_tree.insert(20);
  original_tree.insert(30);

  AVLtree<int> moved_tree;
  moved_tree = std::move(original_tree);

  EXPECT_TRUE(moved_tree.search(10));
  EXPECT_TRUE(moved_tree.search(20));
  EXPECT_TRUE(moved_tree.search(30));

  EXPECT_FALSE(original_tree.search(10));
  EXPECT_FALSE(original_tree.search(20));
  EXPECT_FALSE(original_tree.search(30));
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
