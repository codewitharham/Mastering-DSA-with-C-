#include <stdio.h>
#include <iostream>

struct Vertex {
    int data;
    int weight;
    Vertex* next;
};

struct Graph {
    int Vertices;
    Vertex* head;
};

Vertex* createVertex(int data, int weight) {
    Vertex* newVertex = new Vertex;
    newVertex->data = data;
    newVertex->weight = weight;
    newVertex->next = NULL; // Initialize the next pointer to NULL
    return newVertex;
}

void CreateGraph(Graph* g, int vertices) {
    g->Vertices = vertices;
    g->head = new Vertex[vertices];
    for (int i = 0; i < vertices; i++) {
        g->head[i].data = i; // Initialize the data for each vertex
        g->head[i].weight = 0; // Initialize the weight for each vertex
        g->head[i].next = NULL; // Initialize the next pointer to NULL
    }
}

void addEdge(Graph* g, int src, int dest, int weight) {
    Vertex* newVertex = createVertex(dest, weight);
    newVertex->next = g->head[src].next; // Point the new vertex to the current head of the source vertex
    g->head[src].next = newVertex; // Update the head of the source vertex to the new vertex
}

void printGraph(Graph* g) {
    for (int i = 0; i < g->Vertices; i++) {
        Vertex* temp = g->head[i].next; // Start from the first adjacent vertex
        std::cout << "Vertex " << g->head[i].data << ":";
        while (temp != NULL) {
            std::cout << " -> (" << temp->data << ", weight: " << temp->weight << ")"; // Print the adjacent vertex and its weight
            temp = temp->next; // Move to the next adjacent vertex
        }
        std::cout << std::endl;
    }
}

int main() {
    Graph g;
    int vertices;
    std::cout << "Enter the number of vertices: " << std::endl;
    std::cin >> vertices;

    CreateGraph(&g, vertices);

    int edges;
    std::cout << "Enter the number of edges: " << std::endl;
    std::cin >> edges;

    for (int i = 0; i < edges; i++) {
        int src, dest, weight;
        std::cout << "Enter edge (src dest weight): ";
        std::cin >> src >> dest >> weight;
        addEdge(&g, src, dest, weight);
    }

    printGraph(&g);

    return 0;
}