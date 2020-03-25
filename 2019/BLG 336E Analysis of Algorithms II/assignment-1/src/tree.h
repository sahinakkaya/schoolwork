#ifndef TREE_H
#define TREE_H
#include "node.h"
class Tree{
    private:
        Node* root;
        bool end_flag;
    public:
        Tree();
        void attach_root(Node&);
        void create_levels_until(int=999, string="", bool=true);
        int breadth_first_traversal(bool=false);
        int depth_first_traversal(bool=false);
        bool end_of_game(Pokemon*, Pokemon*, string, bool);
        Node* breadth_first_search(string);
        void print_path_for_node(Node*);
        ~Tree();
};

#endif