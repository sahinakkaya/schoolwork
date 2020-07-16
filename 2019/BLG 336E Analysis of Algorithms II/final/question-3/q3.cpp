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
            std::cout << i->sourceNode << " --> " ;
            std::cout << i->destinationNode << " : " ;
            std::cout << setw(2) << i->weight << endl ;
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
    bool buildDPTable(){
        // Fill here
        
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
    
    void printShortestPathBetweenSourceAndDestination(){
        // Fill here
        
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
