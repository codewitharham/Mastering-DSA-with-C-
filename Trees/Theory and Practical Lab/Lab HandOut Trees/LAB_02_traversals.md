# LAB 02 — Tree Traversals
## Predict → Trace → Implement → Break → Challenge

> **Lab Rules:** Always predict before running. The prediction step is where learning happens.

---

## Reference Node Struct (Use for all exercises)

```cpp
#include <iostream>
#include <queue>
#include <stack>
#include <vector>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int v) : data(v), left(nullptr), right(nullptr) {}
};

Node* N(int v) { return new Node(v); }  // shorthand for exercises
```

---

## PART A — Predict the Output

For each tree diagram, write the output of all four traversals WITHOUT running code.

---

### Exercise A1 — Single Node

```
Tree:    10
```

| Traversal | Your Prediction |
|---|---|
| Inorder | |
| Preorder | |
| Postorder | |
| Level Order | |

---

### Exercise A2 — Left-Skewed (degenerate)

```
Tree:     1
         /
        2
       /
      3
     /
    4
```

| Traversal | Your Prediction |
|---|---|
| Inorder | |
| Preorder | |
| Postorder | |
| Level Order | |

**Insight question:** For a left-skewed tree, which traversal output is the same as reading the tree top-to-bottom? Which is bottom-to-top?
```
Top-to-bottom: ___________
Bottom-to-top: ___________
```

---

### Exercise A3 — Right-Skewed (sorted insert order)

```
Tree:   1
         \
          2
           \
            3
             \
              4
```

| Traversal | Your Prediction |
|---|---|
| Inorder | |
| Preorder | |
| Postorder | |
| Level Order | |

---

### Exercise A4 — Perfect Binary Tree

```
Tree:        1
           /   \
          2     3
         / \   / \
        4   5 6   7
```

| Traversal | Your Prediction |
|---|---|
| Inorder | |
| Preorder | |
| Postorder | |
| Level Order | |

---

### Exercise A5 — BST (Your reference tree)

```
Tree:          10
              /   \
             8     30
            / \   /  \
           6   9 25   40
               /      \
              20       50
```

**Note:** This is the exact tree from your `Binary_Search_Tree_RECURSIVE.cpp`

| Traversal | Your Prediction |
|---|---|
| Inorder | |
| Preorder | |
| Postorder | |
| Level Order | |

**Verify:** Does inorder give sorted output? It should — this is a BST.

---

### Exercise A6 — Asymmetric Tree

```
Tree:      5
          / \
         3   8
        /     \
       1       9
        \
         2
```

| Traversal | Your Prediction |
|---|---|
| Inorder | |
| Preorder | |
| Postorder | |
| Level Order | |

---

### Exercise A7 — Expression Tree

```
Tree:       +
           / \
          *   5
         / \
        3   4
```
This represents the expression: `(3 * 4) + 5`

| Traversal | Gives | Your Prediction |
|---|---|---|
| Inorder | Original infix expression | |
| Preorder | Prefix (Polish) notation | |
| Postorder | Postfix (RPN) notation | |

**Manual evaluation via postorder:** show step-by-step:
```
Step 1: ___________
Step 2: ___________
Step 3: ___________
Result: ___________
```

---

### Exercise A8 — Unbalanced Reconstruction Challenge

Given ONLY these two traversal outputs, **draw the tree**:
```
Preorder:  10  5  3  7  15  12  20
Inorder:    3  5  7  10  12  15  20
```

```
Your tree drawing:

           ___
          /   \
        ___   ___
        ...
```

**Hint:** In preorder, the first element is always the root. Find it in inorder — everything left is the left subtree, everything right is the right subtree. Apply recursively.

---

## PART B — Trace the Call Stack

Simulate the recursion by hand. Fill in the execution table step by step.

---

### Exercise B1 — Inorder Call Stack Trace

Tree:
```
      4
     / \
    2   6
   / \
  1   3
```

Fill the execution table. Each row is a function call. `→` means "makes this call next".

