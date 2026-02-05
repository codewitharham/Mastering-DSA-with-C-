#include <iostream>
using namespace std;

// Node structure
struct Node {
    int data;
    Node* next;
};

Node* SinglyLinkedList = NULL; // Global head pointer

void insertAtEnd(int value) {
    // Allocate new node
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode-> data = value;
    newNode-> next = NULL;

    if(SinglyLinkedList == NULL){
        SinglyLinkedList = newNode;
    } else {
        // Traverse to the end of the list
        Node* temp = SinglyLinkedList; // Start from head
        while(temp-> next != NULL){
            temp = temp-> next;
        }
        temp-> next = newNode;
    }

}


void insertAtStart(int value){
    // Allocate new node
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode-> data = value;
    
    if(SinglyLinkedList == NULL){
        // If the list is empty, new node becomes the head
        SinglyLinkedList = newNode;
    } else {
        newNode-> next = SinglyLinkedList;
        SinglyLinkedList = newNode;
    }
    
}

void insertAtPosition(int value, int position){
    // Allocate new node
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode-> data = value;
    
    if(position == 1){
        // Insert at the start
        newNode-> next = SinglyLinkedList;
        SinglyLinkedList = newNode;
    } else {
        Node* temp = SinglyLinkedList; // Start from head
        for(int i = 1; i < position - 1 && temp != NULL; i++){
            temp = temp-> next;
        }
        if(temp == NULL){
            cout << "Position out of bounds." << endl;
            free(newNode); // Free allocated memory
            return;
        }
        newNode-> next = temp-> next;
        temp-> next = newNode;
    }
    
}

int searchValue(int data){
    Node* temp = SinglyLinkedList;
    int pos = 1;

    while(temp != NULL){
        if(temp->data == data){
            cout << "Element found at position: " << pos << endl;
            return pos;
        }
        temp = temp->next;
        pos++;
    }
    return -1;
}

int deleteAtStart(){
    if(SinglyLinkedList == NULL){
        cout << "List is empty. Cannot delete." << endl;
        return -1;
    }else{
        Node* temp = SinglyLinkedList;
        int deletedValue = temp-> data;
        SinglyLinkedList = SinglyLinkedList-> next;
        free(temp); // Free memory
        return deletedValue;
    }
}

int deleteAtEnd(){
    if(SinglyLinkedList == NULL){
        cout << "List is empty. Cannot delete." << endl;
        return -1;
    }else{
        if(SinglyLinkedList-> next == NULL){
            // Only one node in the list
            int deletedValue = SinglyLinkedList-> data;
            free(SinglyLinkedList);
            SinglyLinkedList = NULL;
            return deletedValue;
        } else {
            Node* temp = SinglyLinkedList; // Start from head
            while(temp-> next-> next != NULL){
                temp = temp-> next;
            }
            int deletedValue = temp-> next-> data;
            free(temp-> next); // Free memory of last node
            temp-> next = NULL; // Update second last node's next to NULL
            return deletedValue;
        }
    }
}

int deleteAtPosition(int position){
    if(SinglyLinkedList == NULL){
        cout << "List is empty. Cannot delete." << endl;
        return -1;
    }
    if(position == 1){
        return deleteAtStart();
    } else {
        Node* temp = SinglyLinkedList; // Start from head
        for(int i = 1; i < position - 1 && temp != NULL; i++){
            temp = temp-> next;
        }
        if(temp == NULL || temp-> next == NULL){
            cout << "Position out of bounds." << endl;
            return -1;
        }
        Node* nodeToDelete = temp-> next;
        int deletedValue = nodeToDelete-> data;
        temp-> next = nodeToDelete-> next;
        free(nodeToDelete); // Free memory
        return deletedValue;
    }
}

void displayList(){
    Node* temp = SinglyLinkedList; // Start from head
    if (temp == NULL){
        cout << "List is empty." << endl;
    }else{
        while(temp != NULL){
            cout << temp-> data << " -> ";
            temp = temp-> next;
        }
        cout << "NULL" << endl;
        
    }
    
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