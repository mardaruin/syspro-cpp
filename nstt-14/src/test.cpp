#include "main.hpp"

#include <cstdint>
#include <gtest/gtest.h>
#include <iostream>

int main() {
  alignas(alignof(double)) char buffer[100];
  allocate<100>(buffer, 42, 3.14, 'A');

  int* p_int       = reinterpret_cast<int*>(buffer);
  double* p_double = reinterpret_cast<double*>(p_int + 1);
  char* p_char     = reinterpret_cast<char*>(p_double + 1);

  std::cout << *p_int << ", " << p_double << ", " << p_char << std::endl;

  p_char->~char();
  p_double->~double();
  p_int->~int();
}
