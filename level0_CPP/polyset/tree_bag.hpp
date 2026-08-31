/*		SUBJECT		*/

#ifndef TREE_BAG_HPP
#define TREE_BAG_HPP

#include "bag.hpp"

class tree_bag : virtual public bag {
protected:
  struct node {
    node *l;  // Pointer to the Left child node (stores smaller or equal values)
    node *r;  // Pointer to the Right child node (stores larger values)
    int value;  // The actual integer data stored in this node
  };
  node *tree;

public:
  tree_bag();
  tree_bag(const tree_bag &);
  tree_bag  &operator=(const tree_bag &);
  ~tree_bag();

  node *extract_tree();  // like a getter to get data from node,  but node set to NULL
  void set_tree(node *);

  virtual void insert(int);
  virtual void insert(int *array, int size);
  virtual void print() const;
  virtual void clear();

private:
  static void destroy_tree(node *);
  static void print_node(node *);
  static node *copy_node(node *);
};

#endif