#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <climits>

using namespace std;

struct Edge{
    int sourceNode;
    int destinationNode;
    int weight;
};

class Graph{
    int numberOfNodes;
    int numberOfEdges;
    vector<Edge> edges;

public:
    void setNumberOfNodes(int n){
        numberOfNodes = n;
    }
    int getNumberOfNodes(){
        return numberOfNodes;
    }
    void setNumberOfEdges(int n){
        numberOfEdges = n;
    }
    int getNumberOfEdges(){
        return numberOfEdges;
    }

    void AddEdge(int sourceNode, int destinationNode, int weight){
        Edge e = Edge();
        e.sourceNode = sourceNode;
        e.destinationNode = destinationNode;
        e.weight = weight;

        edges.push_back(e);
    }
    vector<Edge> getAllEdges(){
        return edges;
    }

    vector<Edge> getOutgoingEdges(int src){
        vector<Edge> outgoingEdges;

        for (Edge e : edges){
            if(e.sourceNode == src){
                outgoingEdges.push_back(e);
            }
        }

        return outgoingEdges;
    }

    int getWeightOfEdge(int src, int dst){
       int weight = 0;
       for (Edge e : edges){
           if(e.sourceNode == src && e.destinationNode == dst){
               cout << "weigth: " << e.weight << endl;
               weight = e.weight;
           }
       }

       return weight;
    }

    void printGraph(){
        cout << "************* Graph data *************" << endl;
        cout << "Number of total edges: " << numberOfEdges << endl;
        cout << "Number of total nodes: " << numberOfNodes << endl << endl;

        cout << "Source node --> Destination node : Edge weigth" << endl;
        for (std::vector<Edge>::const_iterator i = edges.begin(); i != edges.end(); ++i){
            cout << i->sourceNode << " --> " ;
            cout << i->destinationNode << " : " ;
            cout << setw(2) << i->weight << endl ;
        }
        cout << "**************************************" << endl << endl;
    }
};

class BellmanFord{
    Graph G;
    int sourceNode;
    int destinationNode;
    int** M;
    bool graphContainsNegativeWeightCycle;

public:
    void setGraph(Graph g){
        G = g;
    }
    Graph getGraph(){
        return G;
    }
    void setSourceNode(int s){
        sourceNode = s;
    }
    int getSourceNode(){
        return sourceNode;
    }
    void setDestinationNode(int t){
        destinationNode = t;
    }
    int getDestinationNode(){
        return destinationNode;
    }
    bool buildDPTable() {
        int num_of_nodes = G.getNumberOfNodes();
        int num_of_edges = G.getNumberOfEdges();

        M = new int*[num_of_nodes];
        M[0] = new int[num_of_nodes];

        int destination = getDestinationNode();
        for (int j = 0; j < num_of_nodes; j++) {
            if (j == destination)
            M[0][j] = 0;
            else
            M[0][j] = INT_MAX;
        }

        for (int i = 1; i <= num_of_nodes - 1; i++) {
            M[i] = new int[num_of_nodes];

            for (int j = 0; j < num_of_nodes; j++) M[i][j] = M[i - 1][j];

            for (int j = 0; j < num_of_edges; j++) {
            int u = G.getAllEdges()[j].sourceNode;
            int v = G.getAllEdges()[j].destinationNode;
            int weight = G.getAllEdges()[j].weight;

            if (M[i - 1][v] != INT_MAX and M[i - 1][v] + weight < M[i][u])
                M[i][u] = M[i - 1][v] + weight;
            }
        }

        for (int j = 0; j < num_of_edges; j++) {
            int u = G.getAllEdges()[j].sourceNode;
            int v = G.getAllEdges()[j].destinationNode;
            int weight = G.getAllEdges()[j].weight;

            if (M[num_of_nodes - 1][v] != INT_MAX and
                M[num_of_nodes - 1][v] + weight < M[num_of_nodes - 1][u]) {
                cout << "Graph contains negative weight cycle!" << endl;
                graphContainsNegativeWeightCycle = true;
                return false;
            }
        }
        graphContainsNegativeWeightCycle = false;
        return true;
    }

    void printDPTable(){
        if(!graphContainsNegativeWeightCycle){
            cout << endl << "Dynamic programming table: (shortest paths from each node to destination node): " << endl << endl;

            int numberOfNodes = G.getNumberOfNodes();

            for(int i = 0; i <= numberOfNodes; i++){
                for(int j = 0; j <= numberOfNodes; j++){
                    if(i == 0 && j == 0)
                        cout << "\t";
                    else if(i != 0 && j == 0)
                        cout << setw(10) << "Iteration-" << i - 1;
                    else if(i == 0 && j != 0)
                        cout << "\t" << "Node-" << j - 1 << " ";
                    else{
                        if(M[i - 1][j - 1] == INT_MAX)
                            cout << "\t " << "\u221E";
                        else
                            cout << "\t" << setw(2) << M[i - 1][j - 1];
                    }
                }
                cout << endl;
            }
            cout << endl;
        }
    }

    void printShortestPathBetweenSourceAndDestination() {
        int n = G.getNumberOfNodes();
        int source = getSourceNode();
        int destination = getDestinationNode();
        cout << "Shortest path value from " << source << " to " << destination << ": "
            << M[n - 1][sourceNode] << endl;

        int path_edges = 0;
        for (int i = 0; i < n - 1; i++) {
            if (M[i][source] != M[i + 1][source])
                path_edges = i + 1;
        }

        vector<int> path;
        path.push_back(source);

        for (int j = 0; j < path_edges; j++) {
            vector<Edge> v = G.getOutgoingEdges(source);
            for (int i = 0; (unsigned)i < v.size(); i++) {
                int s = v[i].sourceNode;
                int d = v[i].destinationNode;
                int weight = v[i].weight;
                if (weight + M[n - 1][d] == M[n - 1][source]) {
                    source = d;
                    path.push_back(source);
                }
            }
        }

        cout << "Shortest path value from " << source << " to " << destination << ": ";
        for (int i = 0; (unsigned)i < path.size(); i++) {
            cout << path[i];
            if ((unsigned)i != path.size() - 1) 
                cout << " -> ";
        }
        cout << endl;
    }
};

int main(int argc, char* argv[])
{
    if(argc > 1){
        Graph graph;

        //read graph data from file
        string inputFileName = argv[1];
        string line;
        ifstream infile(inputFileName);

        getline(infile, line);
        graph.setNumberOfNodes(stoi(line));
        getline(infile, line);
        graph.setNumberOfEdges(stoi(line));

        int src, dst, w;
        while (infile >> src >> dst >> w) {
           graph.AddEdge(src, dst, w);
        }

        graph.printGraph();

        BellmanFord bf;
        bf.setGraph(graph);

        int dstNode;
        int srcNode;

        cout << "Enter the destination node: ";
        cin >> dstNode;

        bf.setDestinationNode(dstNode);

        if(bf.buildDPTable()){
            bf.printDPTable();

            cout << "Enter a source node: ";
            cin >> srcNode;
            bf.setSourceNode(srcNode);

            bf.printShortestPathBetweenSourceAndDestination();
        }
    }
    else{
        cout << "Error: please provide a test file!" << endl;
    }

    return 0;
}
