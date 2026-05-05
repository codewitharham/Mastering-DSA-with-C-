#include <iostream>
#include <string>
#include <stack>
#include <queue>

using namespace std;

template <typename T>
struct Node{
    T data;
    Node* left;
    Node* right;

    Node(T val){
        data = val;
        left = NULL;
        right = NULL;
    }
};

template <typename T>
struct ExpressionBST{
    Node<T>* root;
};

template <typename T>
Node<T>* createNode(T val){
    Node<T>* newNode = new Node<T>(val);
    return newNode;
}



int precedence(string op){
    // Logical NOT has highest precedence
    if(op == "!"){
        return 6; 
    }
    // Exponentiation
    else if(op == "^"){
        return 5; 
    }
    // Multiplication / Division
    else if(op == "*" || op == "/"){
        return 4; 
    }
    // Addition / Subtraction
    else if(op == "+" || op == "-"){
        return 3; 
    }
    // Relational and Equality Operators
    else if(op == "==" || op == "!=" || op == "<" || op == ">" || op == "<=" || op == ">="){
        return 2; 
    }
    // Logical AND
    else if(op == "&&"){
        return 1; 
    }
    // Logical OR
    else if(op == "||"){
        return 0; 
    }
    
    // For non-operator characters (operands), return -1
    return -1; 
}

bool isOperator(string token){
    // Check if the token is an operator
    return precedence(token) != -1;
}

bool isOperand(string token){
    // Check if the token is an operand (e.g., a variable or a number)
    return !isOperator(token) && token != "(" && token != ")";
}


vector<string> tokenizeExpression(string expression) {
    vector<string> tokens;
    int expressionLength = expression.length();

    for (int i = 0; i < expressionLength; i++) {
        char c = expression[i];

        if (isspace(c)) {
            continue; // Skip spaces
        } 
        
        // Handle parentheses separately (they should never merge)
        if (c == '(' || c == ')') {
            tokens.push_back(string(1, c));
        }
        // Handle Operators (supporting multi-char like &&, ||, ==)
        else if (isOperator(string(1, c))) {
            string opr = "";
            while (i < expressionLength && isOperator(string(1, expression[i]))) {
                opr += expression[i];
                i++;
                // Stop if we hit a different type of character
                if (i < expressionLength && (isspace(expression[i]) || isalnum(expression[i]) || expression[i] == '(' || expression[i] == ')')) break;
            }
            tokens.push_back(opr);
            i--; // Adjust for outer loop
        }
        // Handle Operands (Numbers and Variables)
        else {
            string operand = "";
            while (i < expressionLength && !isspace(expression[i]) && !isOperator(string(1, expression[i])) && expression[i] != '(' && expression[i] != ')') {
                operand += expression[i];
                i++;
            }
            tokens.push_back(operand);
            i--; 
        }
    }
    return tokens;
}


vector<string> infixToPostfix(string infix){
    // Implement the Shunting Yard algorithm to convert infix to postfix

    vector<string> tokens = tokenizeExpression(infix);
    stack<string> operatorStack;
    queue<string> outputQueue;

    int tokenCount = tokens.size();

    for(int i = 0; i < tokenCount; i++){
        string token = tokens[i];

        if(isOperand(token)){
            outputQueue.push(token);
        }
        else if(isOperator(token)){
            while(!operatorStack.empty() && precedence(operatorStack.top()) >= precedence(token)){
                outputQueue.push(operatorStack.top());
                operatorStack.pop();
            }
            operatorStack.push(token);
        }
        else if(token == "("){
            operatorStack.push(token);
        }
        else if(token == ")"){
            while(!operatorStack.empty() && operatorStack.top() != "("){
                outputQueue.push(operatorStack.top());
                operatorStack.pop();
            }
            if(!operatorStack.empty() && operatorStack.top() == "("){
                operatorStack.pop(); // Pop the '(' from the stack
            }
        }
    }

    // Pop any remaining operators from the stack to the output queue
    while(!operatorStack.empty()){
        outputQueue.push(operatorStack.top());
        operatorStack.pop();
    }

    vector<string> postfixTokens;
    while(!outputQueue.empty()){
        postfixTokens.push_back(outputQueue.front());
        outputQueue.pop();
    }

    return postfixTokens;

}






ExpressionBST<string> createExpressionBST(string expression){
    int exprLength = expression.length();
    
    stack<Node<string>*> nodeStack;

    // Convert infix expression to postfix
    vector<string> postfix = infixToPostfix(expression);
   

    // Build the expression BST from the postfix expression

    
    for(int i = 0; i < postfix.size(); i++){
        string token = postfix[i];

        if(isOperand(token)){
            nodeStack.push(createNode(token)); // If it's an operand, create a node and push to stack
        }
        else if(isOperator(token)){
            Node<string>* newNode = createNode(token); // Create a new node for the operator

            // Pop the top two nodes from the stack to be the right and left children of the new operator node
            if(!nodeStack.empty()){
                newNode->right = nodeStack.top();
                nodeStack.pop();
            }
            if(!nodeStack.empty()){
                newNode->left = nodeStack.top();
                nodeStack.pop();
            }

            // Push the new operator node back to the stack
            nodeStack.push(newNode);
        }
    }

    
    ExpressionBST<string> bst;
    bst.root = nodeStack.top(); // The final node on the stack is the root of the expression BST
    return bst;
}


void printInOrder(Node<string>* node){
    if(node == NULL){
        return;
    }
    printInOrder(node->left);
    cout << node->data << " ";
    printInOrder(node->right);
}

void printPreOrder(Node<string>* node){
    if(node == NULL){
        return;
    }
    cout << node->data << " ";
    printPreOrder(node->left);
    printPreOrder(node->right);
}


void printPostOrder(Node<string>* node){
    if(node == NULL){
        return;
    }
    printPostOrder(node->left);
    printPostOrder(node->right);
    cout << node->data << " ";
}








int main(){

    string expression;
    cout << "Enter a expression: ";
    getline(cin, expression); // Use getline to read the entire expression including spaces

    cout << "Expression: " << expression << endl;

    cout << "Postfix Notation: ";
    vector<string> postfix = infixToPostfix(expression);
    for(int i = 0; i < postfix.size(); i++){
        cout << postfix[i] << " ";
    }

    ExpressionBST<string> bst = createExpressionBST(expression);

    cout << "In-order Traversal: ";
    printInOrder(bst.root);

    cout << "\nPre-order Traversal: ";
    printPreOrder(bst.root);

    cout << "\nPost-order Traversal: ";
    printPostOrder(bst.root);

    return 0;
}