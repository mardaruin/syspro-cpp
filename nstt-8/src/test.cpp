#include "main.hpp"

#include <cstdint>
#include <gtest/gtest.h>

TEST(IOTest, InitialState) {
  StringIO io;
  EXPECT_TRUE(io.is_opened());
  EXPECT_FALSE(io.is_eof_reached());
}

TEST(IOTest, CloseMethod) {
  StringIO io;
  io.close();
  EXPECT_FALSE(io.is_opened());
  EXPECT_TRUE(io.is_eof_reached());
}

TEST(StringIO, ReadAndWritePrimitives) {
  StringIO io;

  int32_t num = 1234;
  float flt   = 12.34f;
  char ch     = 'a';

  io.write(num);
  io.write(flt);
  io.write(ch);

  io.reset();

  EXPECT_EQ(io.read<int32_t>(), num);
  EXPECT_FLOAT_EQ(io.read<float>(), flt);
  EXPECT_EQ(io.read<char>(), ch);
}

TEST(StringIO, ReadAndWriteString) {
  StringIO io;
  std::string str = "Why are you even looking here?";
  io.write_string(str);
  io.reset();
  EXPECT_EQ(io.read_string(), str);
}

TEST(FileIO, ReadAndWriteToFile) {
  const char* filename = "test_file.bin";
  int32_t num          = 5678;
  std::string str      = "Привет! Испугался? не бойся!!";
  {
    FileIO file_writer(filename, "wb");


    file_writer.write(num);
    file_writer.write_string(str);
  }
  {
    FileIO file_reader(filename, "rb");

    EXPECT_EQ(file_reader.read<int32_t>(), num);
    EXPECT_EQ(file_reader.read_string(), str);

    EXPECT_FALSE(file_reader.is_eof_reached());

    char ch = file_reader.read<char>();

    EXPECT_TRUE(file_reader.is_eof_reached());
  }
}
