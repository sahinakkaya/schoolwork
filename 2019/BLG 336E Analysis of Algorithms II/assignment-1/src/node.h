#ifndef NODE_H
#define NODE_H
#include "pokemon.h"
using namespace std;
class Node{
    public:
        
        pair<Pokemon*, Pokemon*> pokemons;
        Pokemon* attacker;
        Pokemon* defender;
        double probability;
        int level;
        Node* parent;
        string attack_name;
        bool is_effective;
        bool is_leaf;
        vector<Node*> children;
        Node(const pair<Pokemon, Pokemon>&, double, int, Node*, string="som", bool=true, bool=true);
        Node(const Node&); // copy constructor
        string repr();
        void print();
        ~Node();
};
#endif
// class Node:
//     """A class to represent a state in the game"""
//     END_FLAG = []

//     def __init__(self, pokemons: Tuple[Pokemon, Pokemon],
//                  probability: float, level: int, parent: 'Node' = None,
//                  attack_name: str = None, is_effective: bool = None,
//                  is_leaf: Optional[bool] = True) -> None:
//         """
//         :param pokemons: a pair of Pokemon instances where the next attacker comes
//                         first
//         :param probability: the probability of encountering this state in the
//                             game
//         :param level: an integer that shows the level of this state
//         :param parent: parent of the node
//         :param attack_name: name of the attack used to reach this state
//         :param is_effective: effectiveness of the attack
//         :param is_leaf: a boolean that tells if this state is end of game
//         """
//         self.pokemons = pokemons
//         self.attacker, self.defender = pokemons
//         self.probability = probability
//         self.level = level
//         self.parent = parent
//         self.attack_name = attack_name
//         self.is_effective = is_effective
//         self.is_leaf = is_leaf
//         self.children = []

//     def create_levels_until(self, max_level: Optional[int] = 999,
//                             winner: Optional[str] = "",
//                             verbose: Optional[bool] = True) -> None:
//         """
//         Creates levels until number of levels reaches max_level OR
//         winner wins the game
//         """
//         leaves = deque([self])
//         while not Node.END_FLAG:

//             node = leaves.popleft()
//             if node.level == max_level:
//                 break
//             children = []
//             winner_is_pikachu = winner == "pikachu"
//             if node.attacker.health_points > 0:
//                 possible_attacks = node.attacker.get_attacks(node.level)
//                 num_attacks = len(possible_attacks)
//                 for attack in possible_attacks:
//                     effective = True
//                     attacker, defender, n = self.__spawn_node(node, attack,
//                                                               effective,
//                                                               num_attacks, max_level,
//                                                               verbose)
//                     if self.__end_of_game(attacker, defender, winner,
//                                           winner_is_pikachu):
//                         Node.END_FLAG.append(True)
//                     children.append(n)

//                     if attack.accuracy != 1:
//                         effective = False
//                         attacker, defender, n = self.__spawn_node(node, attack,
//                                                                   effective,
//                                                                   num_attacks,
//                                                                   max_level,
//                                                                   verbose)
//                         children.append(n)

//             if len(children) > 0:
//                 node.is_leaf = False
//                 node.children.extend(children)
//                 leaves.extend(children)

//     @staticmethod
//     def __end_of_game(attacker, defender, winner, winner_is_pikachu):
//         if defender.health_points == 0 and attacker.is_pikachu == winner_is_pikachu:
//             if winner in ("pikachu", "blastoise"):
//                 return True
//         return False

//     @staticmethod
//     def __spawn_node(node, attack, effective, num_attacks, max_level, verbose):
//         attacker, defender = node.attacker.copy(), node.defender.copy()
//         # Effective
//         attacker.attack(defender, attack, effective=effective)
//         mul = attack.accuracy if effective else attack.inaccuracy
//         probability = node.probability / num_attacks * mul
//         n = Node((defender, attacker), probability, node.level + 1, node,
//                  attack.name, effective)
//         if verbose and n.level == max_level:
//             print(n)
//         return attacker, defender, n

//     @staticmethod
//     def breadth_first_traversal(root_node: 'Node',
//                                 verbose: Optional[bool] = False) -> int:
//         """
//         Performs a level order traversal on tree that has root 'root_node' and
//         returns number of nodes
//         """
//         if root_node is None:
//             return 0
//         node_count = 0
//         queue = deque((root_node,))

//         while len(queue) > 0:
//             node_count += 1
//             node = queue.popleft()
//             if verbose:
//                 print(node)
//             queue.extend(node.children)

//         return node_count

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

