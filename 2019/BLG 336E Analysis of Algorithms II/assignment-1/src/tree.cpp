#include "tree.h"
#include <deque>
using namespace std; 

Tree::Tree(){
    root = nullptr;
    end_flag = false;
}

void Tree::attach_root(Node& node){
    if (root){
        this->~Tree();
    }
    root = new Node(node);
}
/*
 *Creates levels until number of levels reaches max_level OR
 *winner wins the game
*/
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
                Pokemon attacker = Pokemon(*node->attacker);
                Pokemon defender = Pokemon(*node->defender);
                attacker.attack(defender, attack, effective);

                double probability = node->probability / num_attacks * attack.accuracy;
                Node* n = new Node(make_pair(defender, attacker), probability, node->level + 1, node,
                                attack.name, effective);
                if (verbose && n->level == max_level)
                    n->print();
                if (defender.health_points == 0 and attacker.is_pikachu == winner_is_pikachu)
                    if (winner == "pikachu" || winner == "blastoise")
                        end_flag = true;
                children.push_back(n);
                if (attack.accuracy != 1){
                        effective = false;
                        Pokemon attacker = Pokemon(*node->attacker);
                        Pokemon defender = Pokemon(*node->defender);
                        attacker.attack(defender, attack, effective);
                        double probability = node->probability / num_attacks * attack.inaccuracy;
                        Node* n = new Node(make_pair(defender, attacker), probability, node->level + 1, node,
                                attack.name, effective);
                        if (verbose && n->level == max_level)
                            n->print();
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
/*
 *Performs a level order traversal on tree that has root 'root_node' and
 *returns number of nodes
*/
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
/*
*Performs pre order traversal on tree that has root 'root_node' and
*returns number of nodes
*/
int Tree::depth_first_traversal(bool verbose){
    if (root ==nullptr)
        return 0;
    int node_count = 0;
    vector<Node*> stack;
    stack.push_back(root);
    Node* node;
    while (stack.size() > 0){
        node_count++;
        node = stack.back();
        stack.pop_back();
        if (verbose)
            node->print();
        for (auto it = node->children.rbegin(); it != node->children.rend(); ++it){
            stack.push_back(*it);
        }
    }
    return node_count;
}

void Tree::print_path_for_node(Node* node){
    vector<Node*> list_of_nodes;
    while (node->parent){
        list_of_nodes.push_back(node);
        node = node->parent;
    }
    int pikachu_hp, blastoise_hp;
    string prev_attacker, attack_name;
    while (list_of_nodes.size()>0){
        node = list_of_nodes.back();
        list_of_nodes.pop_back();
        if (node->attacker->is_pikachu){
            prev_attacker = "Blastoise";
            pikachu_hp = node->attacker->health_points;
            blastoise_hp = node->defender->health_points;
        }
        else{
            prev_attacker = "Pikachu";
            pikachu_hp = node->defender->health_points;
            blastoise_hp = node->attacker->health_points;
        }
        attack_name = node->attack_name;
        string is_effective = node->is_effective? "Effective":"Noneffective";

        cout << prev_attacker << " used " << attack_name << ". " << is_effective
            << " (P:" << pikachu_hp << ", B:"<<blastoise_hp<<")"<<endl;
    }
    cout << "Level count: "<< node->level <<endl;
    cout << "Probability: "<< node->probability << endl;

}

Tree::~Tree(){
    // cout << "node gets deleted (root)";
    // root->print();
    delete root;
    root=nullptr;
    end_flag=false;
}