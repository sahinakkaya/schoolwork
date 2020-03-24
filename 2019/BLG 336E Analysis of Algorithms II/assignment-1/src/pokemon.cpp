#include "pokemon.h"

map<string, vector<Attack>> Pokemon::ATTACKS = {{"pikachu", {
                                                              {"Thundershock", "-10", "100", "40", "0"}, 
                                                              {"Skull Bash", "-15", "70", "50", "0"},
                                                              {"Slam", "-20", "80", "60", "0"}, 
                                                              {"Skip", "100", "100", "0", "3"}
                                                            }
                                                },
                                                {"blastoise",{
                                                              {"Tackle", "-10", "100", "30", "0"}, 
                                                              {"Water Gun", "-20", "100", "40", "0"},
                                                              {"Bite", "-25", "100", "60", "0"},
                                                              {"Skip", "100", "100", "0", "3"}
                                                             }
                                                }};
string Pokemon::name(){
    return this->is_pikachu? "pikachu" : "blastoise";
}

string Pokemon::repr(){
    string initial = this->name().substr(0, 1);
    for (auto & c: initial) c = toupper(c);
    return initial + "_HP:" + to_string(health_points) + " "+ initial +"_PP:" + to_string(power_points);

}

Pokemon::Pokemon(){}
/*
:param name: name of the pokemon, either 'pikachu' or 'blastoise'
:param health_points: the integer that holds the initial HP of pokemon
:param power_points: the integer that holds the initial PP of pokemon
*/
Pokemon::Pokemon(string name, int health_points, int power_points){
    this->health_points = health_points;
    this->power_points = power_points;
    this->is_pikachu = name == "pikachu";
    if (name != "pikachu" && name!= "blastoise")
        throw "name of the pokemon should be 'pikachu' or 'blastoise'";
}

/* 
 *Returns list of all all attacks that the pokemon can do
*/
vector<Attack>& Pokemon::attacks(){
    return this->ATTACKS[name()];
}
/*
 *Takes an integer, level, and returns possible attacks for
 *that level
*/
vector<Attack> Pokemon::get_attacks(int level){
    vector<Attack> possible_attacks;
    for(auto attack:this->attacks()){
        if (attack.first_usage <= level && attack.cost <= power_points)
            possible_attacks.push_back(attack);
    }
    return possible_attacks;
}

Pokemon Pokemon::copy(){
    string name = this->name();
    return Pokemon(name, health_points, power_points);
}

/*
 *Attacks to the opponent with specified attack and do damage
 *if effective is True
*/
void Pokemon::attack(Pokemon& opponent, const Attack& attack, bool effective){
    this->power_points -= attack.cost;
    if (effective){
        opponent.health_points -= attack.damage;
        if (opponent.health_points < 0)
            opponent.health_points = 0;
    }
}


