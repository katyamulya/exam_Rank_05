#include "bigint.hpp"
#include <iostream>

int main()
{
    const bigint a(42);
    bigint b(21), c, d(1337), e(d);

    std::cout << "a = " << a << std::endl;
    std::cout << "b = " << b << std::endl;
    std::cout << "c = " << c << std::endl;
    std::cout << "d = " << d << std::endl;
    std::cout << "e = " << e << std::endl;

    std::cout << "a + b = " << a + b << std::endl;
    std::cout << "(c += a) = " << (c += a) << std::endl;

    std::cout << "b = " << b << std::endl;
    std::cout << "++b = " << ++b << std::endl;
    std::cout << "b++ = " << b++ << std::endl;

    std::cout << "(b << 10) + 42 = " << ((b << 10) + 42) << std::endl;
    std::cout << "(d <<= 4) = " << (d <<= 4) << std::endl;
    std::cout << "(d >>= 2) = " << (d >>= (const bigint)2) << std::endl;

    std::cout << "a =" << a << std::endl;
    std::cout << "d =" << d << std::endl;

    std::cout << "(d < a) = " << (d < a) << std::endl;
    std::cout << "(d <= a) = " << (d <= a) << std::endl;
    std::cout << "(d > a) = " << (d > a) << std::endl;
    std::cout << "(d >= a) = " << (d >= a) << std::endl;
    std::cout << "(d == a) = " << (d == a) << std::endl;
    std::cout << "(d != a) = " << (d != a) << std::endl;

}

// c++ -Wall -Werror -Wextra -std=c++98 main.cpp bigint.cpp
// ./a.out 

/*  RESULTS:

a = 42
b = 21
c = 0				// default constructor works here
d = 1337
e = 1337			// copy constructor works here

a + b = 63
(c += a) = 42

b = 21
++b = 22
b++ = 22

(b << 10) + 42 = 230000000042
(d <<= 4) = 13370000
(d >>= 2) = 133700

a =42
d =133700

(d < a) = 0
(d <= a) = 0
(d > a) = 1
(d >= a) = 1
(d == a) = 0
(d != a) = 1


*/