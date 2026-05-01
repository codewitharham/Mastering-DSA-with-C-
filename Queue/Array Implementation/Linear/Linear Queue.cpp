#include <iostream>

using namespace std;


template<typename T>
struct LinearQueue{
    int front; 
    int rear; 
    int capacity; 
    T* arr; // Pointer to an array that holds the elements of the queue. It is used to store the actual data of the queue and allows for dynamic memory allocation based on the specified capacity.
};

template<typename T>
LinearQueue<T>* createQueue(int capacity){
    LinearQueue<T>* q = new LinearQueue<T>; // Dynamically allocate memory for a new queue of type LinearQueue and assign its address to the pointer variable 'q'.
    q->capacity = capacity; 
    q->front = 0; 
    q->rear = -1; 
    q->arr = new T[capacity]; // Dynamically allocate memory for an array of type T with the specified capacity and assign its address to the 'arr' pointer of the queue.
    return q; 
}

template<typename T>
void Enqueue(LinearQueue<T>* q, T data){
    if (q->rear == q->capacity - 1) { 
        return;
    }
    q->rear = q->rear + 1; 
    q->arr[q->rear] = data; 
}

template<typename T>
T Dequeue(LinearQueue<T>* q){
    if (q->front > q->rear) {
        
        q->front = 0;
        q->rear = -1;
       
        throw runtime_error("Queue is empty!, overflow condition");


    }
    T data = q->arr[q->front];
    q->front = q->front + 1;
    return data;
}


template<typename T>
void display(LinearQueue<T>* q){
    for (int i = q->front; i <= q->rear; i++) {
        cout << q->arr[i] << " "; 
    }
    cout << endl;
}


int main(){

    LinearQueue<int>* q = createQueue<int>(5); // Create a queue of integers with a capacity of 5
    Enqueue(q, 10); 
    Enqueue(q, 20); 
    Enqueue(q, 30); 

    display(q); 
    Dequeue(q); 
    display(q); 

    Dequeue(q); 
    Dequeue(q); 
    display(q); 

    Enqueue(q, 40); 
    display(q); 
    Enqueue(q, 50); 
    display(q); 

    Dequeue(q); 
    Dequeue(q); 
    display(q); 
    Dequeue(q); 
    
    
    


    return 0;
}