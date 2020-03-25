#include "pokemon.h"
#include <fstream>
#include <sstream>

map<string, vector<Attack>> Pokemon::ATTACKS = {{"pikachu", {}},
                                                {"blastoise",{}}};

vector<Attack> Pokemon::read_attacks_file(string name){
    string filename = name + ".txt";
    ifstream file(filename);
    if (file.fail())
    { // If cannot opened,
        cerr << "Cannot open file '" << filename << "'. No such file." << endl;
        throw "file not found";
    }
    string line; 
    getline(file, line);
    vector<Attack> attacks;
    for(; getline(file, line);)
    {
        stringstream ss(line);
        vector<string> result;
        while(ss.good()){
            string substr;
            getline(ss, substr, ',');
            result.push_back(substr);
        }
        string attack_name = result[0];
        string cost = result[1];
        string accuracy = result[2];
        string damage=result[3];
        string first_usage=result[4];
        attacks.push_back(Attack(attack_name, cost, accuracy, damage, first_usage));
    }  
    return attacks;
}

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
    if (ATTACKS[name].empty()){
        vector<Attack> attacks = read_attacks_file(name); 
        ATTACKS[name] = attacks;
    }
    this->read_attacks_file(name);
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


