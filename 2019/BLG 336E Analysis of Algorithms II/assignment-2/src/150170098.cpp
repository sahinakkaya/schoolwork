//
// Created by sahin on 22/04/2020 at 09:48
//

// 8 hours left. I'm listening The Best of Mozart at the
// the same time and enjoying my life :D :D
// https://youtu.be/Rb0UmrCXxVA?t=3410
#include <fstream>
#include <iostream>
#include "helper_functions.h"

using namespace std;

int main(int argc, char *argv[]) {
    string filename = argv[1];
    ifstream file(filename);
    if (file.fail()) {  // If cannot opened,
        cerr << "Cannot open file '" << filename << "'. No such file." << endl;
        return EXIT_FAILURE;
    }
    int num_of_nodes;
    file >> num_of_nodes;
    int **adj_matrix = allocate_matrix(num_of_nodes);


    int lh, ld, jh, jd;
    file >> jh >> jd >> lh >> ld;
    int source, target, weight;

    while (file >> source >> target >> weight) {
        adj_matrix[source][target] = weight;
    }
    file.close();
//    print_matrix(adj_matrix, num_of_nodes);
    auto solution = get_shortest_path(adj_matrix, jd, jh, num_of_nodes, 48);
    if (solution.empty()) {
        cout << "No solution" << endl;
    } else {
        while (!solution.empty()) {
            auto pair = solution.top();
            solution.pop();
            cout << pair.first << ": " << pair.second << " ";
        }
    }
    return EXIT_SUCCESS;
}


