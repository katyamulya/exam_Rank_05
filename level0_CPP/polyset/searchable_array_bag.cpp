#include "searchable_array_bag.hpp"

searchhable_array_bag::searchhable_array_bag() : array_bag() {}
searchhable_array_bag::searchhable_array_bag(const searchhable_array_bag& other) : array_bag(other) {}
searchhable_array_bag& searchhable_array_bag::operator=(const searchhable_array_bag& other)
{
	if (this != &other)
		array_bag::operator=(other);
	return *this;
}
searchhable_array_bag::~searchhable_array_bag() {}

bool searchhable_array_bag::has(int value) const
{
	if (this->size <= 0)
		return false;
	for(int i = 0; i< this->size; i++)
	{
		if (this->data[i] == value)
			return true;
	}
	return false;
}