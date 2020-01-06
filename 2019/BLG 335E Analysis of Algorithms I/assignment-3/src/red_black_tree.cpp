#include "red_black_tree.h"

Node* RedBlackTree::os_select(Node* node, int i) {
  if (i > get_node_count()) {
    return nullptr;
  }
  if (node == TNULL) {
    return nullptr;
  }
  int r = node->left->size + 1;
  if (i == r)
    return node;
  else if (i < r) {
    return os_select(node->left, i);
  }
  return os_select(node->right, i - r);
}

void RedBlackTree::delete_fixup(Node* x) {
  Node* w;
  while (x != root && x->color == black) {
    if (x == x->parent->left) {
      w = x->parent->right;
      if (w->color == red) {
        w->color = black;
        x->parent->color = red;
        left_rotate(x->parent);
        w = x->parent->right;
      }
      if (w->left->color == black && w->right->color == black) {
        w->color = red;
        x = x->parent;
      } else {
        if (w->right->color == black) {
          w->left->color = black;
          w->color = red;
          right_rotate(w);
          w = x->parent->right;
        }
        w->color = x->parent->color;
        x->parent->color = black;
        w->right->color = black;
        left_rotate(x->parent);
        x = root;
      }
    } else {
      w = x->parent->left;
      if (w->color == red) {
        w->color = black;
        x->parent->color = red;
        right_rotate(x->parent);
        w = x->parent->left;
      }
      if (w->right->color == black && w->left->color == black) {
        w->color = red;
        x = x->parent;
      } else {
        if (w->left->color == black) {
          w->right->color = black;
          w->color = red;
          left_rotate(w);
          w = x->parent->left;
        }
        w->color = x->parent->color;
        x->parent->color = black;
        w->left->color = black;
        right_rotate(x->parent);
        x = root;
      }
    }
  }
  x->color = black;
}

void RedBlackTree::insert_fixup(Node* z) {
  Node* y;
  while (z->parent->color == red) {
    if (z->parent == z->parent->parent->right) {
      y = z->parent->parent->left;
      if (y->color == red) {
        y->color = black;
        z->parent->color = black;
        z->parent->parent->color = red;
        z = z->parent->parent;
      } else {
        if (z == z->parent->left) {
          z = z->parent;
          right_rotate(z);
        }
        z->parent->color = black;
        z->parent->parent->color = red;
        left_rotate(z->parent->parent);
      }
    } else {
      y = z->parent->parent->right;
      if (y->color == red) {
        y->color = black;
        z->parent->color = black;
        z->parent->parent->color = red;
        z = z->parent->parent;
      } else {
        if (z == z->parent->right) {
          z = z->parent;
          left_rotate(z);
        }
        z->parent->color = black;
        z->parent->parent->color = red;
        right_rotate(z->parent->parent);
      }
    }
  }
  root->color = black;
}

void RedBlackTree::print_helper(Node* node, string indent, bool is_right) {
  if (node != TNULL) {
    cout << indent;
    if (is_right) {
      cout << "R----";
      indent += "   ";
    } else {
      cout << "L----";
      indent += "|  ";
    }
    string color = node->color == red ? "RED" : "BLACK";
    cout << "(" << node->data.get_size() << ", " << node->data.get_ordinal()
         << ")(" << color << ")" << endl;
    print_helper(node->left, indent, false);
    print_helper(node->right, indent, true);
  }
}

void RedBlackTree::left_rotate(Node* x) {
  Node* y = x->right;
  x->right = y->left;
  if (y->left != TNULL) {
    y->left->parent = x;
  }
  y->parent = x->parent;
  if (x->parent == TNULL) {
    this->root = y;
  } else if (x == x->parent->left) {
    x->parent->left = y;
  } else {
    x->parent->right = y;
  }
  y->left = x;
  x->parent = y;
  y->size = x->size;
  x->size = x->left->size + x->right->size + 1;
}

