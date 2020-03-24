#include "tree.h"
using namespace std;
int main(int argc, char**argv){
    Attack a = Attack("Thundershock","-10","100","40","0");
    //cout << a.cost << endl;
    //cout << Pokemon::ATTACKS["blastoise"][1].name << endl;

    Pokemon pikachu = Pokemon("pikachu", 200, 100);
    Pokemon blastoise = Pokemon("blastoise", 200, 100);
    //pikachu.attack(blastoise, a, false);
    Node n = Node(make_pair(&pikachu, &blastoise), 1, 0, nullptr);
    // cout << (n.parent == nullptr) << endl;
    // Node p = Node(make_pair(pikachu, blastoise), 0.5, 0, &n);
    // cout << (p.parent->parent == nullptr) << endl;

    Tree tree;
    tree.create_root(&n);
    int max_level;
    string part = argv[1];
    if (part == "part1"){
        max_level = stoi(argv[2]);
        tree.create_levels_until(max_level);
    }
    //Pokemon p = pikachu.copy();
    //p.health_points = 0;
    //cout << p.health_points<< endl;

    // cout << pikachu.health_points<< endl;
    // cout << pikachu.power_points << endl;
    // cout << blastoise.health_points << endl;
    // cout << blastoise.power_points << endl;


    // for(auto attack:pikachu.get_attacks(2))
    //     cout << attack.name << endl;
    

    //cout << pikachu.is_pikachu << endl;

    //Pokemon bulba = Pokemon("bulbasaur", 1, 1);
}