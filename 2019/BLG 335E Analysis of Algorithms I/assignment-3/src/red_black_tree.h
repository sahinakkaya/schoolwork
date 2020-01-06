#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H

#include <iostream>
#include <vector>
#include <stack>
#include "node.h"
#include "hw3.h"
using namespace std;

class RedBlackTree {
 private:
  Node* root;
  Node* TNULL;

  Node* os_select(Node*, int);

  void delete_fixup(Node*);

  void insert_fixup(Node*);
  void print_helper(Node*, string, bool);
  void left_rotate(Node*);
  void right_rotate(Node*);

 public:
  RedBlackTree();

  Node* minimum(Node*);
  Node* maximum(Node*);

  int get_node_count();
  Node* nth_smallest_element(int);
  
  vector<Package> get_smallest_packages();
  Node* successor(Node*);
  Node* predecessor(Node*);
  
  void insert(Package&);
  Node* get_root();
  Node* delete_node(Node* z);
  void print_tree();
  bool is_empty();

  HW3_Result report();
};

#endif