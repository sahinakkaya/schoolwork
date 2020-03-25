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