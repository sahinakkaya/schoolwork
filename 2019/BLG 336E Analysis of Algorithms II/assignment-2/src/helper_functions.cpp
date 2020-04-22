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

int min_distance(const int *dist, const bool *sptSet, int node_count) {
    int min = INT_MAX, min_index = 0;

    for (int v = 0; v < node_count; v++)
        if (!sptSet[v] && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
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

    int dist[num_of_nodes];

    bool sptSet[num_of_nodes];

    int parent[num_of_nodes];

    parent[src] = -1;
    for (int i = 0; i < num_of_nodes; i++) {
        dist[i] = INT_MAX;
        sptSet[i] = false;
    }
    dist[src] = starting_time;

    for (int count = 0; count < num_of_nodes - 1; count++) {
        int u = min_distance(dist, sptSet, num_of_nodes);
        sptSet[u] = true;

        for (int v = 0; v < num_of_nodes; v++) {
            if (!sptSet[v] && graph[u][v] &&
                dist[u] + graph[u][v] < dist[v]) {
                parent[v] = u;
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

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
        int temp = graph[current_node][next_node];
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
//        cout << "Found a path with length " << path_length << endl;
//        cout << "current path lenght is " << distance << endl;
        if (path_length < distance) {
            distance = path_length;
            r = path;
//            cout << "So we accept the new path" << endl;
        } else {
//            cout << "Current one is better" << endl;
        }
        graph[current_node][next_node] = temp;

        current_node = next_node;
        i--;
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

int get_duration(Solution &s) {
    if (s.empty())
        return INT_MAX;
    else
        return s.front().second;
}
