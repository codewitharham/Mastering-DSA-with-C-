#include <stdio.h>
#include <iostream>

struct Graph {
    int Vertices;
    int** adjMatrix;
};

void addEdge(Graph* g, int src, int dest, int weight) {
    g->adjMatrix[src][dest] = weight; // Set the weight of the edge from src to dest
    g->adjMatrix[dest][src] = weight; // Set the weight of the edge from dest to src (for undirected graph)
}

void printAdjMatrix(Graph* g) {
    for (int i = 0; i < g->Vertices; i++) {
        for (int j = 0; j < g->Vertices; j++) {
            std::cout << g->adjMatrix[i][j] << " "; // Print the weight at the current position in the adjacency matrix
        }
        std::cout << std::endl; // Move to the next line after printing each row of the adjacency matrix
    }
}


int main() {
    int vertices;
    std::cout << "Enter the number of vertices: " << std::endl;
    std::cin >> vertices;

    Graph g;
    g.Vertices = vertices;

    // Create a 2D array for the adjacency matrix
    g.adjMatrix = new int*[g.Vertices];
    for (int i = 0; i < g.Vertices; i++) {
        g.adjMatrix[i] = new int[g.Vertices];
    }

    // Initialize the adjacency matrix with 0s
    for (int i = 0; i < g.Vertices; i++) {
        for (int j = 0; j < g.Vertices; j++) {
            g.adjMatrix[i][j] = 0;
        }
    }

    int edges;
    std::cout << "Enter the number of edges: " << std::endl;
    std::cin >> edges;

    // Add edges to the graph with weights
    addEdge(&g, 0, 1, 5);
    addEdge(&g, 0, 2, 3);
    addEdge(&g, 1, 3, 8);
    addEdge(&g, 1, 5, 2);
    addEdge(&g, 2, 0, 3);

    // Print the adjacency matrix
    printAdjMatrix(&g);

    return 0;
}
