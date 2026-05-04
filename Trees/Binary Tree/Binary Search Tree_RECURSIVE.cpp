#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
};

struct BinarySearchTree {
    Node* root;
};

void createNode(Node*& node, int value) {
    node = new Node;
    node->data = value;
    node->left = NULL;
    node->right = NULL;
}

void insertNode(Node*& node, int value) {
    if (node == NULL) {
        createNode(node, value);
        return;
    } else if (value < node->data) {
        insertNode(node->left, value);
    } else if (value > node->data) {
        insertNode(node->right, value);
    }
}

void inorderTraversal(Node* root) {
    if (root == NULL) return;
    inorderTraversal(root->left);
    cout << root->data << " ";
    inorderTraversal(root->right);
}

void preorderTraversal(Node* root) {
    if (root == NULL) return;
    cout << root->data << " ";
    preorderTraversal(root->left);
    preorderTraversal(root->right);
}

void postorderTraversal(Node* root) {
    if (root == NULL) return;
    postorderTraversal(root->left);
    postorderTraversal(root->right);
    cout << root->data << " ";
}

Node* findMinimum(Node* root){
    Node* currentNode = root->right;
    while( currentNode != NULL && currentNode->left != NULL){
        currentNode = currentNode->left;
    }
    return currentNode;
}

Node* deleteNode(Node*& root, int value) {
    
    if ( root == NULL ){
        return root;
    }

    if( value < root->data){
        root->left = deleteNode(root->left, value);
        return root;
    }

    if( value > root->data){
        root->right = deleteNode(root->right, value);
        return root;
    }
    
    if(value == root->data){

        // Case 1: No child
        if(root->left == NULL && root->right == NULL){
            delete root;
            return NULL;
        }

        // Case 2: One child
        if(root->left == NULL){
            Node* temp = root->right;
            delete root;
            return temp;
        }

        if(root->right == NULL){
            Node* temp = root->left;
            delete root;
            return temp;
        }

        //case 3: Two children
        Node* temp = findMinimum(root);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
        return root;

    }

}

int main() {
    BinarySearchTree bst;
    bst.root = NULL;

    // int n, value;
    // cout << "Enter the number of nodes: ";
    // cin >> n;
    // for (int i = 0; i < n; i++) {
    //     cout << "Enter value for node " << i + 1 << ": ";
    //     cin >> value;
    //     insertNode(bst.root, value);
    // }

        insertNode(bst.root, 10);
        insertNode(bst.root, 8);
        insertNode(bst.root, 30);
        insertNode(bst.root, 6);
        insertNode(bst.root, 9);
        insertNode(bst.root, 25);
        insertNode(bst.root, 40);
        insertNode(bst.root, 20);
        insertNode(bst.root, 50);

    cout << "Inorder Traversal: ";
    inorderTraversal(bst.root);
    cout << endl;

    cout << "Preorder Traversal: ";
    preorderTraversal(bst.root);
    cout << endl;

    cout << "Postorder Traversal: ";
    postorderTraversal(bst.root);
    cout << endl;

    bst.root = deleteNode(bst.root, 8);

    cout << "Inorder Traversal: ";
    inorderTraversal(bst.root);
    cout << endl;


    return 0;
}