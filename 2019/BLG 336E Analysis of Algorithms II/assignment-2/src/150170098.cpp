//
// Created by sahin on 22/04/2020 at 09:48
//

// 13 hours left.
#include <fstream>
#include <iostream>
#include "helper_functions.h"

using namespace std;

int main(int argc, char *argv[]){
    string filename = argv[1];
    ifstream file(filename);
    if (file.fail()) {  // If cannot opened,
        cerr << "Cannot open file '" << filename << "'. No such file." << endl;
        return EXIT_FAILURE;
    }
    int num_of_nodes;
    file >> num_of_nodes;
    int** adj_matrix = allocate_matrix(num_of_nodes);


    int jh, jd, lh, ld;
    file >> jh >> jd >> lh >> ld;
    int source, target, weight;

    while (file >> source >> target >> weight) {
        adj_matrix[source][target] = weight;
    }
    print_matrix(adj_matrix, num_of_nodes);

    file.close();
    return EXIT_SUCCESS;
}


