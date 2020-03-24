#include "attack.h"
Attack::Attack(string name, string cost, string accuracy, string damage, string first_usage){
    this->name = name;
    this->cost = -stoi(cost);
    this->accuracy = stod(accuracy) / 100;
    this->inaccuracy = 1 - this->accuracy;
    this->damage = stoi(damage);
    this->first_usage = stoi(first_usage);
}

// class Attack:
//     """A class to represent an attack"""

//     def __init__(self, name: str, cost: str,
//                  accuracy: str, damage: str, first_usage: str) -> None:
//         """
//         :param name: name of the attack
//         :param cost: the integer that will be decreased from attacker's pp
//         :param accuracy: the probability that the attack will succeed (0-100)
//         :param damage: the integer that will be decreased from defender's hp
//                        if the attack is succeeded
//         :param first_usage: the first round where the attack may be used
//         """
//         self.name = name
//         self.cost = -int(cost)
//         self.accuracy = int(accuracy) / 100
//         self.inaccuracy = 1 - self.accuracy
//         self.damage = int(damage)
//         self.first_usage = int(first_usage)

//     def __repr__(self):
//         return f"{self.name}, {self.cost}, {self.accuracy}, " 
//                f"{self.damage}, {self.first_usage}"