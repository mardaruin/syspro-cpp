#include "main.hpp"

#include <cstdint>
#include <gtest/gtest.h>

int main() {
  std::cout << nth_prime<100>::type::value << std::endl;
}
