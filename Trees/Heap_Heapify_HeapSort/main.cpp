#include <iostream>

using namespace std;

// What is Heapify?
// Heapify is a process used to maintain the heap property in a binary tree.
// The heap property states that in a max heap, for any given node I, the value of I is greater than or equal to the values of its children, and in a min heap, the value of I is less than or equal to the values of its children.

// -> Each Node is greater than its children (Max Heap)
// -> Each Node is less than its children (Min Heap)

// MAX HEAP is used in making a priority queue, where the highest priority element is always at the front of the queue. 
   // It is also used in heap sort algorithm to sort elements in ascending order.

// MIN HEAP is used in Dijkstra's algorithm to find the shortest path in a graph, where the node with the smallest distance is always at the front of the queue. 
   // It is also used in heap sort algorithm to sort elements in descending order.


struct Node{
    int data;
    Node* left;
    Node* right;

    Node(int val){
        data = val;
        left = NULL;
        right = NULL;
    }
};


void Heapify(Node* BinaryTree[],int size, int rootIndex){
    int largest = rootIndex;
    int leftChild = 2 * rootIndex + 1;
    int rightChild = 2 * rootIndex + 2;

  

    if(leftChild < size && BinaryTree[leftChild]->data > BinaryTree[largest]->data){
        largest = leftChild;
    }
    if(rightChild < size && BinaryTree[rightChild]->data > BinaryTree[largest]->data){
        largest = rightChild;
    }

    if(largest != rootIndex){
        Node* temp = BinaryTree[rootIndex];
        BinaryTree[rootIndex] = BinaryTree[largest];
        BinaryTree[largest] = temp;

        Heapify(BinaryTree,size,largest);
    }
}

void BuildMaxHeap(Node* BinaryTree[], int size){
    int index = (size / 2) - 1; // Start from the last non-leaf node

    while (index >= 0){
        Heapify(BinaryTree,size,index);
        index--;
    }
}

void HeapSort(Node* BinaryTree[], int size){
    BuildMaxHeap(BinaryTree,size);

    int lastindex = size - 1;
    int rootIndex = 0;

    while (lastindex > rootIndex){
        Node* temp = BinaryTree[rootIndex];
        BinaryTree[rootIndex] = BinaryTree[lastindex];
        BinaryTree[lastindex] = temp;

        lastindex--;

        Heapify(BinaryTree,lastindex,rootIndex);
    }
}

void printInOrder(Node* BinaryTree[], int rootIndex, int size){
    if(rootIndex >= size || BinaryTree[rootIndex] == NULL){
        return;
    }
    int leftIndex = 2 * rootIndex + 1;
    int rightIndex = 2 * rootIndex + 2;
    printInOrder(BinaryTree, leftIndex, size);
    cout << BinaryTree[rootIndex]->data << " ";
    printInOrder(BinaryTree, rightIndex, size);
}

void printPreOrder(Node* BinaryTree[], int rootIndex, int size){
    if(rootIndex >= size || BinaryTree[rootIndex] == NULL){
        return;
    }
    cout << BinaryTree[rootIndex]->data << " ";
    int leftIndex = 2 * rootIndex + 1;
    int rightIndex = 2 * rootIndex + 2;
    printPreOrder(BinaryTree, leftIndex, size);
    printPreOrder(BinaryTree, rightIndex, size);
}   


void printPostOrder(Node* BinaryTree[], int rootIndex, int size){
    if(rootIndex >= size || BinaryTree[rootIndex] == NULL){
        return;
    }
    int leftIndex = 2 * rootIndex + 1;
    int rightIndex = 2 * rootIndex + 2;
    printPostOrder(BinaryTree, leftIndex, size);
    printPostOrder(BinaryTree, rightIndex, size);
    cout << BinaryTree[rootIndex]->data << " ";
}


int main(){

    // Create an array of pointers to Node, representing the binary tree
    Node* BinaryTree[10];
    // Initialize the binary tree with some values
    BinaryTree[0] = new Node(3);
    BinaryTree[1] = new Node(9);
    BinaryTree[2] = new Node(2);
    BinaryTree[3] = new Node(1);
    BinaryTree[4] = new Node(4);
    BinaryTree[5] = new Node(5);
    BinaryTree[6] = new Node(8);
    BinaryTree[7] = new Node(7);
    BinaryTree[8] = new Node(6);
    BinaryTree[9] = new Node(10);

    int size = sizeof(BinaryTree) / sizeof(BinaryTree[0]);

    cout << "Original Binary Tree: ";
    for(int i = 0; i < size; i++){
        cout << BinaryTree[i]->data << " ";
    }
    cout << endl;

    HeapSort(BinaryTree,size);

    cout << "Sorted Binary Tree: ";
    for(int i = 0; i < size; i++){
        cout << BinaryTree[i]->data << " ";
    }
    cout << endl;

    cout << "In-order traversal: ";
    printInOrder(BinaryTree, 0, size);
    cout << endl;

    cout << "Pre-order traversal: ";
    printPreOrder(BinaryTree, 0, size);
    cout << endl;

    cout << "Post-order traversal: ";
    printPostOrder(BinaryTree, 0, size);
    cout << endl;

    return 0;
}