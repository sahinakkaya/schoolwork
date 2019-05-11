/* @Author
* Student Name: Şahin Akkaya
* Student ID : 150170098
* Date: 09.05.2019 */

#include "menu.h"
#include "helper_functions.h"
using namespace std;

/*
 /brief initialize Menu with given file stream
 /param file a reference to input file stream that'll be used for initializing Menu
*/
Menu::Menu(ifstream& file) {
    getline(file, header);
    vector<string> units;
    for (auto const& x : Ingredient::unit_of_types) {
        units.push_back(x.second);
    }
    string line;
    while (getline(file, line)) {
        vector<string> fields;
        split(line, "\t", fields, 2);
        vector<tuple<string, int>> ingredient_list;
        if (fields[1] == "N/A") {
            ingredient_list.push_back(make_tuple(fields[0], 1));
            menu[fields[0]] = ingredient_list;
        } else {
            vector<string> ingredients;
            split(fields[1], ", ", ingredients, -1);
            for (auto const& ingredient : ingredients) {
                vector<string> items;
                split(ingredient, " ", items, -1);
                int required_amount = stoi(items[0]);
                string ingredient_name;
                if (vector_contains(units, items[1])) {
                    ingredient_name = join(" ", items, 2);
                } else {
                    ingredient_name = join(" ", items, 1);
                }
                ingredient_list.push_back(make_tuple(ingredient_name, required_amount));
            }
            menu[fields[0]] = ingredient_list;
        }
    }
}
/*
 /brief print menu
*/
void Menu::print() {
    for (auto const& x : menu) {
        cout << x.first << "\t";
        vector<tuple<string, int>> v = x.second;
        for (auto const& y : v) {
            cout << get<0>(y) << " " << get<1>(y) << ", ";
        }
        cout << endl;
    }
}