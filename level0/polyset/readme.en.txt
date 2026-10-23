bag

In computer science (and this exam), a bag is a data collection that allows 
duplicate values. Order is usually secondary.

The standard array_bag and tree_bag classes (given) let store numbers, 
but they do not have a built-in search feature. You can insert items, 
but you can't easily ask the bag, "Do you have the number 3?

The abstract interface searchable_bag (given) defines a pure virtual lookup function 
(typically virtual bool has(int value) const = 0;)

Task: Use multiple inheritance to combine the storage capabilities of the raw bags 
with the lookup interface, creating searchable_array_bag and searchable_tree_bag. 
These classes can store elements and search through them.


set

A set is a collection that strictly forbids duplicates.

Instead of rewriting array or tree code from scratch to handle uniqueness, 
the set class uses the Wrapper (or Adapter) Design Pattern.

The set class does not inherit from bags. Instead, it takes a reference 
or pointer to a searchable_bag in its constructor and holds it privately.

When you try to call set::insert(int value), the set acts as a gatekeeper. 
It first calls the underlying bag's .has(value) function.
- If the bag already has the number, the set rejects it and returns false.
- If the bag does not have it, the set calls the bag's .insert(value) function 
and returns true


bool has(int) const

- for classes searchable_array_bag and searchable_tree_bag
this function must iterate through the underlying array/tree 
and check if the value exists.

if node is empty -> false
while
    if node.value == value -> true
    if node.value > value -> search left
    else -> search right
[not found] -> false

- for set wrapper class
The set will call this exact function to check for duplicates 
before letting an element be inserted.


Files to implement:

searchable_array_bag.hpp, searchable_array_bag.cpp
searchable_tree_bag.hpp, searchable_tree_bag.cpp
set.hpp, set.cpp