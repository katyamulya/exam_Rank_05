#include "set.hpp"

// 1. The ONLY way to build a set (saves the reference address into the pointer)
set::set(searchable_bag& sbag) : bag(&sbag) {}
// 2. Copy Constructor (copies the pointer address)
set::set(const set& other) : bag(other.bag) {}
// 3. Assignment Operator (rebinds the pointer address)
set& set::operator=(const set& other)
{
	if (this != &other)
		this->bag = other.bag;
	return *this;
}
// 4. Destructor (Does NOT delete bag, as set doesn't own it)
set::~set() {}

void set::insert(int value)
{
	// Check if it already exists using 'has'
	if (bag->has(value) == false)
		bag->insert(value);
}
void set::insert(int *array, int size)
{
	if(!array)
		return;
	for(int i = 0; i < size; i++)
	{
		this->insert(array[i]); // Re-use the single insert to check duplicates automatically
	}
}
void set::print() const
{
	bag->print(); // Forward print directly to the bag instance
}
void set::clear()
{
	bag->clear();  // Forward clear directly to the bag instance
}

bool set::has(int value) const
{
	return bag->has(value); // Forward has directly to the bag instance
}

searchable_bag& set::get_bag() const
{
	return *bag;
}