| Step | Current Call | Action | Output |
|---|---|---|---|
| 1 | inorder(4) | 4≠null, call left | — |
| 2 | inorder(2) | 2≠null, call left | — |
| 3 | inorder(1) | 1≠null, call left | — |
| 4 | inorder(null) | | |
| 5 | ← back in inorder(1) | | |
| 6 | | | |
| 7 | | | |
| 8 | | | |
| 9 | | | |
| 10 | | | |
| ... | continue until done | | |

**Final output:** `___________`

---

### Exercise B2 — Postorder Stack Depth

For the tree in B1, what is the **maximum depth** the call stack reaches during postorder traversal? Draw the stack at its deepest point.

```
Maximum depth: ___ frames

Stack at deepest point (top to bottom):
┌────────────────┐
│ postorder(___) │ ← top
├────────────────┤
│ postorder(___) │
├────────────────┤
│ postorder(___) │
├────────────────┤
│ postorder(___) │ ← bottom
└────────────────┘
```

---

### Exercise B3 — Level Order Queue Trace

Same tree as B1. Fill in the queue state at each step:

| Step | Dequeue | Output | Queue after enqueue |
|---|---|---|---|
| 1 | 4 | 4 | [2, 6] |
| 2 | | | |
| 3 | | | |
| 4 | | | |
| 5 | | | |
| 6 | | | |

---

## PART C — Implement ALL Traversals From Scratch

**Instructions:** Close all reference documents. Implement each function from memory. Then test against the predictions from Part A.

---

### Exercise C1 — All Four Recursive Traversals

```cpp
// Implement all four. DO NOT look at your existing code.

void inorder(Node* root) {
    // YOUR CODE
}

void preorder(Node* root) {
    // YOUR CODE
}

void postorder(Node* root) {
    // YOUR CODE
}

void levelOrder(Node* root) {
    // YOUR CODE — requires #include <queue>
}
```

**Test harness — build these trees and verify against Part A predictions:**

```cpp
// Build the A4 perfect tree
Node* buildA4() {
    Node* root = N(1);
    root->left  = N(2); root->right = N(3);
    root->left->left  = N(4); root->left->right  = N(5);
    root->right->left = N(6); root->right->right = N(7);
    return root;
}

// Build the A5 BST
Node* buildA5() {
    Node* root = N(10);
    root->left  = N(8);  root->right = N(30);
    root->left->left  = N(6);  root->left->right  = N(9);
    root->right->left = N(25); root->right->right = N(40);
    root->right->left->left  = N(20);
    root->right->right->right = N(50);
    return root;
}

int main() {
    Node* t = buildA5();
    cout << "Inorder: ";    inorder(t);    cout << "\n";
    cout << "Preorder: ";   preorder(t);   cout << "\n";
    cout << "Postorder: ";  postorder(t);  cout << "\n";
    cout << "LevelOrder: "; levelOrder(t); cout << "\n";
    return 0;
}
```

---

### Exercise C2 — All Three Iterative DFS Traversals

Implement from scratch. No STL traversal helpers — only `stack<Node*>`.

```cpp
// Iterative Preorder: 1 stack, push right before left
void preorderIterative(Node* root) {
    // YOUR CODE
}

// Iterative Inorder: 1 stack + current pointer (the hardest one)
void inorderIterative(Node* root) {
    // YOUR CODE
    // Hint: you need TWO things running simultaneously:
    //   - a pointer 'cur' to track where you're going
    //   - a stack to save nodes you'll come back to
}

// Iterative Postorder: 2 stacks — s1 for processing, s2 for collecting
void postorderIterative(Node* root) {
    // YOUR CODE
}
```

**Self-check:** For each iterative version, verify it gives IDENTICAL output to the recursive version on the A5 tree.

---

### Exercise C3 — Level Order with Level Grouping

The basic level order prints everything flat. Now implement the grouped version that returns a `vector<vector<int>>` — each inner vector is one level.

