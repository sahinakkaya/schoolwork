/* @Author
Student Name: Şahin Akkaya
Student ID : 150170098
Date: 24/12/2018 */
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

class TreeNode {
 public:
  int data;
  TreeNode* left;
  TreeNode* right;
};

class Tree {
  int nodecount;
  TreeNode* make_new_node(int);

 public:
  TreeNode* root;
  Tree();
  int get_nodecount();
  void add(int);
  void print(TreeNode*);
  void find_path(TreeNode*, int, int, string, bool&, int);
  int remove_last_node();
  void close(TreeNode*);
};
/*
  /brief takes an integer and returns its binary representation.
  /param n an integer
  /return a string that holds binary representation of n
*/
string int2binary(int n) {
  string b = "";
  while (n != 0) {
    if (n % 2)
      b = "1" + b;
    else
      b = "0" + b;
    n /= 2;
  }
  return b;
};

/*
  /brief constructer for Tree class. Sets initial values for root and nodecount.
*/
Tree::Tree() {
  root = NULL;
  nodecount = 0;
};

/*
  /brief creates a new TreeNode, initializes it with the given data and returns
  a pointer to that node
  /param data an integer that is going to be stored in the new node
  /return a TreeNode pointer that is created in this function
*/
TreeNode* Tree::make_new_node(int data) {
  TreeNode* tNode = new TreeNode;
  tNode->data = data;
  tNode->left = NULL;
  tNode->right = NULL;
  return tNode;
};

/*
  /brief prints the contents of t with pre-order traversal.
  (has nothing to do with this homework but it helps to visualize the tree)
  /param t a TreeNode pointer
*/
void Tree::print(TreeNode* t) {
  if (!t) {
    return;
  }
  cout << t->data << " ";
  print(t->left);
  print(t->right);
};

/*
  /brief takes an integer and adds it to the tree as explained in the pdf file.
  (i don't know what is the name of this type of addition)
  /param data an integer that is going to be added to the tree
*/
void Tree::add(int data) {
  // If we don't have root, create the root
  if (!root)
    root = make_new_node(data);

  else {  // Otherwise, we need to traverse the tree to find addition position.
    TreeNode* t = root;

    // We are adding nodecount+1 th number. If we convert it to binary
    string s = int2binary(nodecount + 1);

    // Starting from second index of the binary representation,
    // we go left for each 0, and go right for each 1

    /*Example: If nodecount is 8, we are adding 9th number. 9 in binary is 1001.
    We skip first index, remain part is 001.
    Which means left-left-right. Which is correct position for 9th number!! OMG
    I'm genious! :D

    However, we should stop before last index because we don't want to assign
    data to NULL.
    */

    int size = s.size();
    int i;
    for (i = 1; i < size - 1; i++) {
      if (s[i] == '1')
        t = t->right;
      else
        t = t->left;
    }
    if (s[i] == '1')
      t->right = make_new_node(data);
    else
      t->left = make_new_node(data);
  }
  nodecount++;
};

/*
  /brief removes last node from tree, deallocates the memory that is reserved
  for it and returns its data /return last node's data
*/
int Tree::remove_last_node() {
  int data = -1;
  if (!root) {
    cerr << "You don't have any node in tree, returning with -1" << endl;
    return data;
  } else {
    // Same logic with adding. No need for extra explanation.
    TreeNode* t = root;

    string s = int2binary(nodecount);
    int size = s.size();
    int i;
    for (i = 1; i < size - 1; i++) {
      if (s[i] == '1')
        t = t->right;
      else
        t = t->left;
    }

    if (s[i] == '1') {
      data = t->right->data;
      delete t->right;
      t->right = NULL;
    } else {
      data = t->left->data;
      delete t->left;
      t->left = NULL;
    }
  }
  nodecount--;
  return data;
};
/*
  /brief traverses the tree to find a path that sums up to spesific number,
  and prints it if any.
*/
void Tree::find_path(TreeNode* t,
                     int target,
                     int current_sum,
                     string path,
                     bool& path_found,
                     int root_value) {
  // If the path is not found, continue the function.
  if (!path_found) {
    // If we reached a leaf node's left or right child (i.e NULL),
    // we don't want to continue to search for a path.
    if (!t)
      return;

    // If the root value is already equals to target, no need to search for a
    // path. We print path found and return from the function.
    if (current_sum == target) {
      cout << "Path Found: " << root_value << endl;
      path_found = true;
      return;
    }
    // Otherwise, we add current node's data to our current sum and to our path.
    current_sum += t->data;
    path += " " + to_string(t->data);

    // If we reach target value by doing this, we print path found and return
    // from the function.
    if (current_sum == target) {
      path = " " + to_string(root_value) + path;
      cout << "Path Found:" << path << endl;
      path_found = true;
      return;
    }

    // As we are doing pre-order traversal, we should visit t, then traverse its
    // left child and right child. We have visited t above (current_sum+=t->data
    // etc.), we should now traverse its left and right respectively.
    find_path(t->left, target, current_sum, path, path_found, root_value);
    find_path(t->right, target, current_sum, path, path_found, root_value);
  }
};
/*
  /brief takes a TreeNode pointer and deletes its left subtree, right subtree
  and finally itself.
*/
void Tree::close(TreeNode* t) {
  if (t) {
    if (t->left != NULL) {
      close(t->left);
      t->left = NULL;
    }
    if (t->right != NULL) {
      close(t->right);
      t->right = NULL;
    }
    delete t;
  }
}

int main(int argc, char* argv[]) {
  if (argc != 2) {
    cerr << "You entered " << argc << " argument" << (argc == 1 ? "" : "s")
         << "." << endl;
    cerr << "Please enter exactly 2 arguments." << endl;
    return -1;
  }

  // Open file...
  ifstream file(argv[1]);

  if (file.fail()) {  // If cannot opened,
    cerr << "Cannot open file '" << argv[1] << "'. No such file." << endl;
    return -1;
  }

  Tree tree;
  int number;

  // Add all numbers to the tree. We will remove the last number later to use as
  // a target value.
  while (file >> number) {
    tree.add(number);
  }
  file.close();

  // We're getting the target value by removing the last node we added to tree.
  // We subtract root's data from it because we want to search root->left and
  // root->right seperately.
  int target = tree.remove_last_node() - tree.root->data;

  bool path_found = new bool;

  // Searching for a path in the left subtree.
  path_found = false;
  tree.find_path(tree.root->left, target, 0, "", path_found, tree.root->data);
  if (!path_found)
    cout << "No Path Found" << endl;

  // Searching for a path in the right subtree.
  path_found = false;
  tree.find_path(tree.root->right, target, 0, "", path_found, tree.root->data);
  if (!path_found)
    cout << "No Path Found" << endl;

  tree.close(tree.root);
  return 0;
}
