#include <iostream>

using namespace std;


struct graph{
    int V;
    int* adjMatrix;
};

void addEdge(graph* g, int src, int dest){
    g->adjMatrix[src * g->V + dest] = 1; // Mark the edge from src to dest
    g->adjMatrix[dest * g->V + src] = 1; // Mark the edge from dest to src (for undirected graph)
}

void printAdjMatrix(graph* g){
    for (int i = 0; i < g->V; i++) {
        for (int j = 0; j < g->V; j++) {
            cout << g->adjMatrix[i * g->V + j] << " "; // Print the value at the current position in the adjacency matrix
        }
        cout << endl; // Move to the next line after printing each row of the adjacency matrix
    }
}


int main(){

    // Get the number of vertices from the user

    int vertices;
    cout << "Enter the number of vertices: " << endl;
    cin >> vertices;

    // Create an adjacency matrix
    graph undirectedGraph;

    undirectedGraph.V = vertices;

    // create a 2D array for the adjacency matrix
    undirectedGraph.adjMatrix = new int[undirectedGraph.V * undirectedGraph.V];

    // Initialize the adjacency matrix with 0s
    for (int i = 0; i < undirectedGraph.V; i++) {
        for (int j = 0; j < undirectedGraph.V; j++) {
            undirectedGraph.adjMatrix[i * undirectedGraph.V + j] = 0;
        }
    }

    // Get the number of edges from the user
    int edges;
    cout << "Enter the number of edges: " << endl;
    cin >> edges;

    // Add edges to the graph
    addEdge(&undirectedGraph, 0, 1);
    addEdge(&undirectedGraph, 0, 2);
    addEdge(&undirectedGraph, 1, 0);
    addEdge(&undirectedGraph, 1, 3);
    addEdge(&undirectedGraph, 1, 5);
    addEdge(&undirectedGraph, 2, 0);
    addEdge(&undirectedGraph, 2, 6);
    addEdge(&undirectedGraph, 3, 1);
    addEdge(&undirectedGraph, 3, 4);
    addEdge(&undirectedGraph, 3, 5);
    addEdge(&undirectedGraph, 4, 3);
    addEdge(&undirectedGraph, 4, 6);
    addEdge(&undirectedGraph, 4, 5);
    addEdge(&undirectedGraph, 5, 1);
    addEdge(&undirectedGraph, 5, 3);
    addEdge(&undirectedGraph, 5, 4);
    addEdge(&undirectedGraph, 6, 2);
    addEdge(&undirectedGraph, 6, 4);
    



    // Print the adjacency matrix
    cout << "Adjacency Matrix:" << endl;
    printAdjMatrix(&undirectedGraph);


    return 0;
}