```cpp
vector<vector<int>> levelOrderGrouped(Node* root) {
    // YOUR CODE
    // Key insight: before processing a level, snapshot q.size()
    // That tells you how many nodes are on this level
}
```

Expected output for A4 tree:
```
[[1], [2, 3], [4, 5, 6, 7]]
```

---

### Exercise C4 — Reverse Level Order

Return levels from bottom to top (deepest level first).

```cpp
vector<vector<int>> reverseLevelOrder(Node* root) {
    // YOUR CODE
    // Hint: do normal level order grouped, then reverse the result
    // OR use a stack to reverse as you go
}
```

Expected output for A4:
```
[[4, 5, 6, 7], [2, 3], [1]]
```

---

## PART D — Bug Hunt
### Each traversal has exactly one subtle bug. Find it and explain why it causes incorrect output.

---

### Bug D1 — Broken Preorder (Wrong order)

```cpp
void preorder(Node* root) {
    if (root == nullptr) return;
    preorder(root->left);    // ← look carefully at order
    cout << root->data << " ";
    preorder(root->right);
}
```

For tree A4 (`1, 2, 3, 4, 5, 6, 7`):
- **Buggy output:** `___________`
- **What traversal does this actually implement?** `___________`
- **Fix:** `___________`

---

### Bug D2 — Level Order with Missing Nodes

```cpp
void levelOrder(Node* root) {
    if (root == nullptr) return;
    queue<Node*> q;
    q.push(root);
    while (!q.empty()) {
        Node* node = q.front();
        q.pop();
        cout << node->data << " ";
        q.push(node->left);    // ← bug
        q.push(node->right);
    }
}
```

**What's wrong:** `___________`

**What crash will occur:** `___________`

**Fix:** `___________`

---

### Bug D3 — Iterative Preorder Reversed

```cpp
void preorderIterative(Node* root) {
    stack<Node*> st;
    if (root == nullptr) return;
    st.push(root);
    while (!st.empty()) {
        Node* node = st.top(); st.pop();
        cout << node->data << " ";
        if (node->left)  st.push(node->left);   // ← check push order
        if (node->right) st.push(node->right);
    }
}
```

For tree A4:
- **Buggy output:** `___________`
- **Correct preorder output:** `___________`
- **What's wrong with the push order:** `___________`
- **Fix:** `___________`

---

### Bug D4 — Iterative Inorder Missing Nodes

```cpp
void inorderIterative(Node* root) {
    stack<Node*> st;
    Node* cur = root;
    while (cur != nullptr) {          // ← check loop condition
        while (cur != nullptr) {
            st.push(cur);
            cur = cur->left;
        }
        cur = st.top(); st.pop();
        cout << cur->data << " ";
        cur = cur->right;
    }
}
```

**What's wrong with the outer loop condition:**
```
Bug: ___________________________________________
The loop stops when: ___________________________________________
Should stop when: ___________________________________________
Fix: ___________________________________________
```

---

### Bug D5 — Level Order Grouped Wrong Count

```cpp
vector<vector<int>> levelOrderGrouped(Node* root) {
    vector<vector<int>> result;
    if (!root) return result;
    queue<Node*> q;
    q.push(root);
    while (!q.empty()) {
        vector<int> level;
        while (!q.empty()) {           // ← inner loop bug
            Node* node = q.front(); q.pop();
            level.push_back(node->data);
            if (node->left)  q.push(node->left);
            if (node->right) q.push(node->right);
        }
        result.push_back(level);
    }
    return result;
}
```

**What's wrong:** `___________`

**What output does this produce:** `___________`

**Fix:** `___________`

---

## PART E — Traversal Modifications

Implement these creative variations. They appear frequently in interviews.

---

### Exercise E1 — Reverse Inorder (Descending BST)

Standard inorder gives ascending order for BST. Implement a traversal that gives **descending order** (Right → Root → Left):

```cpp
void reverseInorder(Node* root) {
    // YOUR CODE
    // Hint: swap left and right in standard inorder
}
```

