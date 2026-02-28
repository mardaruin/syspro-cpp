#include "avl.hpp"

#include <gtest/gtest.h>

TEST(AVLTest, InsertAndSearch) {
  AVLtree tree;
  tree.insert(10);
  tree.insert(20);
  tree.insert(30);
  EXPECT_TRUE(tree.search(10));
  //EXPECT_FALSE(tree.search(20));
}

TEST(AVLTest, InsertAndRemove) {
  AVLtree tree;
  tree.insert(10);
  tree.insert(20);
  EXPECT_TRUE(tree.search(10));
  tree.remove(10);
  EXPECT_FALSE(tree.search(10));
}

TEST(AVLTest, CopyConstructor) {
  AVLtree original_tree;
  original_tree.insert(10);
  original_tree.insert(20);
  original_tree.insert(30);

  AVLtree copied_tree(original_tree);

  EXPECT_TRUE(copied_tree.search(10));
  EXPECT_TRUE(copied_tree.search(20));
  EXPECT_TRUE(copied_tree.search(30));

  copied_tree.remove(30);
  EXPECT_TRUE(original_tree.search(20));
}

TEST(AVLTest, AssignmentOperator) {
  AVLtree original_tree;
  AVLtree copied_tree;
  copied_tree.insert(10);
  copied_tree.insert(20);
  copied_tree.insert(30);

  original_tree = copied_tree;

  copied_tree.remove(20);
  EXPECT_TRUE(original_tree.search(20));
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
