/* @Author
* Student Name: Şahin Akkaya
* Student ID : 150170098
* Date: 09.05.2019 */

#ifndef MENU_H
#define MENU_H
#include "ingredient.h"
#include <fstream>
#include <vector>
#include <tuple>
using namespace std;
class Menu{
    string header;
    map<string, vector<tuple<string, int>>> menu;
    public:
        Menu(ifstream&);
        map<string, vector<tuple<string, int>>> get_menu() {return menu;}
        void print();
};
#endif