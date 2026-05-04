#include <iostream>
#include <queue>

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



void BST_BreadthFirstSearch(Node* root) {

    queue<Node*> q;

    if(root == NULL) return;

    // process the root node
    q.push(root);
    while(!q.empty()) {
        Node* currentNode = q.front();
        q.pop();

        cout << currentNode->data << " ";

        if(currentNode->left != NULL) {
            q.push(currentNode->left);
        }

        if(currentNode->right != NULL) {
            q.push(currentNode->right);
        }
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

    cout << "Breadth First Search (Level Order Traversal): ";
    BST_BreadthFirstSearch(bst.root);
    

    return 0;
}