//
// Created by sahin on 22/04/2020.
//

#ifndef ASSIGNMENT_2_HELPER_FUNCTIONS_H
#define ASSIGNMENT_2_HELPER_FUNCTIONS_H
int** allocate_matrix(int node_count);
void print_matrix(int** matrix, int length);
int minDistance(int dist[], bool sptSet[], int node_count);
void printPath(int parent[], int dist[], int j);
void printSolution(int dist[], int num_of_nodes,
                   int parent[]);
void get_shortest_path(int** graph, int src, int num_of_nodes);
#endif //ASSIGNMENT_2_HELPER_FUNCTIONS_H
