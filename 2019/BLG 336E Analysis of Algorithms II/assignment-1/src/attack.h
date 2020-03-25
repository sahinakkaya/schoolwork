#ifndef ATTACK_H
#define ATTACK_H
#include <iostream>

using namespace std;


class Attack {
    public:
        string name;
        int cost;
        double accuracy;
        double inaccuracy;
        int damage;
        int first_usage;
        Attack(string, string, string, string, string);
        string repr();
};
#endif