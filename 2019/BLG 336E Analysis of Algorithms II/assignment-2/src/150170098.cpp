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
    Solution j_hd = get_shortest_path(adj_matrix, jh, jd, num_of_nodes);
    Solution l_hd = get_shortest_path(adj_matrix, lh, ld, num_of_nodes);
//    int intersection_node = get_intersection_node(j_hd, l_hd);
    int intersection_node = -1;

    if (intersection_node == -1) {

        cout << "Joseph's path from hotel to destination" << endl;
        int j_duration = print_solution(j_hd);
//        cout << "Duration: " << j_duration << endl;

        cout << "--------------------------" << endl;
        cout << "Lucy's path from hotel to destination" << endl;
        int l_duration = print_solution(l_hd);
//        cout << "Duration: " << l_duration << endl;
        Solution j_dh = get_shortest_path(adj_matrix, jd, jh, num_of_nodes, j_duration + 30);
        Solution l_dh = get_shortest_path(adj_matrix, ld, lh, num_of_nodes, l_duration + 30);

//        intersection_node = get_intersection_node(j_dh, l_dh);
        if (intersection_node == -1){
            cout << "---------return-----------" << endl;
            cout << "Joseph's path from destination to hotel" << endl;
            j_duration = print_solution(j_dh);
            cout << "Duration: " << j_duration << endl;

            cout << "Lucy's path from destination to hotel" << endl;
            l_duration = print_solution(l_dh);
            cout << "Duration: " << l_duration << endl;


        }


    }


    return EXIT_SUCCESS;
}


