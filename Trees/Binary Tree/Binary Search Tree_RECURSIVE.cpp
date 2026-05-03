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

void deleteNode(Node*& node, int value) {
    if (node == NULL){
        return;
    }else{

        if(value == node->left->data){
            Node *toDelete = node->left;
            node->left = NULL;
            delete[] toDelete;
        
        }else{
            
            if(value == node->right->data){
                Node *toDelete = node->right;
                node->right = NULL;
                delete[] toDelete;
            }        

        }
    }

    if (value < node->data) {
        deleteNode(node->left, value);
    } else if (value > node->data) {
        deleteNode(node->right, value);
    }
    
}

int main() {
    BinarySearchTree bst;
    bst.root = NULL;

    int n, value;
    cout << "Enter the number of nodes: ";
    cin >> n;
    for (int i = 0; i < n; i++) {
        cout << "Enter value for node " << i + 1 << ": ";
        cin >> value;
        insertNode(bst.root, value);
    }

    cout << "Inorder Traversal: ";
    inorderTraversal(bst.root);
    cout << endl;

    cout << "Preorder Traversal: ";
    preorderTraversal(bst.root);
    cout << endl;

    cout << "Postorder Traversal: ";
    postorderTraversal(bst.root);
    cout << endl;

    return 0;
}