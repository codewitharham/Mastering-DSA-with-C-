#include <iostream>
using namespace std;

struct vertex
{
    int data;
    vertex *next;
};

struct graph
{
    int V;
    vertex *head;
};

vertex *createVertex(int data)
{
    vertex *newVertex = new vertex;
    newVertex->data = data;
    newVertex->next = NULL; // Initialize the next pointer to NULL
    return newVertex;
}

void addEdge(graph *g, int src, int dest)
{
    // check if src and dest are within the valid range of vertices
    if (src < 0 || src >= g->V || dest < 0 || dest >= g->V)
    {
        cout << "the src and dest vertices must be between 0 and " << g->V - 1 << endl;
        throw runtime_error("Source or destination vertex is out of bounds.");
        return;
    }

    vertex *newVertex = createVertex(dest);
    newVertex->next = g->head[src].next; // Point the new vertex to the current head of the source vertex
    g->head[src].next = newVertex;       // Update the head of the source vertex to the new vertex
}

bool Graph_findPath(graph *g, int current, int endVertex, bool *visited, vertex *&path)
{
    visited[current] = true;

    if (current == endVertex)
    {
        // Append end vertex to path
        vertex *newNode = createVertex(current);
        newNode->next = path;
        path = newNode;
        return true;
    }

    vertex *neighbor = g->head[current].next;
    while (neighbor != NULL)
    {
        int adj = neighbor->data;
        if (!visited[adj])
        {
            if (Graph_findPath(g, adj, endVertex, visited, path))
            {
                
                vertex *newNode = createVertex(current); //
                newNode->next = path;
                path = newNode;
                return true;
            }
        }
        neighbor = neighbor->next;
    }

    return false; // No path found from this vertex
}

int main()
{
    // Create a graph with n vertices
    graph undirectedGraph;
    cout << "Enter the number of vertices: " << endl;
    cin >> undirectedGraph.V;
    undirectedGraph.head = new vertex[undirectedGraph.V];
    for (int i = 0; i < undirectedGraph.V; i++)
    {
        undirectedGraph.head[i].data = i;    // Initialize the data for each vertex
        undirectedGraph.head[i].next = NULL; // Initialize the next pointer to NULL
    }

    // Add edges to the graph
    // Get the number of edges from the user
    int edges;
    cout << "Enter the number of edges: " << endl;
    cin >> edges;

    try
    {
        for (int i = 0; i < edges; i++)
        {
            int src, dest;
            cout << "Enter edge " << i + 1 << " (source destination): ";
            cin >> src >> dest;
            addEdge(&undirectedGraph, src, dest);
            addEdge(&undirectedGraph, dest, src);
        }
    }
    catch (const runtime_error &e)
    {
        cout << "Error: " << e.what() << endl;
        delete[] undirectedGraph.head;
        return 1;
    }

    int startVertex, endVertex;
    cout << "Enter the starting vertex for path finding: " << endl;
    cin >> startVertex;
    cout << "Enter the ending vertex for path finding: " << endl;
    cin >> endVertex;

    vertex *pathArrayList = NULL;

    bool *visited = new bool[undirectedGraph.V];
    for (int i = 0; i < undirectedGraph.V; i++)
    {
        visited[i] = false;
    }

    bool found = Graph_findPath(&undirectedGraph, startVertex, endVertex, visited, pathArrayList);

    if (found)
    {
        cout << "Path found: ";
        vertex *temp = pathArrayList;
        while (temp != NULL)
        {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
    else
    {
        cout << "No path found." << endl;
    }

    return 0;
}