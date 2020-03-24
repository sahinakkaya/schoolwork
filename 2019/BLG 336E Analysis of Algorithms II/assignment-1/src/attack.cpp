#include "attack.h"
/*
:param name: name of the attack
:param cost: the integer that will be decreased from attacker's pp
:param accuracy: the probability that the attack will succeed (0-100)
:param damage: the integer that will be decreased from defender's hp
        if the attack is succeeded
*/
Attack::Attack(string name, string cost, string accuracy, string damage, string first_usage){
    this->name = name;
    this->cost = -stoi(cost);
    this->accuracy = stod(accuracy) / 100;
    this->inaccuracy = 1 - this->accuracy;
    this->damage = stoi(damage);
    this->first_usage = stoi(first_usage);
}

string Attack::repr(){
    string r = name + ", " + to_string(cost) + ", " + to_string(accuracy) 
                + ", " + to_string(damage) + ", " + to_string(first_usage);
    return r;
}