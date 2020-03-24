#ifndef POKEMON_H
#define POKEMON_H
#include <iostream>
#include <map>
#include <vector>
#include "attack.h"
using namespace std;
class Pokemon{
        vector<Attack>& attacks();
    public:
        static map<string, vector<Attack>> ATTACKS;
        int health_points;
        int power_points;
        bool is_pikachu;
        Pokemon(string, int, int);
        Pokemon();
        // Pokemon& operator = (const Pokemon &t);
        vector<Attack> get_attacks(int);
        string name();
        Pokemon copy();
        void attack(Pokemon&, const Attack&, bool);

};

// class Pokemon:
//     @staticmethod
//     def __read_attacks_file(name):
//         """
//         Reads attacks file for pokemon specified by name and returns
//         list of attacks that the pokemon can do
//         """
//         with open(name + ".txt") as f:
//             f.readline()
//             return [Attack(*line.split(",")) for line in f.readlines()]


//     def __repr__(self):
//         name = "pikachu" if self.is_pikachu else "blastoise"
//         return f"Pokemon('{name}', {self.health_points}, {self.power_points})"

//     def __str__(self):
//         i = "P" if self.is_pikachu else "B"
//         return f"{i}_HP:{self.health_points} {i}_PP:{self.power_points}"

#endif