#include <iostream>
using namespace std;


struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

Node* deleteLeaf(Node* root, int val) {
    if (root == nullptr) return nullptr;
    if (val < root->data) {
        root->left = deleteLeaf(root->left, val);
        return root;
    }
    if (val > root->data) {
        root->right = deleteLeaf(root->right, val);
        return root;
    }
    // val == root->data, and it's a leaf
    if (root->left == nullptr && root->right == nullptr) {
        return nullptr;   // ← bug is here
    }
    return root;
}

Node* deleteLeaf_Fixed(Node* root, int val) {
    if (root == nullptr) return nullptr;
    if (val < root->data) {
        root->left = deleteLeaf_Fixed(root->left, val);
        return root;
    }
    if (val > root->data) {
        root->right = deleteLeaf_Fixed(root->right, val);
        return root;
    }
    // val == root->data, and it's a leaf
    if (root->left == nullptr && root->right == nullptr) {
        
        delete root;  // Free the memory of the leaf node
        return nullptr;   // Return nullptr to indicate the leaf has been deleted
    }
    return root;
}