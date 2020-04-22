//
// Created by sahin on 22/04/2020.
//

#ifndef ASSIGNMENT_2_HELPER_FUNCTIONS_H
#define ASSIGNMENT_2_HELPER_FUNCTIONS_H

#include <vector>
using namespace std;
typedef vector<pair<int, int>> Solution;
int **allocate_matrix(int node_count);

void print_matrix(int **matrix, int length);

int minDistance(const int dist[], const bool sptSet[], int node_count);

void printPath(int parent[], int dist[], int j);

void printSolution(int dist[], int num_of_nodes,
                   int parent[], int src, int dst = -1);
int print_solution(Solution&);
int get_intersection_node(Solution&, Solution&);
Solution get_shortest_path(int **graph, int src, int dst, int num_of_nodes, int starting_time = 0);
Solution get_node_times(const int *parent, int *dist, int src, int j);


#endif //ASSIGNMENT_2_HELPER_FUNCTIONS_H
