#include <iostream>
#include <stack>

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


void BST_DepthFirstSearch_PREORDER_Traversal(Node* root) {
    stack<Node*> DFSStack;

    if(root == NULL) return;

    // process the root node
    DFSStack.push(root);
    while(!DFSStack.empty()) {
        Node* currentNode = DFSStack.top();
        DFSStack.pop();

        cout << currentNode->data << " ";

        if(currentNode->right != NULL) {
            DFSStack.push(currentNode->right);
        }

        if(currentNode->left != NULL) {
            DFSStack.push(currentNode->left);
        }
    }
  
}

void BST_DepthFirstSearch_INORDER_Traversal(Node* root) {
    stack<Node*> DFSStack;
    Node* currentNode = root;

    while(currentNode != NULL || !DFSStack.empty()) {
        while(currentNode != NULL) {
            DFSStack.push(currentNode);
            currentNode = currentNode->left;
        }

        currentNode = DFSStack.top();
        DFSStack.pop();

        cout << currentNode->data << " ";

        currentNode = currentNode->right;
    }
}

void BST_DepthFirstSearch_POSTORDER_Traversal(Node* root) {
    if (root == NULL) return;
    stack<Node*> s1, s2;
    s1.push(root);
    
    while (!s1.empty()) {
        Node* node = s1.top();
        s1.pop();
        s2.push(node);

        if (node->left) s1.push(node->left);
        if (node->right) s1.push(node->right);
    }

    while (!s2.empty()) {
        cout << s2.top()->data << " ";
        s2.pop();
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

    cout << "Preorder Traversal: ";
    BST_DepthFirstSearch_PREORDER_Traversal(bst.root);
    cout << endl;

    cout << "Inorder Traversal: ";
    BST_DepthFirstSearch_INORDER_Traversal(bst.root);
    cout << endl;   

    cout << "Postorder Traversal: ";
    BST_DepthFirstSearch_POSTORDER_Traversal(bst.root);
    cout << endl;

    

    return 0;
}