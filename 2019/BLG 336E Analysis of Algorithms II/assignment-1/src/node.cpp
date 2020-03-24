
#include "node.h"
Node::Node(pair<Pokemon, Pokemon> pokemons, double probability, int level, 
            Node* parent, string attack_name , bool is_effective, bool is_leaf){
    this->pokemons = pokemons;
    this->attacker = &pokemons.first;
    this->defender = &pokemons.second;
    this->probability = probability;
    this->level = level;
    this->parent = parent;
    this->attack_name = attack_name;
    this->is_effective = is_effective;
    this->is_leaf = is_leaf;
}
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
