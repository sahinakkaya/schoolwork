#include <iostream>
#include <iomanip>
#include <climits>
using namespace std;

int** allocate_matrix(int node_count){
    int** m = new int*[node_count];
    for(int i = 0; i < node_count; ++i) {
        m[i] = new int[node_count];
        for(int j = 0; j<node_count;j++)
            m[i][j] = 0;
    }
    return m;
}

void print_matrix(int** matrix, int length){
    cout << "   ";
    for(int i =0;i<length;i++)
        cout<<setw(3)<<setfill(' ') <<i;
    cout << endl;
    for(int i =0;i<length;i++){
        cout  << setw(3)<<setfill(' ') <<i;
        for(int j=0; j<length;j++){
            cout << setw(3)<<setfill(' ') <<matrix[i][j];
        }
        cout << endl;
    }
}

int minDistance(int dist[], bool sptSet[], int node_count)
{
    // Initialize min value
    int min = INT_MAX, min_index=0;

    for (int v = 0; v < node_count; v++)
        if (!sptSet[v]  && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}
void printPath(int parent[], int dist[], int j)
{

    // Base Case : If j is source
    if (parent[j] == - 1)
        return;

    printPath(parent, dist,parent[j]);

    printf("(%d: %d) ", j, dist[j]);
}
void printSolution(int dist[], int num_of_nodes,
                  int parent[])
{
    int src = 0;
    printf("Vertex\t Distance\tPath");
    for (int i = 1; i < num_of_nodes; i++)
    {
        printf("\n%d -> %d \t\t %d\t\t%d ",
               src, i, dist[i], src);
        printPath(parent, dist, i);
    }
}


void get_shortest_path(int** graph, int src, int num_of_nodes)
{

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
    for (int i = 0; i < num_of_nodes; i++)
    {
        parent[0] = -1;
        dist[i] = INT_MAX;
        sptSet[i] = false;
    }

    // Distance of source vertex
    // from itself is always 0
    dist[src] = 0;

    // Find shortest path
    // for all vertices
    for (int count = 0; count < num_of_nodes - 1; count++)
    {
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
        for (int v = 0; v < num_of_nodes; v++)

            // Update dist[v] only if is
            // not in sptSet, there is
            // an edge from u to v, and
            // total weight of path from
            // src to v through u is smaller
            // than current value of
            // dist[v]
            if (!sptSet[v] && graph[u][v] &&
                dist[u] + graph[u][v] < dist[v])
            {
                parent[v] = u;
                dist[v] = dist[u] + graph[u][v];
            }
    }

    // print the constructed
    // distance array
    printSolution(dist, num_of_nodes, parent);
}
