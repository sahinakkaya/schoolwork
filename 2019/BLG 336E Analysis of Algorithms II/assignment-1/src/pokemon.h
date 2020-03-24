#ifndef POKEMON_H
#define POKEMON_H
#include <iostream>
#include <map>
#include <vector>
#include "attack.h"
using namespace std;
class Pokemon{
        vector<Attack>& attacks();
        vector<Attack> read_attacks_file(string);
    public:
        static map<string, vector<Attack>> ATTACKS;
        int health_points;
        int power_points;
        bool is_pikachu;
        Pokemon(string, int, int);
        Pokemon();
        vector<Attack> get_attacks(int);
        string name();
        Pokemon copy();
        void attack(Pokemon&, const Attack&, bool);
        string repr();

};


#endif