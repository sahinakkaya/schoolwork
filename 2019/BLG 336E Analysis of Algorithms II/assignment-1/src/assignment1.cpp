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
    clock_t t;
    t = clock();
    Tree tree;
    tree.create_root(&n);
    int max_level;
    string part = argv[1];
    string last_arg = argv[argc-1];
    bool verbose = last_arg == "v";
    int node_count=0;
    if (part == "part1"){
        max_level = stoi(argv[2]);
        tree.create_levels_until(max_level);
    }else if(part =="part2"){
        max_level = stoi(argv[2]);
        tree.create_levels_until(max_level, "", false);
        string t = argv[3];
        if (t == "bfs")
            node_count = tree.breadth_first_traversal(verbose);
        else if (t == "dfs")
            node_count = tree.depth_first_traversal(verbose);
        else
            throw "enter dfs or bfs";
        cout << "node count is: " << node_count <<endl;
    }else if (part =="part3"){

        string winner_pokemon = argv[2];
        tree.create_levels_until(999, winner_pokemon);
        Node* node = tree.breadth_first_search(winner_pokemon);
        tree.print_path_for_node(node);
    }
    t = clock() - t;
    cout << "It took " << ((float)t) / CLOCKS_PER_SEC << " seconds to execute"<<endl;
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