Test on A5 BST. Expected: `50 40 30 25 20 10 9 8 6`

---

### Exercise E2 — Zigzag Level Order

Print levels alternately left-to-right then right-to-left:

```
Level 0 (L→R): 10
Level 1 (R→L): 30 8
Level 2 (L→R): 6 9 25 40
Level 3 (R→L): 50 20
```

```cpp
vector<vector<int>> zigzagLevelOrder(Node* root) {
    // YOUR CODE
    // Hint: use a flag to reverse alternate levels
    // OR use deque to push from front or back
}
```

---

### Exercise E3 — Right Side View

Print only the rightmost node at each level (what you'd see standing to the right of the tree):

```
For A5 tree: 10, 30, 40, 50
```

```cpp
vector<int> rightSideView(Node* root) {
    // YOUR CODE
    // Hint: use level-order grouped — take last element of each level
}
```

---

### Exercise E4 — Count Nodes Per Level

Return a vector where `result[i]` = number of nodes at level `i`:

```cpp
vector<int> nodesPerLevel(Node* root) {
    // YOUR CODE
}
// For A5: [1, 2, 4, 2]
```

---

### Exercise E5 — Mirror / Invert a Tree

Swap left and right children at every node (mirror the tree):

```
Before:          10              After:          10
               /   \                           /   \
              8     30                        30    8
```

```cpp
Node* invertTree(Node* root) {
    // YOUR CODE
    // Hint: postorder — fix children before fixing parent
}
```

---

## PART F — Reconstruct Tree From Traversals

**Key theorem:** Given **Preorder + Inorder**, you can uniquely reconstruct the tree. (Postorder + Inorder also works. Preorder + Postorder alone does NOT always give a unique tree.)

---

### Exercise F1 — Manual Reconstruction

Given:
```
Preorder: 3  9  20  15  7
Inorder:  9  3  15  20  7
```

Draw the tree step by step:
```
Step 1: Preorder[0] = 3 → root is 3
Step 2: Find 3 in inorder: [9 | 3 | 15 20 7]
        → left subtree inorder:  [9]
        → right subtree inorder: [15, 20, 7]
Step 3: Preorder for left:  next 1 element = [9]
        Preorder for right: next 3 elements = [20, 15, 7]
Step 4: Build recursively...

Your tree:
      ___
     /   \
   ___   ___
```

---

### Exercise F2 — Implement the Reconstruction

```cpp
// Given preorder and inorder arrays, build the tree
Node* buildTree(vector<int>& preorder, vector<int>& inorder,
                int preStart, int preEnd, int inStart, int inEnd) {
    // YOUR CODE
    // Algorithm:
    // 1. preorder[preStart] = current root value
    // 2. Find that value's index in inorder → call it 'mid'
    // 3. leftSize = mid - inStart
    // 4. Recursively build left: preorder[preStart+1 .. preStart+leftSize], inorder[inStart..mid-1]
    // 5. Recursively build right: preorder[preStart+leftSize+1..preEnd], inorder[mid+1..inEnd]
}
```

---

## PART G — Challenge Problems

These are harder problems that combine traversal concepts. Solve one per study session.

---

### Challenge G1 — Lowest Common Ancestor (LCA)

Find the lowest common ancestor of two nodes p and q in a binary tree (NOT necessarily a BST).

```
LCA of 6 and 9 in A5 tree = 8
LCA of 20 and 50 in A5 tree = 30
LCA of 6 and 50 in A5 tree = 10
```

```cpp
Node* lca(Node* root, Node* p, Node* q) {
    // YOUR CODE
    // Key insight: if root == p OR root == q, return root
    // Recursively find in left and right subtrees
    // If found in both: root is LCA
    // If found in one: return that result
}
```

---

### Challenge G2 — Diameter of Binary Tree

The diameter is the length of the longest path between any two nodes (the path may or may not pass through the root).

```cpp
int diameter = 0;  // global

int diameterHelper(Node* root) {
    // returns height, updates diameter as side effect
    // YOUR CODE
    // At each node: path through this node = leftHeight + rightHeight + 2
    // Update global diameter if this is larger
    // Return: 1 + max(leftHeight, rightHeight)
}
```

---

### Challenge G3 — Level Order Zig-Zag with Deque

Implement zigzag level order using a single `deque<Node*>` instead of reversing:

```cpp
vector<vector<int>> zigzagDeque(Node* root) {
    // YOUR CODE
    // For left-to-right level: deque front, push children to back
    // For right-to-left level: deque back, push children to front
    // Toggle direction each level
}
```

---

## SOLUTIONS — Part A

### A1 — Single Node
- Inorder: `10`  |  Preorder: `10`  |  Postorder: `10`  |  Level: `10`

### A2 — Left Skewed
- Inorder: `4 3 2 1`  |  Preorder: `1 2 3 4`  |  Postorder: `4 3 2 1`  |  Level: `1 2 3 4`
- Top-to-bottom: **Preorder** (root first, then down left)
- Bottom-to-top: **Inorder** (deepest left leaf first, then up)

### A3 — Right Skewed
- Inorder: `1 2 3 4`  |  Preorder: `1 2 3 4`  |  Postorder: `4 3 2 1`  |  Level: `1 2 3 4`
- **Note:** Inorder = Preorder = Level for right-skewed. Inorder traversal of a right-skewed BST (built by inserting sorted) gives sorted output.

### A4 — Perfect Binary Tree
- Inorder:    `4 2 5 1 6 3 7`
- Preorder:   `1 2 4 5 3 6 7`
- Postorder:  `4 5 2 6 7 3 1`
- Level:      `1 2 3 4 5 6 7`

### A5 — Your BST
- Inorder:    `6 8 9 10 20 25 30 40 50`
- Preorder:   `10 8 6 9 30 25 20 40 50`
- Postorder:  `6 9 8 20 25 50 40 30 10`
- Level:      `10 8 30 6 9 25 40 20 50`

### A6 — Asymmetric
- Inorder:    `1 2 3 5 8 9`
- Preorder:   `5 3 1 2 8 9`
- Postorder:  `2 1 3 9 8 5`
- Level:      `5 3 8 1 9 2`

### A7 — Expression Tree
- Inorder (infix): `3 * 4 + 5`
- Preorder (prefix): `+ * 3 4 5`
- Postorder (RPN): `3 4 * 5 +`
- Evaluation: Step 1: pop 3,4 apply * = 12. Step 2: pop 12,5 apply + = 17. Result: **17**

### A8 — Reconstruction
```
Preorder: 10  5  3  7  15  12  20
Inorder:   3  5  7  10  12  15  20

Step 1: root = 10. In inorder: [3 5 7 | 10 | 12 15 20]
Step 2: left subtree = {3,5,7}. Preorder for left: [5 3 7]
        right subtree = {12,15,20}. Preorder for right: [15 12 20]
Step 3: left root = 5. In {3 5 7}: [3 | 5 | 7] → left=3, right=7
        right root = 15. In {12 15 20}: [12 | 15 | 20] → left=12, right=20
```

```
        10
       /   \
      5     15
     / \   /  \
    3   7 12   20
```

---

## SOLUTIONS — Part B

### B1 — Inorder Call Stack Trace (A1 tree: 4/2/6/1/3)

| Step | Current Call | Action | Output |
|---|---|---|---|
| 1 | inorder(4) | call left | — |
| 2 | inorder(2) | call left | — |
| 3 | inorder(1) | call left | — |
| 4 | inorder(null) | return | — |
| 5 | back in inorder(1) | print | 1 |
| 6 | inorder(null) [right of 1] | return | — |
| 7 | back in inorder(2) | print | 2 |
| 8 | inorder(3) | call left→null | — |
| 9 | back in inorder(3) | print | 3 |
| 10 | inorder(null) [right of 3] | return | — |
| 11 | back in inorder(4) | print | 4 |
| 12 | inorder(6) | both nulls | — |
| 13 | back in inorder(6) | print | 6 |
**Final: `1 2 3 4 6`**

---

## SOLUTIONS — Part D

### D1
Bug: `preorder(root->left)` before the print makes it INORDER, not preorder.

### D2
Bug: `q.push(node->left)` and `q.push(node->right)` without null checks. Enqueueing nullptr then calling `q.front()->data` crashes.
Fix: `if (node->left) q.push(node->left);`

### D3
Bug: push left before right. Stack is LIFO — right needs to be pushed first so left is on top and processed first.
Fix: push right first, then left.

### D4
Bug: outer loop `while (cur != nullptr)` should be `while (cur != nullptr || !st.empty())`.
When `cur` becomes null after processing the rightmost node in a subtree, there may still be saved nodes in the stack. The current condition exits too early.

### D5
Bug: inner loop `while (!q.empty())` drains the ENTIRE queue each iteration. After the first iteration, all nodes are processed and the outer loop exits. Everything ends up in one level.
Fix: `int levelSize = q.size(); for (int i = 0; i < levelSize; i++)` — snapshot the size first.

---

## SOLUTIONS — Part E

### E1 — Reverse Inorder
```cpp
void reverseInorder(Node* root) {
    if (!root) return;
    reverseInorder(root->right);    // right first
    cout << root->data << " ";
    reverseInorder(root->left);     // then left
}
```

### E2 — Zigzag Level Order
```cpp
vector<vector<int>> zigzagLevelOrder(Node* root) {
    vector<vector<int>> result;
    if (!root) return result;
    queue<Node*> q;
    q.push(root);
    bool leftToRight = true;
    while (!q.empty()) {
        int size = q.size();
        vector<int> level(size);
        for (int i = 0; i < size; i++) {
            Node* node = q.front(); q.pop();
            int idx = leftToRight ? i : (size - 1 - i);  // place at correct position
            level[idx] = node->data;
            if (node->left)  q.push(node->left);
            if (node->right) q.push(node->right);
        }
        result.push_back(level);
        leftToRight = !leftToRight;
    }
    return result;
}
```

### E3 — Right Side View
```cpp
vector<int> rightSideView(Node* root) {
    vector<int> result;
    if (!root) return result;
    queue<Node*> q;
    q.push(root);
    while (!q.empty()) {
        int size = q.size();
        for (int i = 0; i < size; i++) {
            Node* node = q.front(); q.pop();
            if (i == size - 1) result.push_back(node->data);  // last in level
            if (node->left)  q.push(node->left);
            if (node->right) q.push(node->right);
        }
    }
    return result;
}
```

### E5 — Mirror Tree
```cpp
Node* invertTree(Node* root) {
    if (!root) return nullptr;
    Node* left  = invertTree(root->left);   // recurse first (postorder style)
    Node* right = invertTree(root->right);
    root->left  = right;   // swap
    root->right = left;
    return root;
}
```

---

## SOLUTIONS — Challenges

### G1 — LCA
```cpp
Node* lca(Node* root, Node* p, Node* q) {
    if (!root || root == p || root == q) return root;
    Node* left  = lca(root->left,  p, q);
    Node* right = lca(root->right, p, q);
    if (left && right) return root;   // p in left, q in right → this node is LCA
    return left ? left : right;        // one subtree has both
}
```

### G2 — Diameter
```cpp
int maxDiameter = 0;
int diameterHelper(Node* root) {
    if (!root) return -1;
    int leftH  = diameterHelper(root->left);
    int rightH = diameterHelper(root->right);
    int pathThrough = leftH + rightH + 2;   // path through this node
    maxDiameter = max(maxDiameter, pathThrough);
    return 1 + max(leftH, rightH);
}
int diameter(Node* root) {
    maxDiameter = 0;
    diameterHelper(root);
    return maxDiameter;
}
```
