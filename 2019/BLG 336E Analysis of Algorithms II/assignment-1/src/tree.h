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
        bool end_of_game(Pokemon*, Pokemon*, string, bool);
        Node* breadth_first_search(string);
};


//     @staticmethod
//     def breadth_first_search(root_node: 'Node', winner: str):
//         if root_node is None:
//             return None
//         queue = deque((root_node,))
//         winner_is_pikachu = winner == "pikachu"
//         while len(queue) > 0:
//             node = queue.popleft()
//             if Node.__end_of_game(node.defender, node.attacker, winner,
//                                   winner_is_pikachu):
//                 return node
//             queue.extend(node.children)

//         return None

//     @staticmethod
//     def depth_first_traversal(root_node: 'Node',
//                               verbose: Optional[bool] = False) -> int:
//         """
//         Performs pre order traversal on tree that has root 'root_node' and
//         returns number of nodes
//         """
//         if root_node is None:
//             return 0
//         node_count = 0
//         stack = [root_node]
//         while len(stack) > 0:
//             node_count += 1
//             node = stack.pop()
//             if verbose:
//                 print(node)
//             stack.extend(reversed(node.children))
//         return node_count

//     def __str__(self):
//         pikachu_index = 0 if self.pokemons[0].is_pikachu else 1
//         blastoise_index = (pikachu_index + 1) % 2
//         return " ".join(map(str, (self.pokemons[pikachu_index],
//                                   self.pokemons[blastoise_index],
//                                   f"PROB:{self.probability:.7f}")))

#endif