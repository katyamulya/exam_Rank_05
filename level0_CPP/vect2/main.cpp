#include "vect2.hpp"
#include <iostream>

// c++ -Wall -Werror -Wextra -std=c++98 main.cpp vect2.cpp


int main()
{
    vect2 v1; // 0, 0
    vect2 v2(1, 2); // 1, 2
    const vect2 v3(v2); // 1, 2
    vect2 v4 = v2; // 1, 2

    std::cout << "v1: " << v1 << std::endl;
    std::cout << "v1: " << "{" << v1[0] << ", " << v1[1] << "}" << std::endl;
    std::cout << "v2: " << v2 << std::endl;
    std::cout << "v3: " << v3 << std::endl;
    std::cout << "v4: " << v4 << std::endl;
    std::cout << v4++ << std::endl; // 2, 3
    std::cout << ++v4 << std::endl; // 3, 4
    std::cout << v4-- << std::endl; // 2, 3
    std::cout << --v4 << std::endl; // 1, 2
    v2 += v3; // 2, 4
    v1 -= v2; // -2, -4
    v2 = v3 + v3 *2; // 3, 6
    v2 = 3 * v2; // 9, 18
    v2 += v2 += v3; // 20, 40    // v2.operator+=( v2.operator+=(v3) );
    v1 *= 42; // -84, -168
    v1 = v1 - v1 +v1;
    std::cout << "v1: " << v1 << std::endl;
    std::cout << "v2: " << v2 << std::endl;
    std::cout << "-v2: " << -v2 << std::endl;
    std::cout << "v1[1]: " << v1[1] << std::endl;
    v1[1] = 12;
    std::cout << "v1[1]: " << v1[1] << std::endl;
    std::cout << "v3[1]: " << v3[1] << std::endl;
    std::cout << "v1 == v3: " << (v1 == v3) << std::endl;
    std::cout << "v1 == v1: " << (v1 == v1) << std::endl;
    std::cout << "v1 != v3: " << (v1 != v3) << std::endl;
    std::cout << "v1 != v1: " << (v1 != v1) << std::endl;
}

/* Results:

v1: {0, 0}
v1: {0, 0}
v2: {1, 2}
v3: {1, 2}
v4: {1, 2}
{1, 2}
{3, 4}
{3, 4}
{1, 2}
v1: {-84, -168}
v2: {20, 40}
-v2: {-20, -40}
v1[1]: -168
v1[1]: 12
v3[1]: 2
v1 == v3: 0
v1 == v1: 1
v1 != v3: 1
v1 != v1: 0

*/

/*

int main() {
    std::cout << "--- Testing Constructors & Stream Output ---\n";
    vect2 v1;
    vect2 v2(3, 4);
    vect2 v3(v2);
    std::cout << "Default v1: " << v1 << " (Expected: {0, 0})\n";
    std::cout << "Param v2:   " << v2 << " (Expected: {3, 4})\n";
    std::cout << "Copy v3:    " << v3 << " (Expected: {3, 4})\n\n";

    std::cout << "--- Testing Math Operators ---\n";
    std::cout << "v2 + v3:    " << (v2 + v3) << " (Expected: {6, 8})\n";
    std::cout << "v2 - v3:    " << (v2 - v3) << " (Expected: {0, 0})\n";
    std::cout << "v2 * 3:     " << (v2 * 3)  << " (Expected: {9, 12})\n";
    std::cout << "2 * v2:     " << (2 * v2)  << " (Expected: {6, 8})\n";
    std::cout << "-v2:        " << (-v2)     << " (Expected: {-3, -4})\n\n";

    std::cout << "--- Testing Compound Assignments ---\n";
    v1 += v2;
    std::cout << "v1 += v2:   " << v1 << " (Expected: {3, 4})\n";
    v1 *= 2;
    std::cout << "v1 *= 2:    " << v1 << " (Expected: {6, 8})\n\n";

    std::cout << "--- Testing Increment / Decrement ---\n";
    std::cout << "v2++ result: " << v2++ << " (Expected: {3, 4})\n";
    std::cout << "v2 after:    " << v2   << " (Expected: {4, 5})\n";
    std::cout << "++v2 result: " << ++v2 << " (Expected: {5, 6})\n\n";

    std::cout << "--- Testing Comparisons & Subscript ---\n";
    std::cout << "v2 == v3:   " << (v2 == v3 ? "True" : "False") << " (Expected: False)\n";
    std::cout << "v2 != v3:   " << (v2 != v3 ? "True" : "False") << " (Expected: True)\n";
    std::cout << "v2[0]:      " << v2[0] << " (Expected: 5)\n";
    
    v2[0] = 10;
    std::cout << "Modified v2:" << v2 << " (Expected: {10, 6})\n";

    return 0;
}
*/