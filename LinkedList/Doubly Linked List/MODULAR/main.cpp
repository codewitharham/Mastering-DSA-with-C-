#include <iostream>
using namespace std;

// Node structure
struct Node {
    int data;
    Node* next;
};

Node* CircularLinkedList = NULL; // Global head pointer

void insertAtEnd(int value) {
    
}

void insertAtStart(int value){
    
}

void insertAtPosition(int value, int position){
    
}

int searchValue(int data){
    
}

int deleteAtStart(){
    
}

int deleteAtEnd(){
    
}

int deleteAtPosition(int position){
    
}

void displayList(){
        
}

int main(){
    // Main function to test the linked list operations
    insertAtEnd(10);
    insertAtEnd(20);
    insertAtEnd(30);
    insertAtStart(5);
    insertAtPosition(15, 3); // Insert 15 at position 3
    searchValue(20); // Search for value 20
    displayList();
    deleteAtStart();
    displayList();
    deleteAtEnd();
    displayList();
    deleteAtPosition(2);
    displayList();

    return 0;
}