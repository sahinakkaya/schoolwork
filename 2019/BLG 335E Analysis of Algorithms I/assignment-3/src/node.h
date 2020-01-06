#ifndef NODE_H
#define NODE_H
#include "package.h"
enum colors { red, black };
class Node {
 public:
  Package data;
  Node* parent;
  Node* left;
  Node* right;
  colors color;
  int size;
  Node(colors);

  int key() const;
};

#endif