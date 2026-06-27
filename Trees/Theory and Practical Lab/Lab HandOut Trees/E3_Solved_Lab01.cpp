// YOUR TEST PROGRAM:
#include <iostream>
#include <stdio.h>
using namespace std;

template<class T>
struct Node {
    T data;
    Node<T>* Left;
    Node<T>* Right;

    
    Node(T val): data(val), Left(nullptr), Right(nullptr) {}
};

template<class T>
Node<T>* createNode(T val){
    Node<T>* newNode = new Node<T>(val);
    return newNode;
}

template<class T>
Node<T>* insert(Node<T>* root, T val) {

    if (root == nullptr){
        return createNode(val);
    }else{
        if (val < root->data)
        {
            root->Left = insert(root->Left, val);
        }

        if(val > root->data)
        {
            root->Right = insert(root->Right, val);
        }
    }
    return root;
}

template<class T>
bool searchTree(Node<T>* root, T searchVal){

    if (root == nullptr)
    {
        return false;
    }

    if(root->data == searchVal){
       return true;
    }else{
        if (searchVal > root->data)
        {
            
            return searchTree(root->Right, searchVal);
        }
        if (searchVal < root->data)
        {
            
            return searchTree(root->Left, searchVal);
        }
        
        return false;
    }
}

template<class T>
void preOrderTraversal(Node<T>* root){
    if(root == nullptr){
        return;
    }
    cout << root->data << endl;
    preOrderTraversal(root->Left);
    preOrderTraversal(root->Right);
}

template<class T>
void inOrderTraversal(Node<T>* root){
    if(root == nullptr){
        return;
    }
    
    inOrderTraversal(root->Left);
    cout << root->data << endl;
    inOrderTraversal(root->Right);
}

template<class T>
void postOrderTraversal(Node<T>* root){
    if(root == nullptr){
        return;
    }
    postOrderTraversal(root->Left);
    postOrderTraversal(root->Right);
    cout << root->data << endl;
}

template<class T>
Node<T>* findInOrderSuccessor(Node<T>* root){

    Node<T>* currentNode = root->Right;

    while (currentNode != nullptr && currentNode->Left != nullptr)
    {
        currentNode = currentNode->Left;
    }
    
    return currentNode;

}

template<class T>
bool deleteFromTree(Node<T>*& root, T val){
    if(root == nullptr){
        return false;
    }

    if(val < root->data){
        
        return deleteFromTree(root->Left, val);
    }

    if(val > root->data){
        return deleteFromTree(root->Right, val);
    }

    if(val == root->data){

        // CASE 1: Delete Leaf Node

        if( root->Left == nullptr && root->Right == nullptr){
            delete root;
            root = nullptr;
            return true;
        }else{

            // CASE 2: DELETE One Child
            if(root->Left == nullptr && root->Right != nullptr){
                Node<T>* tempNode = root->Right;
                delete root;
                root = tempNode;
                return true;
            }

            if(root->Left != nullptr && root->Right == nullptr){
                Node<T>* tempNode = root->Left;
                delete root;
                root = tempNode;
                return true;
            }

            // CASE 3: DELETE Two Child
            Node<T>* tempNode = findInOrderSuccessor(root);
            root->data = tempNode->data;
            return deleteFromTree(root->Right, tempNode->data);

        }

    }
    return false;
}




int main() {
    // Test 1: Build tree
    
    Node<int>* root = nullptr;

    root = insert(root, 10);
    root = insert(root, 8);
    root = insert(root, 30);
    root = insert(root, 6);
    root = insert(root, 9);
    root = insert(root, 7);
    root = insert(root, 25);
    root = insert(root, 40);
    root = insert(root, 50);

    // Test 2: Inorder verification
    inOrderTraversal(root);
    
    // Test 3: Search tests
    cout << "Search for Value: 30" << endl;
    cout << "value was found: " << searchTree(root, 30) << endl; 

    // Test 4: Delete leaf
    deleteFromTree(root, 50);
    inOrderTraversal(root);
    // Test 5: Delete one-child
    deleteFromTree(root, 9);
    inOrderTraversal(root);
    // Test 6: Delete two-child
    deleteFromTree(root, 30);
    inOrderTraversal(root);    
    return 0;
}