#include <iostream>
using namespace std;


struct Node {
    int data;
    Node* left;
    Node* right;
};

int height(Node* root) {
    return 1 + max(height(root->left), height(root->right));  // ← bug
}

int Calculate_height_Fixed(Node* root) {
   
    // Base Case 1: Empty tree/node
    if(root == nullptr){
        return 0;
    }

    // Base Case 2: Leaf node (no children)
    if(root->left == nullptr && root->right == nullptr){
        return 1;
    }

    // NEW CASE: If BOTH children exist, we must calculate both paths and take the larger one
    if (root->left != nullptr && root->right != nullptr) {
        int Lh = Calculate_height_Fixed(root->left) + 1;
        int Rh = Calculate_height_Fixed(root->right) + 1;
        return max(Lh, Rh);
    }

    // If only the left child exists (right is definitely nullptr)
    if (root->left != nullptr) {
        int Lh = Calculate_height_Fixed(root->left) + 1;
        return Lh;
    }

    // If only the right child exists (left is definitely nullptr)
    if (root->right != nullptr) {
        int Rh = Calculate_height_Fixed(root->right) + 1;
        return Rh;
    }
}