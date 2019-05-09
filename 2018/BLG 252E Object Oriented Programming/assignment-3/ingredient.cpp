/* @Author
* Student Name: Şahin Akkaya
* Student ID : 150170098
* Date: 09.05.2019 */

#include "ingredient.h"

using namespace std;
/*
 /brief initialize the base class for ingredient
 /param name a string that corresponds to name of the ingredient
 /param item_count an integer that shows how much "name" ingredient in the stock
 /param price a double that corresponds to price per type of "name" ingredient
*/
BaseIngredient::BaseIngredient(string name, int item_count, double price){
    this->name = name;
    this->item_count = item_count;
    this->price = price;
}

map<char, string> Ingredient::unit_of_types = {{'1', "gram"}, {'2',""}, {'3',"ml"}};

/*
 /brief initiliaze Ingredient class
 /name a string that corresponds to name of the ingredient
 /type a string that corresponds to type of the ingredient: 1, 2 or 3
 /param item_count a string that shows how much "name" ingredient in the stock
 /param price a string that corresponds to price per type of "name" ingredient
*/
Ingredient::Ingredient(string name, string type, string item_count, string price): 
            BaseIngredient(name, stoi(item_count), stod(price))
{ 
    this->type = type[0];
    unit = unit_of_types[this->type];
}


