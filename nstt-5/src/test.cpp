#include "main.hpp"

#include <gtest/gtest.h>

struct TestObject {
  int value      = 0;
  bool destroyed = false;

  TestObject(int val):
      value(val) {}

  ~TestObject() {
    destroyed = true;
  }
};

TEST(ScopedPointer, DeepCopy) {
  TestObject obj(42);
  ScopedPointerDeepCopy<TestObject> op(&obj);
  EXPECT_TRUE(op.get().value == 42 && !op.get().destroyed);

  ScopedPointerDeepCopy<TestObject> copy(op);
  EXPECT_TRUE(copy.get().value == 42 && !copy.get().destroyed);

  op.get().value = 13;
  EXPECT_TRUE(op.get().value == 13 && copy.get().value == 42);

  ScopedPointerDeepCopy<TestObject> op_assign(nullptr);
  op_assign = op;
  EXPECT_TRUE(op_assign.get().value == 13 && !op_assign.get().destroyed);

  ScopedPointerDeepCopy<TestObject> op_move(std::move(op));
  EXPECT_TRUE(op_move.get().value == 13 && !op_move.get().destroyed);
}

TEST(ScopedPointer, Transferring) {
  TestObject obj(42);
  ScopedPointerTransferring<TestObject> op(&obj);
  EXPECT_TRUE(op.get().value == 42 && !op.get().destroyed);

  ScopedPointerTransferring<TestObject> op_move(std::move(op));
  EXPECT_TRUE(op_move.get().value == 42 && !op_move.get().destroyed);
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
