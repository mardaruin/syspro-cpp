#include "emulator.hpp"

#include "gtest/gtest.h"
#include <cmath>
#include <gtest/gtest.h>
#include <iostream>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <vector>

// pc = if R0 == 0 then pc = x else pc++
TEST(Emulator, JmpzNotZeroTest) {
  std::string test = R"(
      Mov R0 3
      Jmpz 3
      Jmpz 4
      Mov R0 13
      )";
  int result       = Emulator::emulate(test);
  EXPECT_EQ(result, 13);
}

// pc = if R0 == 0 then pc = x else pc++
TEST(Emulator, JmpzZeroTest) {
  std::string test = R"(
      Mov R0 0
      Jmpz 3
      Mov R0 42
      )";
  int result       = Emulator::emulate(test);
  EXPECT_EQ(result, 0);
}

// jumping under inf loop
TEST(Emulator, JmpTest) {
  std::string test = R"(
      Mov R0 3
      Jmp 3
      Jmp 2
      Mov R0 13
      )";
  int result       = Emulator::emulate(test);
  EXPECT_EQ(result, 13);
}

TEST(Emulator, AddTest) {
  std::string test = R"(
      Mov R0 3
      Mov R1 4
      Add R0 R1
      )";
  int result       = Emulator::emulate(test);
  EXPECT_EQ(result, 7);
}

TEST(Emulator, MulTest) {
  std::string test = R"(
      Mov R0 3
      Mov R1 4
      Mul R0 R1
      )";
  int result       = Emulator::emulate(test);
  EXPECT_EQ(result, 12);
}

TEST(Emulator, SubTest) {
  std::string test = R"(
      Mov R0 3
      Mov R1 2
      Sub R0 R1
      )";
  int result       = Emulator::emulate(test);
  EXPECT_EQ(result, 1);
}

TEST(Emulator, DivTest) {
  std::string test = R"(
      Mov R0 48
      Mov R1 4
      Div R0 R1
      )";
  int result       = Emulator::emulate(test);
  EXPECT_EQ(result, 12);
}

TEST(Emulator, LoadTest) {
  std::string test = R"(
      Load R0 42
      )";
  Emulator::EmulatorState state;
  state._mem[42]                                   = 24;
  std::vector<Emulator::Instruction*> instructions = Emulator::parse(test);
  instructions[0]->eval(state);
  EXPECT_EQ(state._registers[Emulator::R0], 24);
}

TEST(Emulator, StoreTest) {
  std::string test = R"(
      Mov R0 24
      Store R0 42
      )";
  Emulator::EmulatorState state;
  std::vector<Emulator::Instruction*> instructions = Emulator::parse(test);
  instructions[0]->eval(state);
  instructions[1]->eval(state);
  EXPECT_EQ(state._mem[42], 24);
}

TEST(Emulator, Expression) {
  std::string test = R"(
      Mov R0 5
      Mov R1 0
      Add R1 1
      Jmpz 7
      Mul R1 R0
      Sub R0 1
      Jmp 3
      Sub R1 10
      Div R1 2
      Mov R0 R1
      )";
  int result       = Emulator::emulate(test);
  EXPECT_EQ(result, 55);
}
