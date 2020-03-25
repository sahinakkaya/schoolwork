#ifndef TREE_H
#define TREE_H
#include "node.h"
#include <tuple>

typedef tuple<Pokemon, Pokemon, Node*> PokemonsAndNode;

class Tree{
    private:
        Node* root;
        bool end_flag;
        bool end_of_game(const Pokemon&, const Pokemon&, const string&, bool);
    public:
        Tree();
        void attach_root(Node&);
        void create_levels_until(int=999, string="", bool=true);
        int breadth_first_traversal(bool=false);
        int depth_first_traversal(bool=false);
        PokemonsAndNode spawn_node(Node*, Attack&, bool, int, int, bool);
        Node* breadth_first_search(string);
        void print_path_for_node(Node*);
        ~Tree();
};
#endif

