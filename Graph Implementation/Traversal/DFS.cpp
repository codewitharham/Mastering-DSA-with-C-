#include <iostream>
#include <stack>

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
    newVertex->next = NULL;
    return newVertex;
}

void addEdge(graph *g, int src, int dest)
{

    if (src < 0 || src >= g->V || dest < 0 || dest >= g->V)
    {
        cout << "the src and dest vertices must be between 0 and " << g->V - 1 << endl;
        throw runtime_error("Source or destination vertex is out of bounds.");
    }

    vertex *newVertex = createVertex(dest);
    newVertex->next = g->head[src].next;
    g->head[src].next = newVertex;
}

void DepthFirstSearch_Recursion(graph *g, int startVertex, bool *visited)
{
    if (startVertex < 0 || startVertex >= g->V)
    {
        cout << "Invalid start vertex." << endl;
        return;
    }

    visited[startVertex] = true;
    cout << startVertex << " ";

    vertex *temp = g->head[startVertex].next;
    while (temp != NULL)
    {
        int adjacentVertex = temp->data;
        if (!visited[adjacentVertex])
        {
            DepthFirstSearch_Recursion(g, adjacentVertex, visited);
        }
        temp = temp->next;
    }
}

void DepthFirstSearch_Stack(graph *g, int startVertex)
{
    stack<int> DFS_stack;

    bool *visited = new bool[g->V];

    for (int i = 0; i < g->V; i++)
    {
        visited[i]= false;
    }
    
    if (startVertex < 0 || startVertex >= g->V)
    {
        cout << "Invalid start vertex." << endl;
        return;
    }

    DFS_stack.push(startVertex);
    visited[startVertex] = true;

    while (!DFS_stack.empty())
    {
        int currentVertex = DFS_stack.top();
        DFS_stack.pop();

        cout << currentVertex << " ";

        vertex *temp = g->head[currentVertex].next;
        
        while (temp != NULL)
        {
            int adjacentVertex = temp->data;

            if (!visited[adjacentVertex])
            {
                DFS_stack.push(temp->data);
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
            addEdge(&undirectedGraph, dest, src); // For undirected graph
        }
    }
    catch (const runtime_error &e)
    {
        cerr << e.what() << endl;
        return 1; // Exit with an error code
    }

    int startVertex;
    cout << "Enter the starting vertex for DFS: " << endl;
    cin >> startVertex;
    cout << "DFS Traversal (Recursion): ";
    bool *visited = new bool[undirectedGraph.V];

    for (int i = 0; i < undirectedGraph.V; i++)
    {
        visited[i] = false;
    }

    DepthFirstSearch_Recursion(&undirectedGraph, startVertex, visited);

    cout << endl;
    delete[] visited;
    

    cout << "DFS Traversal (Stack): ";
    DepthFirstSearch_Stack(&undirectedGraph, startVertex);

    delete[] undirectedGraph.head; // Clean up the dynamically allocated head array



    return 0;
};