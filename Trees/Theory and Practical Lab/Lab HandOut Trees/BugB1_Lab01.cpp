#include <iostream>
#include <stdio.h>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int v) : data(v), left(nullptr), right(nullptr) {}
};

// Bug: tree never grows beyond root
void insert_bug(Node* root, int val) {
    if (root == nullptr) {
        root = new Node(val);
        return;
    }
    if (val < root->data) insert_bug(root->left, val);
    else                  insert_bug(root->right, val);
}

Node* insert_modern(Node* root, int val) {
    if (root == nullptr) {
        return new Node(val);
    }
    if (val < root->data) root->left = insert_modern(root->left, val);
    else                  root->right = insert_modern(root->right, val);
    return root;
}

void insert_bug_fixed(Node*& root, int val) {
    if (root == nullptr) {
        root = new Node(val);
        return;
    }
    if (val < root->data) insert_bug_fixed(root->left, val);
    else                  insert_bug_fixed(root->right, val);
}

int main() {
    Node* root1 = nullptr;
    Node* root2= nullptr;
    Node* root3 = nullptr;

    insert_bug(root1, 10);
    insert_bug(root1, 5);

    if (root1 == nullptr) cout << "Tree 1 is empty!\n";
    else cout << "Tree 1 is not empty!\n";

    root2 = insert_modern(root2, 10);
    root2 = insert_modern(root2, 5);

    if (root2 == nullptr) cout << "Tree 2 is empty!\n";
    else cout << "Tree 2 is not empty!\n";

    insert_bug_fixed(root3, 20);
    insert_bug_fixed(root3, 15);

    if (root3 != nullptr) cout << "Tree 3 is not empty!\n";
    else cout << "Tree 3 is empty!\n";
}