/* @Author
* Student Name: Şahin Akkaya
* Student ID : 150170098
* Date: 09.05.2019 */

#ifndef STOCK_H
#define STOCK_H
#include "ingredient.h"
#include <fstream>
#include <vector>
#include <tuple>
using namespace std;

class Stock{
    string header;
    map<string, Ingredient*> stock;
    bool has_enough_ingredient(string, int);
    public:
        Stock(ifstream&);
        bool has_enough(tuple<string, int>, int);
        void update(string, int);
        double get_price(string, int);
        void print(FILE* file = stdout);
        void write_to_file(const char* filename="stock.txt");
};
#endif