#include <iostream>

#include <queue>
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

void BreadthFirstSearch(graph *g, int startVertex)
{
    queue<int> bfsQueue;
    bool *visited = new bool[g->V];

    if (startVertex < 0 || startVertex >= g->V)
    {
        cout << "Invalid start vertex." << endl;
        return;
    }

    for (int i = 0; i < g->V; i++)
    {
        visited[i] = false;
    }

    bfsQueue.push(startVertex);
    visited[startVertex] = true;

    while (!bfsQueue.empty())
    {
        int currentVertex = bfsQueue.front();
        bfsQueue.pop();

        cout << currentVertex << " ";

        vertex *temp = g->head[currentVertex].next;
        while (temp != NULL)
        {
            int adjacentVertex = temp->data;
            if (!visited[adjacentVertex])
            {
                bfsQueue.push(adjacentVertex);
                visited[adjacentVertex] = true;
            }
            temp = temp->next;
        }
    }
    cout << endl;

    delete[] visited; // Clean up the dynamically allocated visited array
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

    BreadthFirstSearch(&undirectedGraph, 0); // Perform BFS starting from vertex 0

    return 0;
}