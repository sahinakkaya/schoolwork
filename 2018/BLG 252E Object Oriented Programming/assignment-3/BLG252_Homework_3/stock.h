#include "ingredient.h"
#include <fstream>
#include <vector>
using namespace std;

class Stock{
    string header;
    map<string, Ingredient*> stock;
/*     void split(string, char, vector<string>&); */
    public:
        Stock(ifstream&);
        bool has_enough_ingredient(string, int);
        void update(string, int);
        double get_price(string, int);
        void print(FILE*);
        void write_to_file(const char* filename="stock.txt");
};