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
    // IMPLEMENT HERE
}

void Graph::initializePreflow(int source){
    // IMPLEMENT HERE
}

void Graph::push(int u, int v){
    // IMPLEMENT HERE
}

void Graph::relabel(int u){
    // IMPLEMENT HERE
}

int Graph::findMaxFlow(){
    // IMPLEMENT HERE
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