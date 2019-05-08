#ifndef INGREDIENT_H
#define INGREDIENT_H
#include <iostream>
#include "helper_functions.h"
#include <map>
using namespace std;

class BaseIngredient{
    protected:
        string name;
        int item_count;
        double price;
    public:
        BaseIngredient(string, int, double);
        virtual double get_cost(int) const = 0;
        string get_name() const {return name;}
        int get_item_count() const{return item_count;}
        void set_item_count(int ic) {item_count = ic;} 
        double get_price() const {return price;}
};
class Ingredient: public BaseIngredient{
    private:
        char type;
        string unit;
    public:
        static map<char, string> unit_of_types;
        Ingredient(string name, string type, string item_count, string price);
        double get_cost(int amount) const {return amount * price;}
        char get_type() const {return type;}
        
};

#endif