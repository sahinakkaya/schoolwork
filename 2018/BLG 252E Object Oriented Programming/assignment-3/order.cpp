/* @Author
* Student Name: Şahin Akkaya
* Student ID : 150170098
* Date: 09.05.2019 */

#include "order.h"
#include "helper_functions.h"
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
        int number_of_lines_to_read = stoi(line);
        vector<tuple<string, int>> orders;
        while (number_of_lines_to_read--){
            getline(file, line);
            vector<string> fields;
            split(line, " ",fields, -1);
            string order_name = join(" ", fields,1);
            int number_of_orders = stoi(fields[0]);
            orders.push_back(make_tuple(order_name, number_of_orders));
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
            string order_name = get<0>(order);
            int number_of_orders = get<1>(order);
            cout << number_of_orders << " " << order_name << endl;
        }
    }
}