#include "vect2.hpp"

// []
int& vect2::operator[](int index)
{
	return (index==0) ? x : y;   // if index==0 -> x, else y
}
const int& vect2::operator[](int index) const
{
	return (index==0) ? x : y;
}