/* @Author
* Student Name: Şahin Akkaya
* Student ID : 150170098
* Date: 09.05.2019 */

#ifndef ORDER_H
#define ORDER_H
#include <fstream>
#include <tuple>
#include <vector>
#include "ingredient.h"
#define NUMBER_OF_TABLES 5

class Order {
    vector<tuple<string, vector<tuple<string, int>>>> tables;

   public:
    Order(ifstream&);
    vector<tuple<string, vector<tuple<string, int>>>> get_tables() const { return tables; }
    void print();
};
#endif