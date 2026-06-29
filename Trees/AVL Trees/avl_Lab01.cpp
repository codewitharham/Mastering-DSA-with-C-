#include <iostream>
#include <stdio.h>
using namespace std;


struct Node{

    int data;
    Node* left;
    Node* right;
    int nodeHeight;

    Node(int val): data(val), left(nullptr), right(nullptr), nodeHeight(1) {}
    // new Node height will always be 1.
};

// Ex : A6 Lab 01:

int getHeight(Node* root){
    if (root == nullptr) return 0;
    return root->nodeHeight;
}

int getBalanceFactor(Node* root){

    if(root == nullptr){
        return 0;
    }

    int result =(  (getHeight(root->left)) - (getHeight(root->right)) );
    return result;
}


// Rotation Cases:
// 1. if PARENT (BF) > 1 and CHILD (BF) >= 0 THEN rotateRight(PARENT) - LEFT LEFT CASE
// 2. if PARENT (BF) > 1 and CHILD (BF) < 0 THEN rotateLeft(CHILD) followed rotateRight(PARENT) - LEFT RIGHT CASE
// 3. if PARENT (BF) < 1 and CHILD (BF) <= 0 THEN rotateLeft(PARENT) - RIGHT RIGHT CASE
// 4. if PARENT (BF) < 1 and CHILD (BF) > 0 THEN rotateRight(CHILD) followed rotateLeft(PARENT) - RIGHT LEFT CASE

int updateNodeHeight(Node* root){
    if(root == nullptr){
        return 0;
    }

    int LH = getHeight(root->left);
    int RH = getHeight(root->right);

    if (LH > RH) {
        return 1 + LH;
    } else {
        return 1 + RH;
    }
}


Node* rotateRight(Node* root){

    Node* child = root->left;
    Node* child_subtree_T2 = child->right;
    
    child->right = root;
    root->left = child_subtree_T2;

    root->nodeHeight = updateNodeHeight(root);
    child->nodeHeight = updateNodeHeight(child);

    return child;

}

Node* rotateLeft(Node* root){

    Node* child = root->right;
    Node* child_subtree_T2 = child->left;
    
    child->left = root;
    root->right = child_subtree_T2;

    root->nodeHeight = updateNodeHeight(root);
    child->nodeHeight = updateNodeHeight(child);

    return child;

}


Node* rebalanceNode(Node* node){
    
    node->nodeHeight = updateNodeHeight(node);

    int ParentBalanceFactor = getBalanceFactor(node);

    // Rebalace at Left of Tree
    if (ParentBalanceFactor > 1)
    {
        int ChildBalanceFactor = getBalanceFactor(node->left);
        // LEFT-LEFT CASE
        if (ChildBalanceFactor >= 0)
        {
            return rotateRight(node);
        }else{
            // LEFT-RIGHT CASE
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
    }
    
    // Rebalace at RIGHT of Tree
    if (ParentBalanceFactor < -1)
    {
        int ChildBalanceFactor = getBalanceFactor(node->right);
        // RIGHT-RIGHT CASE
        if (ChildBalanceFactor <= 0)
        {
            return rotateLeft(node);
        }else{
            // RIGHT-LEFT CASE
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
    }

    return node;

}




int main(){

    return 0;
}
