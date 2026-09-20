#include "set.hpp"

// Private default constructor - prevents uninitialized usage
//set::set() : bag(NULL) {}

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
	if (!bag) return;
	// Check if it already exists using 'has'
	if (bag->has(value) == false)
		bag->insert(value);
}
void set::insert(int *array, int size)
{
	if(!bag || !array)
		return;
	for(int i = 0; i < size; i++)
	{
		this->insert(array[i]); // Re-use the single insert to check duplicates automatically
	}
}
void set::print() const
{
	if (bag)
		bag->print(); // Forward print directly to the bag instance
}
void set::clear()
{
	if(bag)
		bag->clear();  // Forward clear directly to the bag instance
}

bool set::has(int value) const
{
	if (!bag) return false;
	return bag->has(value); // Forward has directly to the bag instance
}

searchable_bag& set::get_bag() const
{
	return *bag;
}
