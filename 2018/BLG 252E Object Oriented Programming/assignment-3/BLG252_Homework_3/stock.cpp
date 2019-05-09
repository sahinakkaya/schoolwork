/* @Author
* Student Name: Şahin Akkaya
* Student ID : 150170098
* Date: 09.05.2019 */

#include "stock.h"
#include "vector"
using namespace std;

/*
 /brief initialize Stock with given file stream
 /param file a reference to input file stream that'll be used for initializing stock
*/
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
    
}

/*
 /brief give back dynamically allocated memory
*/
Stock::~Stock(){
    for(auto const& x:stock){
        delete x.second;
    }
}

/*
 /brief check if stock has enough ingredient with given name and amount
 /param name a string that corresponds to name of the ingredient
 /param amount an integer that is going to be compared with item_count of "name" ingredient
 /return true if item_count of "name" ingredient is greater than or equal to amount, false otherwise
*/
bool Stock::has_enough_ingredient(string name, int amount){
    return stock[name]->get_item_count() >= amount;
}

/*
 /brief check if stock has enough ingredient with given name and amount
 /param t a tuple that is consiting of string name and int amount respectively
 /param a an integer that is going to be multipled with amount
 /return true if item_count of "name" ingredient is greater than or equal to amount * a, false otherwise
*/
bool Stock::has_enough(tuple<string, int> t, int a){
    string name = get<0>(t);
    int amount = get<1>(t) * a;
    return has_enough_ingredient(name, amount);
}

/*
 /brief update the item_count of given "name" ingredient by reducing "amount" amount
 /name a string that corresponds to name of the ingredient
 /amount an integer that is going to be subtracted from item_count of "name" ingredient
*/
void Stock::update(string name, int amount){
    // self.stock[name].item_count -= amount
    int new_item_count = stock[name]->get_item_count() - amount;
    stock[name]->set_item_count(new_item_count);
}

/*
 /brief calculate and return price for "amount" amount of "name" ingredient
 /name a string that corresponds to name of the ingredient
 /amount an integer that corresponds to requested amount of "name" ingredient
 /return a double that is equal to price for "amount" amount of "name" ingredient
*/
double Stock::get_price(string name, int amount){
    return stock[name]->get_cost(amount);
}

/*
 /brief print the current stock information to the file
 /file a FILE pointer that stock information will be written, stdout by default.
*/
void Stock::print(FILE* file){
    FILE fp_old = *stdout;  
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
/*
 /brief create a file named "file_name" and print the stock information to it
 /file_name a character pointer that shows the name of the file that is going to created, "stock.txt" by default
*/
void Stock::write_to_file(const char* file_name){
    FILE* f = fopen(file_name, "w");
    print(f);
    fclose(f);
}