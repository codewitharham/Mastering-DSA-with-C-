#include <iostream>
using namespace std;

struct QNode{
    int data;
    QNode* next; // Pointer to the next node in the queue. It is used to link the nodes together, allowing us to traverse the queue from the front to the rear.
};

struct Queue{
    QNode* front; // Pointer to the front node of the queue. It is used to keep track of the first element in the queue, which is the next element to be dequeued.
    QNode* rear; // Pointer to the rear node of the queue. It is used to keep track of the last element in the queue, which is the most recently enqueued element.
};

QNode* createNode(int data){
    QNode* newNode = new QNode; // Dynamically allocate memory for a new node of type QNode and assign its address to the pointer variable 'newNode'.
    newNode->data = data; 
    newNode->next = NULL; 
    return newNode; 
}

void Enqueue(Queue* q, int data){
    QNode* newNode = createNode(data); // Create a new node with the given data
    if (q->rear == NULL) { // If the queue is empty, set both front and rear to the new node
        q->front = newNode;
        q->rear = newNode;
        return;
    }
    q->rear->next = newNode; // Link the new node to the end of the queue
    q->rear = newNode; // Update the rear pointer to point to the new node
}

int Dequeue(Queue* q){
    if (q->front == NULL) { // If the queue is empty, there is nothing to dequeue
        cout << "Queue is empty!" << endl;
        return -1; 
    }
    QNode* temp = q->front; // Store the front node in a temporary variable
    q->front = q->front->next; // Move the front pointer to the next node in the queue
    if (q->front == NULL) { // If the queue becomes empty after dequeuing, set rear to NULL as well
        q->rear = NULL;
    }
    delete temp; // Free the memory of the dequeued node
    return temp->data; // Return the data of the dequeued node
}

void display(Queue* q){
    QNode* temp = q->front; // Start from the front of the queue
    while (temp != NULL) { // Traverse the queue until the end is reached
        cout << temp->data << " "; // Print the data of the current node
        temp = temp->next; // Move to the next node in the queue
    }
    cout << endl; 
}


int main(){
    Queue q;
    q.front = NULL; 
    q.rear = NULL; 

    Enqueue(&q, 10); 
    Enqueue(&q, 20); 
    Enqueue(&q, 30); 

    cout << "Queue after enqueuing 10, 20, and 30: ";
    display(&q); 

    Dequeue(&q); 
    cout << "Queue after dequeuing an element: ";
    display(&q); 

    return 0;
}