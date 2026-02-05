#include <iostream>
using namespace std;

// Node structure
struct Node {
    int data;
    Node* next;
};

Node* CircularLinkedList = NULL; // Global head pointer

void insertAtEnd(int value) {
    // Allocate new node
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode-> data = value;
    newNode-> next = NULL;
    if(CircularLinkedList == NULL){
        CircularLinkedList = newNode;
        newNode-> next = CircularLinkedList; // Point to itself
    } else {
        // Traverse to the end of the list
        Node* temp = CircularLinkedList; // Start from head
        while(temp-> next != CircularLinkedList){
            temp = temp-> next;
        }
        temp-> next = newNode;
        newNode-> next = CircularLinkedList; // Make it circular
    }
}

void insertAtStart(int value){
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode-> data = value;
    newNode-> next = NULL;
    if(CircularLinkedList == NULL){
        CircularLinkedList = newNode;
        newNode-> next = CircularLinkedList; // Point to itself
    } else {
        Node* temp = CircularLinkedList;
        while(temp-> next != CircularLinkedList){
            temp = temp-> next;
        }
        newNode-> next = CircularLinkedList;
        temp-> next = newNode;
        CircularLinkedList = newNode; // Update head to new node
    }
}

void insertAtPosition(int value, int position){
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode-> data = value;
    newNode-> next = NULL;
    if(position == 1){
        insertAtStart(value);
    } else {
        Node* temp = CircularLinkedList; // Start from head
        for(int i = 1; i < position - 1; i++){
            temp = temp-> next;
            if(temp == CircularLinkedList){
                cout << "Position out of bounds." << endl;
                free(newNode);
                return;
            }
        }
        newNode-> next = temp-> next;
        temp-> next = newNode;
    }
}

int searchValue(int data){
    if(CircularLinkedList == NULL){
        cout << "List is empty." << endl;
        return -1;
    }else{
        Node* temp = CircularLinkedList;
        int position = 1;
        
        while(temp-> next != CircularLinkedList){
            if(temp-> data == data){
                cout << "Value " << data << " found at position " << position << "." << endl;
                return position;
            }
            temp = temp-> next;
            position++;
        }
        // Check the last node
        if(temp-> data == data){
            cout << "Value " << data << " found at position " << position << "." << endl;
            return position;
        } else {
            cout << "Value " << data << " not found in the list." << endl;
            return -1;
        }

    }
}

int deleteAtStart(){
    if(CircularLinkedList == NULL){
        cout << "List is empty. Cannot delete." << endl;
        return -1;
    } else {
        Node* temp = CircularLinkedList;
        while(temp-> next != CircularLinkedList){
            temp = temp-> next;
        }
        int deletedValue = CircularLinkedList-> data;
        if(CircularLinkedList-> next == CircularLinkedList){
            // Only one node in the list
            free(CircularLinkedList);
            CircularLinkedList = NULL;
        } else {
            // Update last node's next pointer to skip the head node
            temp-> next = CircularLinkedList-> next;
            free(CircularLinkedList);
            CircularLinkedList = temp-> next;
        }
        return deletedValue;
    }
}

int deleteAtEnd(){
    Node* temp = CircularLinkedList;
    if(temp == NULL){
        cout << "List is empty. Cannot delete." << endl;
        return -1;
    }else{
        if(temp-> next == CircularLinkedList){
            // Only one node in the list
            int deletedValue = temp-> data;
            free(temp);
            CircularLinkedList = NULL;
            return deletedValue;
        } else {
            Node* prev = NULL;
            while(temp-> next != CircularLinkedList){
                prev = temp;
                temp = temp-> next;
            }
            int deletedValue = temp-> data;
            free(temp);
            prev-> next = CircularLinkedList; // Update second last node's next to head
            return deletedValue;
        }
    }
}

int deleteAtPosition(int position){
    Node* temp = CircularLinkedList;
    if(temp == NULL){
        cout << "List is empty. Cannot delete." << endl;
        return -1;
    }
    if(position == 1){
        return deleteAtStart();
    } else {
        Node* prev = NULL;
        for(int i = 1; i < position; i++){
            prev = temp;
            temp = temp-> next;
            if(temp == CircularLinkedList){
                cout << "Position out of bounds." << endl;
                return -1;
            }
        }
        int deletedValue = temp-> data;
        prev-> next = temp-> next; // Update previous node's next to skip the deleted node
        free(temp);
        return deletedValue;
    }
}

void displayList(){
    if(CircularLinkedList == NULL){
        cout << "List is empty." << endl;
    } else {
        Node* temp = CircularLinkedList;
        while(temp-> next != CircularLinkedList){
            cout << temp-> data << " -> ";
            temp = temp-> next;
        }   
        cout << temp-> data << " -> (back to head)" << endl;
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
    deleteAtPosition(3);
    displayList();
    insertAtEnd(40);
    displayList();

    return 0;
}