#ifndef VECT2_HPP
#define VECT2_HPP

#include <iostream>  //for std::ostream

class vect2
{
	private:
		int x;
		int y;

	public:
		/* Orthodox Canonical Form */
		vect2();  // Default: {0, 0}
		vect2(int x, int y);  // Parameterized: {x, y}
		vect2(const vect2& other);  // Copy constructor
		vect2& operator=(const vect2& other);  // Copy assignment
		~vect2();  // Destructor

		// Math Operators (+ - *)
		vect2 operator+(const vect2& other) const;  // v1 + v2
		vect2 operator-(const vect2& other) const;  // v1 - v2
		vect2 operator*(const int scalar) const;  // v * scalar

		// Compound Assignment Operators (+= -= *=)
		vect2& operator+=(const vect2& other); // v1 += v2
		vect2& operator-=(const vect2& other); // v1 -= v2
		vect2& operator*=(const int scalar);  // v1 *= scalar

		// Increment & Decrement (++ --)
		vect2& operator++();  // Prefix ++v
		vect2 operator++(int); // Postfix v++
		vect2& operator--();   // Prefix --v
		vect2 operator--(int); // Postfix v--

		// Unary Negation
		vect2 operator-() const;

		// Comparison Operators (== !=)
		bool operator==(const vect2& other) const;
		bool operator!=(const vect2& other) const;

		// Subscript Operators ([])
		int& operator[](int index);
		const int& operator[](int index) const;
};

// Stream Insertion Operator (<<)
std::ostream& operator<<(std::ostream& out, const vect2& v);

// Non-member Symmetric Multiplier (scalar * v)
vect2 operator*(const int scalar, const vect2& v);


#endif