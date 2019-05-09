#include "order.h"
using namespace std;
/*
 /brief initialize Order with given file stream
 /param file a reference to input file stream that'll be used for initializing Order
*/
Order::Order(ifstream& file){
    int i = 0;
    while (i++ < NUMBER_OF_TABLES){
        string table_name;
        getline(file, table_name);
        if (table_name == ""){
            break;
        }
        string line;
        getline(file,line);
        int number_of_orders = stoi(line);
        vector<tuple<string, int>> orders;
        while (number_of_orders--){
            getline(file, line);
            vector<string> fields;
            split(line, " ",fields, -1);
            int amount = stoi(fields[0]);
            string name = join(" ", fields,1);
            orders.push_back(make_tuple(name, amount));
        }
        tables.push_back(make_tuple(table_name, orders));
    }
}
/*
 /brief print all the orders with their table names
*/
void Order::print(){
    for(auto const& table: tables){
        string table_name = get<0>(table);
        vector<tuple<string, int>> orders = get<1>(table);
        cout << table_name << endl;
        for(auto const& order: orders){
            string name = get<0>(order);
            int amount = get<1>(order);
            cout << amount << " " << name << endl;
        }
    }
}