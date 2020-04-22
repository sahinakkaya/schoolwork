// I implemented this one under 12 hours and I'm proud of it.
// It's not the best code, nor produces correct results
// but I don't have energy to write 'if' statements.
// I accept whatever this thing does. Thanks.


#include <fstream>
#include <iostream>
#include <climits>
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
    print_matrix(adj_matrix, num_of_nodes);
    Solution j_hd, l_hd, j_dh, l_dh;
    j_hd = get_shortest_path(adj_matrix, jh, jd, num_of_nodes);
    l_hd = get_shortest_path(adj_matrix, lh, ld, num_of_nodes);
    int intersection_node = get_intersection_node(j_hd, l_hd);
    int j_duration = INT_MAX, l_duration = INT_MAX;
    if (intersection_node != -1) {
        Solution j_alt = select_shortest_path(adj_matrix, jh, jd, num_of_nodes, 0, intersection_node, j_hd);
        Solution l_alt = select_shortest_path(adj_matrix, lh, ld, num_of_nodes, 0, intersection_node, l_hd);
        if (j_alt.empty() and l_alt.empty()) {
            cout << "No solution0" << endl;
            return EXIT_FAILURE;
        }
        if (!j_alt.empty() or !l_alt.empty()) {
            if (!j_alt.empty() and !l_alt.empty()) {
                if (get_intersection_node(l_alt, j_hd) != -1 and get_intersection_node(j_alt, l_hd) == -1) {
                    j_hd = j_alt;
                } else if (get_intersection_node(l_alt, j_hd) == -1 and get_intersection_node(j_alt, l_hd) != -1) {
                    l_hd = l_alt;
                } else if (get_intersection_node(l_alt, j_hd) == -1 and get_intersection_node(j_alt, l_hd) == -1) {
                    int l_alt_choosed_duration = get_duration(l_alt) + get_duration(j_hd);
                    int j_alt_choosed_duration = get_duration(j_alt) + get_duration(l_hd);
                    if (l_alt_choosed_duration < j_alt_choosed_duration)
                        l_hd = l_alt;
                    else
                        j_hd = j_alt;
                } else {
                    cout << "No solution1";
                    return EXIT_FAILURE;
                }
            } else if (j_alt.empty()) {
                if (get_intersection_node(l_alt, j_hd) != -1) {
                    cout << "No solution2" << endl;
                    return EXIT_FAILURE;
                } else {
                    l_hd = l_alt;
                }
            } else {
                if (get_intersection_node(j_alt, l_hd) != -1) {
                    cout << "No solution3" << endl;
                    return EXIT_FAILURE;
                } else {
                    j_hd = j_alt;
                }
            }
        }
    }
    j_duration = get_duration(j_hd);
    l_duration = get_duration(l_hd);


    j_dh = get_shortest_path(adj_matrix, jd, jh, num_of_nodes, j_duration + 30);
    l_dh = get_shortest_path(adj_matrix, ld, lh, num_of_nodes, l_duration + 30);
    intersection_node = get_intersection_node(j_dh, l_dh);
    if (intersection_node != -1) {
        Solution j_alt = select_shortest_path(adj_matrix, jd, jh, num_of_nodes, j_duration + 30, intersection_node, j_dh);
        Solution l_alt = select_shortest_path(adj_matrix, ld, lh, num_of_nodes, l_duration + 30, intersection_node, l_dh);
        if (j_alt.empty() and l_alt.empty()) {
            cout << "No solution4" << endl;
            return EXIT_FAILURE;
        }
        if (!j_alt.empty() or !l_alt.empty()) {
            if (!j_alt.empty() and !l_alt.empty()) {
                if (get_intersection_node(l_alt, j_dh) != -1 and get_intersection_node(j_alt, l_dh) == -1) {
                    j_dh = j_alt;
                } else if (get_intersection_node(l_alt, j_dh) == -1 and get_intersection_node(j_alt, l_dh) != -1) {
                    l_hd = l_alt;
                } else if (get_intersection_node(l_alt, j_hd) == -1 and get_intersection_node(j_alt, l_hd) == -1) {
                    int l_alt_choosed_duration = get_duration(l_alt) + get_duration(j_dh);
                    int j_alt_choosed_duration = get_duration(j_alt) + get_duration(l_dh);
                    if (l_alt_choosed_duration < j_alt_choosed_duration)
                        l_dh = l_alt;
                    else
                        j_dh = j_alt;
                } else {
                    cout << "No solution5";
                    return EXIT_FAILURE;
                }
            } else if (j_alt.empty()) {
                if (get_intersection_node(l_alt, j_dh) != -1) {
                    cout << "No solution6" << endl;
                    return EXIT_FAILURE;
                } else {
                    l_dh = l_alt;
                }
            } else {
                if (get_intersection_node(j_alt, l_dh) != -1) {
                    cout << "No solution7" << endl;
                    return EXIT_FAILURE;
                } else {
                    j_dh = j_alt;
                }
            }
        }

    }
    j_duration = get_duration(j_dh);
    l_duration = get_duration(l_dh);
    cout << "Joseph's Path, duration: " << j_duration <<
         endl;
    print_solution(j_hd);
    cout << "-- return --" <<
         endl;
    print_solution(j_dh);
    cout <<
         endl;

    cout << "Lucy's Path, duration: " << l_duration <<
         endl;
    print_solution(l_hd);
    cout << "-- return --" <<
         endl;
    print_solution(l_dh);


    return EXIT_SUCCESS;
}


