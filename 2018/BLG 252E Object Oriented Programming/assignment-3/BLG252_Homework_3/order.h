#ifndef ORDER_H
#define ORDER_H
#include "ingredient.h"
#include <vector>
#include <tuple>
#include <fstream>
#define NUMBER_OF_TABLES 5

class Order{
    vector<tuple<string, vector<tuple<string, int>>>> tables;

    public:
        Order(ifstream&);
        void print();
};
#endif