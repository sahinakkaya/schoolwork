#include <iostream>
using namespace std;
class Ingredient{
    protected:
        string name;
        char type;
        int item_count;
        double price;
    public:
        Ingredient(string, char, int, double);
        double get_cost(int amount) {return amount*price;}
        
};