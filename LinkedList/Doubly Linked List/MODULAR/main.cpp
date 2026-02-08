#include <iostream>
using namespace std;

// Node structure
struct Node {
    int data;
    Node* prev;
    Node* next;
};

Node* DoublyLinkedList = NULL; // Global head pointer

void insertAtEnd(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode-> data = value;
    newNode-> next = NULL;
    newNode-> prev = NULL;
    if(DoublyLinkedList == NULL){
        DoublyLinkedList = newNode;
    }else{
        Node* temp = DoublyLinkedList;
        while(temp-> next != NULL){
            temp = temp-> next;
        }
        temp-> next = newNode;
        newNode-> prev = temp; // Set previous pointer
    }
}

void insertAtStart(int value){
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode-> data = value;
    newNode-> next = NULL;
    newNode-> prev = NULL;
    if(DoublyLinkedList == NULL){
        DoublyLinkedList = newNode;
    } else {
        newNode-> next = DoublyLinkedList; // Point new node to current head
        DoublyLinkedList-> prev = newNode; // Set current head's previous to new node
        DoublyLinkedList = newNode; // Update head to new node
    }
}

void insertAtPosition(int value, int position){
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode-> data = value; 
    newNode-> next = NULL;
    newNode-> prev = NULL;
    if(position == 1){
        insertAtStart(value);
    } else {
        Node* temp = DoublyLinkedList; // Start from head
        for(int i = 1; i < position - 1; i++){
            temp = temp-> next;
            if(temp == NULL){
                cout << "Position out of bounds." << endl;
                return;
            }
        }
        newNode-> next = temp-> next; // Point new node to next node
        newNode-> prev = temp; // Set new node's previous to current node
        if(temp-> next != NULL){
            temp-> next-> prev = newNode; // Update next node's previous to new node
        }
        temp-> next = newNode; // Update current node's next to new node
    }
}

int searchValue(int data){
    Node* temp = DoublyLinkedList;
    int position = 1;
    while(temp != NULL){
        if(temp-> data == data){
            cout << "Value " << data << " found at position " << position << "." << endl;
            return position;
        }
        temp = temp-> next;
        position++;
    }
    cout << "Value " << data << " not found in the list." << endl;
    return -1;
}

int deleteAtStart(){
    if(DoublyLinkedList == NULL){
        cout << "List is empty." << endl;
        return -1;
    }
    Node* temp = DoublyLinkedList;
    DoublyLinkedList = DoublyLinkedList-> next;
    if(DoublyLinkedList != NULL){
        DoublyLinkedList-> prev = NULL;
    }
    int DeletedData = temp -> data; 
    free(temp);
    return DeletedData;
}

int deleteAtEnd(){
    Node* temp = DoublyLinkedList;
    if(temp == NULL){
        cout << "List is empty." << endl;
        return -1;
    }else{
        if(temp-> next == NULL){
            // Only one node in the list
            int deletedValue = temp-> data;
            free(temp);
            DoublyLinkedList = NULL;
            return deletedValue;
        } else {
            while(temp-> next != NULL){
                temp = temp-> next;
            }
            int deletedValue = temp-> data;
            temp-> prev-> next = NULL; // Update second last node's next to NULL
            free(temp);
            return deletedValue;
        }
    }
}

int deleteAtPosition(int position){
    Node* temp = DoublyLinkedList;
    if(temp == NULL){
        cout << "List is empty." << endl;
        return -1;
    }else{
        if(position == 1){
            return deleteAtStart();
        } else {
            for(int i = 1; i < position; i++){
                temp = temp-> next;
                if(temp == NULL){
                    cout << "Position out of bounds." << endl;
                    return -1;
                }
            }
            int deletedValue = temp-> data;
            if(temp-> next != NULL){
                temp-> next-> prev = temp-> prev; // Update next node's previous
            }
            if(temp-> prev != NULL){
                temp-> prev-> next = temp-> next; // Update previous node's next
            }
            free(temp);
            return deletedValue;
        }
    }
}

void displayListForward(){
    Node* temp = DoublyLinkedList;
    while(temp != NULL){
        cout << temp-> data << " ";
        temp = temp-> next;
    }
    cout << endl;
}

void displayListBackward(){
    Node* temp = DoublyLinkedList;
    if(temp == NULL){
        cout << "List is empty." << endl;
        return;
    }
    // Move to the end of the list
    while(temp-> next != NULL){
        temp = temp-> next;
    }
    // Traverse backward
    while(temp != NULL){
        cout << temp-> data << " ";
        temp = temp-> prev;
    }
    cout << endl;
}

int main(){
    // Main function to test the linked list operations
    insertAtEnd(10);
    insertAtEnd(20);
    insertAtEnd(30);
    displayListForward();
    insertAtStart(5);
    displayListForward();
    displayListBackward();
    insertAtPosition(15, 3); // Insert 15 at position 3
    searchValue(20); // Search for value 20
    displayListForward();
    deleteAtStart();
    displayListForward();
    deleteAtEnd();
    displayListForward();
    deleteAtPosition(2);
    displayListForward();

    return 0;
}