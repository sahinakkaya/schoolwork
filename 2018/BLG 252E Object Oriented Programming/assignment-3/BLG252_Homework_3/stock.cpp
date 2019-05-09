#include "stock.h"
#include "vector"
using namespace std;


Stock::Stock(ifstream& file){
    getline(file, header);
    //cout << header << endl;
    string line;
    while(getline(file, line)){
        vector<string> fields;
        split(line, "\t", fields, 4);
        Ingredient* ing = new Ingredient(fields[0],fields[1],fields[2],fields[3]);
        stock[fields[0]] = ing;
    }
    
};



bool Stock::has_enough_ingredient(string name, int amount){
    return stock[name]->get_item_count() >= amount;
}

bool Stock::has_enough(tuple<string, int> t, int a){
    string name = get<0>(t);
    int amount = get<1>(t) * a;
    return has_enough_ingredient(name, amount);
}

void Stock::update(string name, int amount){
    // self.stock[name].item_count -= amount
    int new_item_count = stock[name]->get_item_count() - amount;
    stock[name]->set_item_count(new_item_count);
}

double Stock::get_price(string name, int amount){
    // return self.stock[name].get_cost(amount)
    return stock[name]->get_cost(amount);
}

void Stock::print(FILE* file){
    FILE fp_old = *stdout;  // preserve the original stdout
    *stdout = *file;
    cout << header <<endl;
    for(auto const& x : stock){
        Ingredient* ing = x.second;
        cout << ing->get_name() << '\t' 
             << ing->get_type() << '\t' 
             << ing->get_item_count() << '\t'
             << ing->get_price() << endl;
    }
    *stdout=fp_old;
}

void Stock::write_to_file(const char* file_name){
    FILE* f = fopen(file_name, "w");
    print(f);
    fclose(f);
}