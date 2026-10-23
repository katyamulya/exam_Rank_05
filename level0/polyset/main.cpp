/*		SUBJECT		*/

// c++ -Wall -Werror -Wextra -std=c++98 main.cpp array_bag.cpp tree_bag.cpp searchable_array_bag.cpp searchable_tree_bag.cpp set.cpp

#include "searchable_array_bag.hpp"
#include "searchable_tree_bag.hpp"
#include "set.hpp"

#include <cstdlib>
#include <iostream>

int main(int argc, char **argv)  // 42 21 42
{
	if (argc == 1)
		return 1;
	searchable_bag *t = new searchable_tree_bag;
	searchable_bag *a = new searchable_array_bag;

	for (int i = 1; i < argc; i++) 
	{
		t->insert(atoi(argv[i]));
		a->insert(atoi(argv[i]));
	}
	t->print();  // 21 42
	a->print();  // 42 21 42

	int array[] = {1, 2, 3, 4};


	for (int i = 1; i < argc; i++)
	{
		std::cout << atoi(argv[i]) << " : " << std::endl;
		std::cout << "	t -> " << t->has(atoi(argv[i])) << std::endl;
		std::cout << "	a -> " << a->has(atoi(argv[i])) << std::endl;
		std::cout << (atoi(argv[i]) - 1) << " : " << std::endl;
		std::cout << "	t -> " << t->has(atoi(argv[i]) - 1) << std::endl;
		std::cout << "	a -> " << a->has(atoi(argv[i]) - 1) << std::endl;
	}

	t->clear();
	a->clear();

	const searchable_array_bag tmp(static_cast<searchable_array_bag &>(*a));
	tmp.print();  // nothing (because a was cleaned)
	tmp.has(1);  // 0

	set sa(*a);
	set st(*t);
	for (int i = 1; i < argc; i++)
	{

		st.insert(atoi(argv[i]));
		sa.insert(atoi(argv[i]));

		sa.has(atoi(argv[i]));
		sa.print();
		sa.get_bag().print();
		st.print();
		sa.clear();

		sa.insert(array, 4);
		std::cout << std::endl;
	}
		// sa: 1 2 3 4
		// st: 21 42
		delete t;
    	delete a;

		return (0);
}