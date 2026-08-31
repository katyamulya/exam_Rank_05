#ifndef SEARCHABLE_ARRAY_BAG_HPP
#define SEARCHABLE_ARRAY_BAG_HPP

#include "array_bag.hpp"
#include "searchable_bag.hpp"

class searchhable_array_bag: public array_bag, public searchable_bag
{
	/* Orthodox Canonical Form */
	searchhable_array_bag();
	searchhable_array_bag(const searchhable_array_bag& other);
	searchhable_array_bag& operator=(const searchhable_array_bag& other);
	~searchhable_array_bag();

	bool has(int value) const;
};

#endif