#include "vect2.hpp"

/* Default Constructor: {0, 0} */
vect2::vect2() : x(0), y(0) {}

/* Parameterized Constructor: {x, y} */
vect2::vect2(int x, int y) : x(x), y(y) {}

/* Copy constructor */
vect2::vect2(const vect2& other) : x(other.x), y(other.y) {}   // *this = other; <- Avoid doing this!

/* Copy Assignment Operator */
vect2& vect2::operator=(const vect2& other)
{
	if (this != &other)
	{
		x = other.x;
		y = other.y;
	}
	return *this;
}

/* Destructor */
vect2::~vect2() {}

/* Math Operators (+ - *) */
vect2 vect2::operator+(const vect2& other) const
{
	vect2 result(x + other.x, y + other.y);
	return result;  // OR just: return vect2(x + other.x, y + other.y);
}
vect2 vect2::operator-(const vect2& other) const
{
	vect2 result(x - other.x, y - other.y);
	return result;  // OR just: return vect2(x + other.x, y + other.y);
}
vect2 vect2::operator*(const int scalar) const
{
	vect2 result(x * scalar, y * scalar);
	return result;  // OR just: return vect2(x * scalar, y * scalar);
}

// Compound Assignment Operators (+= -= *=)
vect2& vect2::operator+=(const vect2& other)
{
	x += other.x;
	y += other.y;
	return *this;
}
vect2& vect2::operator-=(const vect2& other)
{
	x -= other.x;
	y -= other.y;
	return *this;
}
vect2& vect2::operator*=(const int scalar)
{
	x *= scalar;
	y *= scalar;
	return *this;
}

// Increment & Decrement (++ --)
vect2& vect2::operator++()
{
	x++;
	y++;
	return *this;
}
vect2 vect2::operator++(int)
{
	vect2 copy(*this);
	++x;  // OR ++(*this); <- Call the prefix operator to increment x and y
	++y;
	return copy;
}
vect2& vect2::operator--()
{
	x--;
	y--;
	return *this;
}
vect2 vect2::operator--(int)
{
	vect2 copy(*this);
	--x;  // OR --(*this); <- Call the prefix operator to increment x and y
	--y;
	return copy;
}

// Unary Negation
vect2 vect2::operator-() const
{
	vect2 result(*this);
	result.x *= -1;
	result.y *= -1;
	return result;   // OR just: return vect2(-x, -y);
}

// Comparison Operators (== !=)
bool vect2::operator==(const vect2& other) const
{
	if (x == other.x && y == other.y)
		return true;
	return false;   // OR just:  return (x == other.x && y == other.y);
}
bool vect2::operator!=(const vect2& other) const
{
	return !(*this==other);
}

/* Subscript Operators ([]) */
int& vect2::operator[](int index)
{
	if (index == 0)
		return x;
	return y;   // OR just: return (index==0) ? x : y;
}
const int& vect2::operator[](int index) const
{
	if (index == 0)
		return x;
	return y;   // OR just: return (index==0) ? x : y;
}

// Stream Insertion Operator (<<)
std::ostream& operator<<(std::ostream& out, const vect2& v)
{
	out << "{" << v[0] << ", " << v[1] << "}";
	return (out);
}

// Non-member Symmetric Multiplier (scalar * v)
vect2 operator*(const int scalar, const vect2& v)
{
	return (v * scalar);
}