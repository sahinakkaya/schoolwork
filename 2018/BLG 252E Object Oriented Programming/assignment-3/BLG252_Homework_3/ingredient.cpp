#include "ingredient.h"

using namespace std;

BaseIngredient::BaseIngredient(string name, int item_count, double price){
    this->name = name;
    this->item_count = item_count;
    this->price = price;
}

map<char, string> Ingredient::unit_of_types = {{'1', "gram"}, {'2',""}, {'3',"ml"}};
Ingredient::Ingredient(string name, string type, string item_count, string price): 
            BaseIngredient(name, stoi(item_count), stod(price))
{ 
    this->type = type[0];
    unit = unit_of_types[this->type];
}


