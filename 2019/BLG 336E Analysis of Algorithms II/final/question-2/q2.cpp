#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>

using namespace std;

class Graph{
    vector <vector<int>> capacity;
    vector <vector<int>> flow;
    int nodeCount;
    vector <int> excess;
    vector <int> height; 
    public:
    void addCapacity(int, int, int);
    void push(int, int);
    void relabel(int);
    void initializePreflow(int);
    int overflowingVertex();
    int findMaxFlow();
    Graph(int);
    ~Graph();
};

Graph::Graph(int n){
    nodeCount = n;
    capacity.assign(nodeCount, vector<int>(nodeCount, 0));
}

void Graph::addCapacity(int from, int to, int cap){
    capacity[from][to] = cap;
}

int Graph::overflowingVertex(){
    for(int i=1;i<nodeCount-1;i++){
        if (excess[i]>0)
            return i;
    }
    return 0; // 0th node is source, it can't overflow so this is OK
}

void Graph::initializePreflow(int source){
    for(int i=0; i<nodeCount; i++){
        height.push_back(0);
        excess.push_back(0);
    }
    flow.assign(nodeCount, vector<int>(nodeCount, 0));
    height[source] = nodeCount;

    for(int dest=0;dest<nodeCount;dest++){
        flow[source][dest] = capacity[source][dest];
        flow[dest][source] = -capacity[source][dest];
        excess[dest] = capacity[source][dest];
        excess[source] = excess[source] - capacity[source][dest];
    }
    
}

void Graph::push(int u, int v){
    int delta = min(excess[u], capacity[u][v] - flow[u][v]);
    flow[u][v] += delta;
    flow[v][u] -= delta;
    excess[u] -= delta;
    excess[v] += delta; 
}

void Graph::relabel(int u){
    int min = INT32_MAX;
    for(int v=0; v<nodeCount;v++){
        int cf = capacity[u][v] - flow[u][v];
        if (cf>0 and height[v]<min)
            min = height[v];
    }
    height[u] = min + 1;
}

int Graph::findMaxFlow(){
    int u;
    while(u=overflowingVertex()){
        bool pushed=false;
        for(int v =0;v<nodeCount;v++){
            int cf = capacity[u][v] - flow[u][v];
            if (cf>0 and height[u]>=height[v]+1){
                push(u, v);
                pushed=true;
            }
        }
        if (not pushed)
            relabel(u);       
    }
    return excess.back();
}

Graph::~Graph(){

}

int main(int argumentNumber, char *arguments[]){
    int nodeCount;
    string filename = arguments[1];
    string tempString;
    int temp, from, to, flow;
    
    ifstream file;
    file.open(filename);
    file >> nodeCount;
    Graph graph(nodeCount);
    file >> tempString >> tempString >> tempString;
    while(file.good()){
        file >> from >> to >> flow;
        graph.addCapacity(from, to, flow);
    }
    graph.initializePreflow(0); // 0th node is source
    cout << "Maximum flow: " << graph.findMaxFlow() << endl; 
    return 0;
}