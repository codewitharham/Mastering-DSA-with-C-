#include <iostream>
using namespace std;

struct node
{
    int data;
    node* next;
};

node *hashTable[10] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};

void insert(int value)
{
    int hashIndex = value % 10;

    node* newNode = new node;
    newNode->data = value;
    newNode->next = NULL;

    if (hashTable[hashIndex] == NULL)
    {
        hashTable[hashIndex] = newNode;
    }
    else
    {
        node* temp = hashTable[hashIndex];
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

void remove(int value)
{
    int hashIndex = value % 10;

    node* temp = hashTable[hashIndex];
    node* prev = NULL;

    while (temp != NULL)
    {
        if (temp->data == value)
        {
            if (prev == NULL)
            {
                hashTable[hashIndex] = temp->next;
            }
            else
            {
                prev->next = temp->next;
            }
            delete temp;
            return;
        }
        prev = temp;
        temp = temp->next;
    }
}

void display()
{
    for (int i = 0; i < 10; i++)
    {
        node* temp = hashTable[i];
        cout << "Index " << i << ": ";
        while (temp != NULL)
        {
            cout << temp->data << " -> ";
            temp = temp->next;
        }
        cout << "NULL" << endl;
    }
}

// Example usage
int main()
{
    insert(10);
    insert(20);
    insert(30);
    insert(40);
    insert(56);
    insert(67);
    insert(70);
    insert(88);
    insert(90);
    insert(100);
    insert(66);
    insert(77);



    display();
     remove(40);
     display();

    return 0;
}