void RedBlackTree::right_rotate(Node* x) {
  Node* y = x->left;
  x->left = y->right;
  if (y->right != TNULL) {
    y->right->parent = x;
  }
  y->parent = x->parent;
  if (x->parent == TNULL) {
    this->root = y;
  } else if (x == x->parent->right) {
    x->parent->right = y;
  } else {
    x->parent->left = y;
  }
  y->right = x;
  x->parent = y;
  y->size = x->size;
  x->size = x->left->size + x->right->size + 1;
}

RedBlackTree::RedBlackTree() {
  TNULL = new Node(black);
  TNULL->size = 0;
  root = TNULL;
}
Node* RedBlackTree::minimum(Node* node) {
  while (node->left != TNULL) {
    node = node->left;
  }
  return node;
}
Node* RedBlackTree::maximum(Node* node) {
  while (node->right != TNULL) {
    node = node->right;
  }
  return node;
}

int RedBlackTree::get_node_count() { return root->size; }
Node* RedBlackTree::nth_smallest_element(int n) { return os_select(root, n); }

vector<Package> RedBlackTree::get_smallest_packages() {
  vector<Package> result;
  Node* n = nth_smallest_element(1);
  Package p = n->data;
  result.push_back(p);
  int key = p.get_size();
  delete_node(n);
  Node* node;
  while ((node = nth_smallest_element(1)) && node->key() == key) {
    result.push_back(node->data);
    delete_node(node);
  }
  return result;
}
Node* RedBlackTree::successor(Node* x) {
  if (x->right != TNULL) {
    return minimum(x->right);
  }
  Node* y = x->parent;
  while (y != TNULL && x == y->right) {
    x = y;
    y = y->parent;
  }
  return y;
}
Node* RedBlackTree::predecessor(Node* x) {
  if (x->left != TNULL) {
    return maximum(x->left);
  }
  Node* y = x->parent;
  while (y != TNULL && x == y->left) {
    x = y;
    y = y->parent;
  }
  return y;
}

void RedBlackTree::insert(Package& p) {
  Node* node = new Node(red);

  node->data = Package(p.get_size(), p.get_ordinal());
  node->left = TNULL;
  node->right = TNULL;
  Node* y = TNULL;
  Node* x = root;

  while (x != TNULL) {
    x->size++;
    y = x;

    if (node->key() < x->key()) {
      x = x->left;
    } else {
      x = x->right;
    }
  }
  node->parent = y;
  if (y == TNULL) {
    root = node;
  } else if (node->key() < y->key()) {
    y->left = node;
  } else {
    y->right = node;
  }

  if (node->parent == TNULL) {
    node->color = black;
    return;
  }

  if (node->parent->parent == TNULL) {
    return;
  }
  insert_fixup(node);
}

Node* RedBlackTree::get_root() { return this->root; }
Node* RedBlackTree::delete_node(Node* z) {
  Node* y;
  Node* x;

  if (z->left == TNULL || z->right == TNULL)
    y = z;
  else
    y = successor(z);
  if (y->left != TNULL)
    x = y->left;
  else
    x = y->right;
  x->parent = y->parent;
  if (y->parent == TNULL)
    this->root = x;
  else if (y == y->parent->left)
    y->parent->left = x;
  else
    y->parent->right = x;

  if (y != z) {
    z->data = y->data;
  }
  Node* t = y;
  while (t != root && t != TNULL) {
    t = t->parent;
    if (t != TNULL) t->size--;
  }
  if (y->color == black) delete_fixup(x);
  return y;
}
void RedBlackTree::print_tree() {
  if (root != TNULL) {
    print_helper(this->root, "", true);
  }
}
bool RedBlackTree::is_empty() { return root == TNULL; }

HW3_Result RedBlackTree::report() {
  int num_of_nodes = get_node_count();
  int num_of_red_nodes = 0;
  int num_of_black_nodes = 0;
  stack<Node*> s;
  Node* node = root;

  while (node != TNULL || !s.empty()) {
    while (node != NULL) {
      s.push(node);
      node = node->left;
    }
    node = s.top();
    s.pop();

    if (node->color == red)
      num_of_red_nodes++;
    else if (node != TNULL)
      num_of_black_nodes++;
    node = node->right;
  }
  return HW3_Result{num_of_nodes, num_of_red_nodes, num_of_black_nodes};
}