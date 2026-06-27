#include <iostream>

using namespace std;

// Bug B2 — The Infinite Loop


struct Node {
    int data;
    Node* left;
    Node* right;
};

void inorder_bug(Node* root) {
    if (root == nullptr) return;
    inorder_bug(root->left);
    cout << root->data << " ";
    inorder_bug(root->left);  
}

void inorder_bugFixed(Node* root) {
    if (root == nullptr) return;
    inorder_bugFixed(root->left);
    cout << root->data << " ";
    inorder_bugFixed(root->right);   // ← fixed
}


