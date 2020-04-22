#include <iostream>
#include <iomanip>
#include <climits>
#include <stack>
#include "helper_functions.h"

using namespace std;

int **allocate_matrix(int node_count) {
    int **m = new int *[node_count];
    for (int i = 0; i < node_count; ++i) {
        m[i] = new int[node_count];
        for (int j = 0; j < node_count; j++)
            m[i][j] = 0;
    }
    return m;
}

void print_matrix(int **matrix, int length) {
    cout << "   ";
    for (int i = 0; i < length; i++)
        cout << setw(3) << setfill(' ') << i;
    cout << endl;
    for (int i = 0; i < length; i++) {
        cout << setw(3) << setfill(' ') << i;
        for (int j = 0; j < length; j++) {
            cout << setw(3) << setfill(' ') << matrix[i][j];
        }
        cout << endl;
    }
}

int minDistance(const int dist[], const bool sptSet[], int node_count) {
    // Initialize min value
    int min = INT_MAX, min_index = 0;

    for (int v = 0; v < node_count; v++)
        if (!sptSet[v] && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

void printPath(int parent[], int dist[], int j) {

    // Base Case : If j is source
    if (parent[j] == -1)
        return;
    printPath(parent, dist, parent[j]);

    printf("(%d: %d) ", j, dist[j]);
}

Solution get_node_times(const int *parent, int *dist, int src, int j) {
    Solution node_times;

    while (parent[j] != -1) {
        if (dist[j] == INT_MAX) {
            Solution no_solution;
            return no_solution;
        }
        node_times.push_back(make_pair(j, dist[j]));
        j = parent[j];
    }
    node_times.push_back(make_pair(src, dist[src]));
    return node_times;
}

void printSolution(int dist[], int num_of_nodes,
                   int parent[], int src, int dst) {
    printf("Vertex\t Distance\tPath");
    if (dst == -1) {
        for (int i = 0; i < num_of_nodes; i++) {
            if (i == src) {
                continue;
            }
            printf("\n%d -> %d \t\t %d\t%d ",
                   src, i, dist[i], src);
            printPath(parent, dist, i);
        }
    } else {
        printf("\n%d -> %d \t\t %d\t%d ",
               src, dst, dist[dst], src);
        printPath(parent, dist, dst);
    }
}

int print_solution(Solution &solution) {
    int duration = 0;
    if (solution.empty()) {
        cout << "No solution" << endl;
        return INT_MAX;
    } else {
        for (auto pair = solution.rbegin(); pair != solution.rend(); pair++) {
            cout << "Node: " << pair->first << " Time: " << pair->second << endl;
            duration = pair->second;
        }
    }
    return duration;
}


Solution get_shortest_path(int **graph, int src, int dst, int num_of_nodes, int starting_time) {

    // The output array. dist[i]
    // will hold the shortest
    // distance from src to i
    int dist[num_of_nodes];

    // sptSet[i] will true if vertex
    // i is included / in shortest
    // path tree or shortest distance
    // from src to i is finalized
    bool sptSet[num_of_nodes];

    // Parent array to store
    // shortest path tree
    int parent[num_of_nodes];

    // Initialize all distances as
    // INFINITE and stpSet[] as false
    parent[src] = -1;
    for (int i = 0; i < num_of_nodes; i++) {
        dist[i] = INT_MAX;
        sptSet[i] = false;
    }

    // Distance of source vertex
    // from itself is always 0
    dist[src] = starting_time;

    // Find shortest path
    // for all vertices
    for (int count = 0; count < num_of_nodes - 1; count++) {
        // Pick the minimum distance
        // vertex from the set of
        // vertices not yet processed.
        // u is always equal to src
        // in first iteration.
        int u = minDistance(dist, sptSet, num_of_nodes);

        // Mark the picked vertex
        // as processed
        sptSet[u] = true;

        // Update dist value of the
        // adjacent vertices of the
        // picked vertex.
        for (int v = 0; v < num_of_nodes; v++) {
            // Update dist[v] only if is
            // not in sptSet, there is
            // an edge from u to v, and
            // total weight of path from
            // src to v through u is smaller
            // than current value of
            // dist[v]
            if (!sptSet[v] && graph[u][v] &&
                dist[u] + graph[u][v] < dist[v]) {
                parent[v] = u;
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    // print the constructed
    // distance array
//    printSolution(dist, num_of_nodes, parent, src, dst);
    auto solution = get_node_times(parent, dist, src, dst);
    return solution;
}

Solution select_shortest_path(int **graph, int src, int dst, int num_of_nodes, int starting_time, int intersection_node,
                              Solution &s) {
    int distance = INT_MAX;
    int i = (int) s.size() - 1;
    int current_node = s[i].first;
    Solution path, r;
    while (current_node != intersection_node) {
//        cout << "removing edge ";
        int next_node = s[i - 1].first;
//        cout << current_node << " " << next_node << endl;
//        return r;
        int temp = graph[current_node][next_node];
//        cout << temp << endl;
        graph[current_node][next_node] = 0;
        path = get_shortest_path(graph, src, dst, num_of_nodes, starting_time);
        if (path.empty()) {
//            cout << "no sol!!!" << endl;
            graph[current_node][next_node] = temp;
            current_node = next_node;
            i--;
            continue;
        }
        int path_length = path[0].second;
        cout << "Found a path with length " << path_length << endl;
        cout << "current path lenght is " << distance << endl;
        if (path_length < distance) {
            distance = path_length;
            r = path;
            cout << "So we accept the new path" << endl;
        } else {
            cout << "Current one is better" << endl;
        }
        graph[current_node][next_node] = temp;

        current_node = next_node;
        i--;
    }
    if (r.empty()) {
        cout << "no solution, fall back to default one" << endl;
        r = get_shortest_path(graph, src, dst, num_of_nodes, starting_time);
    }
    return r;

}


int get_intersection_node(Solution &first, Solution &second) {
    int time = 0;
    int f = (int) first.size() - 1;
    int s = (int) second.size() - 1;
    while (f > 0 or s > 0) {
        int ftime = first[f].second;
        int stime = second[s].second;

        time = min(ftime, stime);
        if (ftime == stime) {
            int fnode = first[f].first;
            int snode = second[s].first;
            if (fnode == snode) {
                return fnode;
            }
        }
        if (time == ftime)
            f -= 1;
        else
            s -= 1;
    }
    return -1;

}
