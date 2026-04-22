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

TEST(AVLTreeIteratorTest, EmptyTree) {
  AVLtree<int> tree;

  EXPECT_EQ(tree.begin(), tree.end());

  int cnt = 0;
  for (const auto& node : tree) {
    cnt++;
  }
  EXPECT_EQ(cnt, 0);
}

TEST(AVLTreeIteratorTest, SingleElement) {
  AVLtree<int> tree;
  tree.insert(26);
  EXPECT_NE(tree.begin(), tree.end());
  EXPECT_EQ(*tree.begin(), 26);
  tree.remove(26);
  EXPECT_EQ(tree.begin(), tree.end());
}

TEST(AVLTreeIteratorTest, MulpipleElements) {
  AVLtree<int> tree;
  tree.insert(20);
  tree.insert(26);
  tree.insert(6);
  EXPECT_NE(tree.begin(), tree.end());
  EXPECT_EQ(*tree.begin(), 6);
  AVLtree<int>::Iterator it(tree.begin());
  ++it;
  EXPECT_EQ(*it, 20);
  it++;
  EXPECT_EQ(*it, 26);
  it++;
  EXPECT_EQ(it, tree.end());
}

TEST(AVLTreeIteratorTest, CompareIterators) {
  AVLtree<int> tree;
  tree.insert(20);
  tree.insert(26);
  tree.insert(6);

  AVLtree<int>::Iterator it1(tree.begin());
  AVLtree<int>::Iterator it2(tree.begin());
  EXPECT_TRUE(it1 == it2);
  ++it1;
  EXPECT_TRUE(it1 != it2);
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
