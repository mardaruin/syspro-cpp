#include <cstdio>
#include <cstring>
#include <iostream>
#include <sys/types.h>

using namespace std;

using false_class = std::integral_constant<bool, false>;
using true_class  = std::integral_constant<bool, true>;

template<int N, int D>
struct is_prime_helper: std::conditional_t<(N % D == 0), false_class, is_prime_helper<N, D - 1>> {};

template<int N>
struct is_prime_helper<N, 1>: std::integral_constant<bool, true_class::value> {};

template<int N>
struct is_prime: is_prime_helper<N, N - 1> {};

template<>
struct is_prime<0>: std::integral_constant<bool, false_class::value> {};

template<>
struct is_prime<1>: std::integral_constant<bool, false_class::value> {};

template<>
struct is_prime<2>: std::integral_constant<bool, true_class::value> {};

template<>
struct is_prime<3>: std::integral_constant<bool, true_class::value> {};

template<int N>
struct next_prime: std::integral_constant<int,
                                          std::conditional_t<is_prime<N + 1>::value,
                                                             std::integral_constant<int, N + 1>,
                                                             next_prime<N + 1>>::value> {};

template<int N>
struct nth_prime: std::integral_constant<int, next_prime<nth_prime<N - 1>::value>::value> {};

template<>
struct nth_prime<1>: std::integral_constant<int, 2> {};

template<>
struct nth_prime<2>: std::integral_constant<int, 3> {};
