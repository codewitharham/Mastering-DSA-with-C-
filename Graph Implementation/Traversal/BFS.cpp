#include <iostream>

using namespace std;



struct vertex{
    int data;
    vertex* next;
};

struct graph{
    int V;
    vertex* head;
};

vertex* createVertex(int data){
    vertex* newVertex = new vertex;
    newVertex->data = data;
    newVertex->next = NULL; // Initialize the next pointer to NULL
    return newVertex;
}

void addEdge(graph* g, int src, int dest){
    vertex* newVertex = createVertex(dest);
    newVertex->next = g->head[src].next; // Point the new vertex to the current head of the source vertex
    g->head[src].next = newVertex; // Update the head of the source vertex to the new vertex
}




void printGraph(graph* g){
    for (int i = 0; i < g->V; i++) {
        vertex* temp = g->head[i].next; // Start from the first adjacent vertex
        cout << "Vertex " << g->head[i].data << ":";
        while (temp != NULL) {
            cout << " -> " << temp->data; // Print the adjacent vertex
            temp = temp->next; // Move to the next adjacent vertex
        }
        cout << endl;
    }
}



int main(){
    // Create a graph with 5 vertices
    graph undirectedGraph;
    undirectedGraph.V = 5;
    undirectedGraph.head = new vertex[undirectedGraph.V];
    for (int i = 0; i < undirectedGraph.V; i++) {
        undirectedGraph.head[i].data = i; // Initialize the data for each vertex
        undirectedGraph.head[i].next = NULL; // Initialize the next pointer to NULL
    }

    // Add edges to the graph
    addEdge(&undirectedGraph, 0, 1);
    addEdge(&undirectedGraph, 0, 2);
    addEdge(&undirectedGraph, 1, 0);
    addEdge(&undirectedGraph, 1, 3);
    addEdge(&undirectedGraph, 1, 5);

    // Print the graph
    printGraph(&undirectedGraph);

    return 0;
}