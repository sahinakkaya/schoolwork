//
// Created by sahin on 22/04/2020 at 09:48
//

// 9 hours left. I'm listening Beethoven's 9th Symphony at the
// the same time and enjoying my life :D
// https://youtu.be/t3217H8JppI?t=3048
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


    int lh, ld, jh, jd;
    file >> jh >> jd >> lh >> ld;
    int source, target, weight;

    while (file >> source >> target >> weight) {
        adj_matrix[source][target] = weight;
    }
    print_matrix(adj_matrix, num_of_nodes);
    get_shortest_path(adj_matrix, ld, lh, num_of_nodes, 48);
    file.close();
    return EXIT_SUCCESS;
}


