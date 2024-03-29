
#include "node.h"
/*
:param pokemons: a pair of Pokemon instances where the next attacker comes
                first
:param probability: the probability of encountering this state in the
                    game
:param level: an integer that shows the level of this state
:param parent: parent of the node
:param attack_name: name of the attack used to reach this state
:param is_effective: effectiveness of the attack
:param is_leaf: a boolean that tells if this state is end of game
*/
Node::Node(const pair<Pokemon, Pokemon>& pokemons, double probability, int level, 
            Node* parent, string attack_name , bool is_effective, bool is_leaf){
    this->attacker = new Pokemon(pokemons.first);
    this->defender = new Pokemon(pokemons.second);
    this->pokemons = make_pair(attacker, defender);
    this->probability = probability;
    this->level = level;
    this->parent = parent;
    this->attack_name = attack_name;
    this->is_effective = is_effective;
    this->is_leaf = is_leaf;
}

string Node::repr(){
    bool pikachu_is_first = attacker->is_pikachu;
    string f = pikachu_is_first?attacker->repr():defender->repr();
    string s = pikachu_is_first?defender->repr():attacker->repr();
    string prob = " PROB:" + to_string(probability);
    string level = " LEVEL:" + to_string(this->level);
    return f + " " + s + prob;
}
Node::Node(const Node& node){
    /*Compiler generated code does not allocates memory so
    we need to do this manually */
    attacker = new Pokemon(*node.attacker);
    defender = new Pokemon(*node.defender);

    /* But the rest is same, so if there is an easy way for this,
    like super() in python, please let me now because this is 
    really bad... */
    pokemons  = make_pair(attacker, defender);
    probability = node.probability;
    level = node.level;
    parent = node.parent;
    attack_name = node.attack_name;
    is_effective = node.is_effective;
    is_leaf = node.is_leaf;

}

void Node::print(){
    cout << repr() <<endl;
}

Node::~Node(){
    delete attacker;
    delete defender;
    for(auto child:children){
        // cout << "node gets deleted ";
        // child->print();
        delete child;
    }
}