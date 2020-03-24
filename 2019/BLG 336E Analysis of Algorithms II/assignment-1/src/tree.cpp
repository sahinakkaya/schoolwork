#include "tree.h"
#include <deque>
using namespace std; 

Tree::Tree(){
    root = nullptr;
    end_flag = false;
}

void Tree::create_root(Node* node){
    root = node;
}
void Tree::create_levels_until(int max_level, string winner, bool verbose){
    deque<Node*> leaves;
    Node* node = root;
    while(!end_flag){
        if (node->level == max_level)
            break;
        vector<Node*> children;
        bool winner_is_pikachu =  winner == "pikachu";
        if(node->attacker->health_points > 0){
            vector<Attack> possible_attacks = node->attacker->get_attacks(node->level);
            int num_attacks = possible_attacks.size();
            for (auto attack :possible_attacks){
                bool effective = true;
                // cout << "an attack begins----------------"<<endl;
                // cout << "name: "<<attack.name<< " damage: " <<attack.damage << " pp: "<<attack.cost<<endl;
                // cout << node->attacker->repr()<< endl;
                Pokemon* attacker = new Pokemon(*node->attacker);
                // cout << attacker->repr()<<endl;
                Pokemon* defender = new Pokemon(*node->defender);
                // Effective
                attacker->attack(*defender, attack, effective);
                // cout << node->attacker->repr()<< endl;

                // cout << attacker->repr()<<endl;
                // cout << "-------------------an attack ends"<<endl;

                double probability = node->probability / num_attacks * attack.accuracy;
                Node* n = new Node(make_pair(defender, attacker), probability, node->level + 1, node,
                                attack.name, effective);
                if (verbose && n->level == max_level){
                    // cout << "effective ";    
                    n->print();
                }
                if (defender->health_points == 0 and attacker->is_pikachu == winner_is_pikachu)
                    if (winner == "pikachu" || winner == "blastoise")
                        end_flag = true;
                children.push_back(n);
                if (attack.accuracy != 1){
                        effective = false;
                        Pokemon* attacker = new Pokemon(*node->attacker);
                        Pokemon* defender = new Pokemon(*node->defender);
                        // Non Effective
                        attacker->attack(*defender, attack, effective);
                        double probability = node->probability / num_attacks * attack.inaccuracy;
                        Node* n = new Node(make_pair(defender, attacker), probability, node->level + 1, node,
                                attack.name, effective);
                        if (verbose && n->level == max_level){
                            // cout << "non effective ";
                            n->print();
                        }
                        children.push_back(n);
                }
            }
        }
        if (children.size() > 0){
                node->is_leaf = false;
                for (auto child:children){
                    node->children.push_back(child);
                }
                for (auto child:children){
                    leaves.push_back(child);
                }

        }
        node = leaves.front();
        leaves.pop_front();
        
    }
    if(node==root){
        root->print();
    }
}  

int Tree::breadth_first_traversal(bool verbose){
    if(root == nullptr)
        return 0;
    int node_count = 0;
    deque<Node*> queue;
    queue.push_back(root);
    Node* node;
    while(not queue.empty()){
        node_count++;
        node = queue.front();
        queue.pop_front();
        if (verbose)
            node->print();
        for(auto child:node->children)
            queue.push_back(child);
    }
    return node_count;
}

bool Tree::end_of_game(Pokemon* attacker, Pokemon* defender, string winner, bool winner_is_pikachu){
    if (defender->health_points == 0 and attacker->is_pikachu == winner_is_pikachu)
            if (winner =="pikachu" || winner == "blastoise")
                return true;
        return false;

}

Node* Tree::breadth_first_search(string winner){
    if(root == nullptr)
        return nullptr;

    deque<Node*> queue;
    queue.push_back(root);
    bool winner_is_pikachu = winner == "pikachu";
    Node* node;
    while(not queue.empty()){
        node = queue.front();
        queue.pop_front();
        if (end_of_game(node->defender, node->attacker, winner, winner_is_pikachu))
            return node;

        for(auto child:node->children)
            queue.push_back(child);
    }
    return nullptr;
}
//     @staticmethod
    // def breadth_first_search(root_node: 'Node', winner: str):
    //     if root_node is None:
    //         return None
    //     queue = deque((root_node,))
    //     winner_is_pikachu = winner == "pikachu"
    //     while len(queue) > 0:
    //         node = queue.popleft()
    //         if Node.__end_of_game(node.defender, node.attacker, winner,
    //                               winner_is_pikachu):
    //             return node
    //         queue.extend(node.children)

    //     return None