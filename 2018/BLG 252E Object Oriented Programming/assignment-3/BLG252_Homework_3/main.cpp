#include "stock.h"
#include "menu.h"
#include "order.h"
using namespace std;


int main(){
    string file_names[] = {"stock", "menu", "order"};
    map <string, ifstream*> files;
    if(!open_files(file_names, 3, files)) // If cannot open any of the files
        return EXIT_FAILURE;
    
    Stock s(*files["stock"]);
    //s.write_to_file();
    //s.print();
    Menu m(*files["menu"]);
    //m.print();
    Order o(*files["order"]);
    o.print();


    close_files(file_names, 3, files);
    return EXIT_SUCCESS;

}


