#ifndef TREE_H
#define TREE_H
#include "node.h"
class Tree{
    private:
        Node* root;
        bool end_flag;
    public:
        Tree();
        void create_root(Node*);
        void create_levels_until(int=999, string="", bool=true);
        int breadth_first_traversal(bool=false);
        int depth_first_traversal(bool=false);
        bool end_of_game(Pokemon*, Pokemon*, string, bool);
        Node* breadth_first_search(string);
};





//     def __str__(self):
//         pikachu_index = 0 if self.pokemons[0].is_pikachu else 1
//         blastoise_index = (pikachu_index + 1) % 2
//         return " ".join(map(str, (self.pokemons[pikachu_index],
//                                   self.pokemons[blastoise_index],
//                                   f"PROB:{self.probability:.7f}")))

#endif