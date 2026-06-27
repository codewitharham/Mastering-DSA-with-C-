#include <iostream>
using namespace std;



struct Node {
    int data;
    Node* Left;
    Node* Right;

    Node(int val): data(val), Left(nullptr), Right(nullptr) {}
};

// Supposed to find smallest value in BST
int findMin(Node* root) {
    if (root == nullptr) return -1;
    if (root->Left == nullptr) return root->data;
    return findMin(root->Right);   // ← bug
}

int findMin_Fixed(Node* root) {
    if (root == nullptr){
        return -1;
    }

    if (root->Left == nullptr){
        return root->data;
    }

    return findMin_Fixed(root->Left);
    
}