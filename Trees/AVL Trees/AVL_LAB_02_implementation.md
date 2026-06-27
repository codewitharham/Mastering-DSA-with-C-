# AVL LAB 02 — Full Implementation
## Implement → Test → Break → Fix → Verify

---

## PART A — Implement Height & Balance Utilities

**Ground rule:** Every AVL function depends on these. Get them wrong and everything above fails silently.

---

### Exercise A1 — Implement and Test `getHeight`

```cpp
// Version 1 (yours to write):
int getHeight(Node* n) {
    // Must return -1 for nullptr
    // Must return n->height for a valid node
    // YOUR CODE (1 line)
}

// Test ALL of these manually:
Node* leaf = new Node(5);          // height = 0
Node* nullNode = nullptr;

cout << getHeight(nullNode) << "\n";   // must print: -1
cout << getHeight(leaf)     << "\n";   // must print: 0

leaf->height = 3;  // manually set to test
cout << getHeight(leaf)     << "\n";   // must print: 3
```

**Critical edge case:** What happens if you forget to handle nullptr?
```
Without null check: ___________
```

---

### Exercise A2 — Implement `updateHeight`

```cpp
void updateHeight(Node* n) {
    // YOUR CODE
    // Formula: n->height = 1 + max(getHeight(n->left), getHeight(n->right))
    // Must also handle nullptr input safely
}

// Test:
Node* root = new Node(10);
root->left  = new Node(5);   // height 0
root->right = new Node(15);  // height 0
updateHeight(root);
cout << root->height << "\n";  // expected: 1

root->left->left = new Node(3);  // height 0
updateHeight(root->left);        // update 5's height first
updateHeight(root);              // then update 10
cout << root->height << "\n";    // expected: 2
```

**Trace the test manually before running:**
```
After adding 3:
  h(5): left=h(3)=0, right=h(null)=-1 → h(5) = 1+max(0,-1) = ___
  h(10): left=h(5)=1, right=h(15)=0  → h(10) = 1+max(1,0)  = ___
```

---

### Exercise A3 — Implement `getBalanceFactor`

```cpp
int getBalanceFactor(Node* n) {
    // YOUR CODE
    // Return 0 for nullptr
    // Return h(left) - h(right) otherwise
}

// Test all cases:
Node* balanced = new Node(10);
balanced->left  = new Node(5);
balanced->right = new Node(15);
// Both children are leaves (height 0)
cout << getBalanceFactor(balanced) << "\n";  // expected: 0

Node* leftHeavy = new Node(10);
leftHeavy->left = new Node(5);
leftHeavy->left->height = 1;  // fake a taller subtree
updateHeight(leftHeavy);
cout << getBalanceFactor(leftHeavy) << "\n";  // expected: +2
```

---

## PART B — Implement All Four Rotations

**Instructions:** Implement WITHOUT looking at reference code. Then run tests.

---

### Exercise B1 — rotateRight

```cpp
//        Z                 Y
//       / \               / \
//      Y   T3    →→→    T1   Z
//     / \                   / \
//   T1   T2               T2   T3

Node* rotateRight(Node* Z) {
    // Step 1: Save Y (Z's left child) and T2 (Y's right child)

    // Step 2: Y->right = Z  (Z becomes Y's right child)
    //         Z->left  = T2 (T2 moves to Z's left)

    // Step 3: updateHeight(Z) FIRST, then updateHeight(Y)

    // Step 4: return Y (new root)

    // YOUR CODE:
}
```

**Verification test:**

```cpp
// Build: Z=30, Y=20, T1=10, T2=25, T3=null
Node* Z = new Node(30);
Z->left  = new Node(20);
Z->left->left  = new Node(10);
Z->left->right = new Node(25);
// Update heights manually:
updateHeight(Z->left->left);   // h=0
updateHeight(Z->left->right);  // h=0
updateHeight(Z->left);         // h=1
updateHeight(Z);               // h=2

Node* result = rotateRight(Z);

// Verify:
cout << result->data        << "\n";  // expected: 20 (Y is new root)
cout << result->left->data  << "\n";  // expected: 10 (T1 unchanged)
cout << result->right->data << "\n";  // expected: 30 (Z is now right child)
cout << result->right->left->data << "\n";  // expected: 25 (T2 moved)
cout << result->right->height     << "\n";  // expected: 1
cout << result->height            << "\n";  // expected: 2
```

---

### Exercise B2 — rotateLeft

```cpp
//     Z                    Y
//    / \                  / \
//   T1   Y      →→→     Z   T3
//       / \            / \
//     T2   T3        T1   T2

Node* rotateLeft(Node* Z) {
    // YOUR CODE — mirror of rotateRight
}
```

**Verification test:**
```cpp
// Build: Z=10, T1=null, Y=20, T2=15, T3=30
Node* Z = new Node(10);
Z->right       = new Node(20);
Z->right->left  = new Node(15);
Z->right->right = new Node(30);
updateHeight(Z->right->left);
updateHeight(Z->right->right);
updateHeight(Z->right);
updateHeight(Z);

Node* result = rotateLeft(Z);
cout << result->data        << "\n";  // expected: 20
cout << result->left->data  << "\n";  // expected: 10
cout << result->right->data << "\n";  // expected: 30
cout << result->left->right->data << "\n";  // expected: 15 (T2 moved)
cout << result->height      << "\n";  // expected: 2
```

---

### Exercise B3 — rotateLeftRight (LR Double Rotation)

```cpp
Node* rotateLeftRight(Node* Z) {
    // Step 1: Left rotate Z's left child
    // Step 2: Right rotate Z
    // YOUR CODE (2 lines)
}
```

**Test — insert 30, 10, 20 (LR case):**
```cpp
Node* root = new Node(30);
root->left = new Node(10);
root->left->right = new Node(20);
updateHeight(root->left->right);
updateHeight(root->left);
updateHeight(root);

// Manually verify: root BF = +2, root->left BF = -1 → LR case
cout << getBalanceFactor(root)        << "\n";  // +2
cout << getBalanceFactor(root->left)  << "\n";  // -1

Node* result = rotateLeftRight(root);
cout << result->data        << "\n";  // expected: 20
cout << result->left->data  << "\n";  // expected: 10
cout << result->right->data << "\n";  // expected: 30
cout << result->height      << "\n";  // expected: 1
```

---

### Exercise B4 — rotateRightLeft (RL Double Rotation)

```cpp
Node* rotateRightLeft(Node* Z) {
    // Step 1: Right rotate Z's right child
    // Step 2: Left rotate Z
    // YOUR CODE (2 lines)
}
```

---

## PART C — Implement AVL Insert

---

### Exercise C1 — `rebalance` First

```cpp
Node* rebalance(Node* node) {
    // Step 1: updateHeight(node)
    // Step 2: compute bf = getBalanceFactor(node)
    // Step 3: if bf == 2 → check left child's bf → LL or LR
    // Step 4: if bf == -2 → check right child's bf → RR or RL
    // Step 5: return node (possibly rotated)
    // YOUR CODE:
}
```

---

### Exercise C2 — Full AVL Insert

```cpp
Node* avlInsert(Node* root, int value) {
    // Part 1: BST insert (exactly as before)
    // Part 2: return rebalance(root)  ← the one-line addition
    // YOUR CODE:
}
```

**Critical test — Sorted Insert:**
```cpp
Node* root = nullptr;
for (int v : {1, 2, 3, 4, 5, 6, 7}) {
    root = avlInsert(root, v);
}
// A plain BST would give a linked list of height 6.
// An AVL tree must give height ≤ 2.

cout << "Root: " << root->data     << "\n";  // expected: 4
cout << "Height: " << root->height << "\n";  // expected: 2
cout << "AVL valid: " << isAVL(root) << "\n"; // expected: 1 (true)

// Inorder should still be sorted:
inorder(root); cout << "\n";  // expected: 1 2 3 4 5 6 7
```

**Reverse sorted test:**
```cpp
Node* root2 = nullptr;
for (int v : {7, 6, 5, 4, 3, 2, 1}) {
    root2 = avlInsert(root2, v);
}
cout << "Root: " << root2->data << "\n";   // expected: 4
cout << "Height: " << root2->height << "\n"; // expected: 2
```

---

### Exercise C3 — Trace Each Insert Manually

Insert sequence: `5, 2, 8, 1, 3` — predict the tree state after each:

| After insert | Tree shape | Root | Height | Any rotation? |
|---|---|---|---|---|
| 5 | single node | 5 | 0 | No |
| 2 | 5 with left child 2 | 5 | 1 | No |
| 8 | | | | |
| 1 | | | | |
| 3 | | | | |

---

## PART D — Implement AVL Delete

---

### Exercise D1 — findMin Helper

```cpp
Node* findMin(Node* node) {
    // Find leftmost node (inorder successor helper)
    // YOUR CODE
}
```

---

### Exercise D2 — Full AVL Delete

```cpp
Node* avlDelete(Node* root, int value) {
    // Part 1: BST delete (find node, handle 3 cases)
    // Part 2: return rebalance(root) at the end
    // YOUR CODE:
}
```

**Test sequence — verify AVL stays balanced after each delete:**
```cpp
// Build tree: 1..7 sorted insert (gives balanced tree rooted at 4)
Node* root = nullptr;
for (int v : {1,2,3,4,5,6,7}) root = avlInsert(root, v);

// Delete leaf
root = avlDelete(root, 1);
cout << "After delete 1: valid=" << isAVL(root) << " root=" << root->data << "\n";

// Delete node with one child
root = avlDelete(root, 2);
cout << "After delete 2: valid=" << isAVL(root) << " root=" << root->data << "\n";

// Delete root (two children)
int oldRoot = root->data;
root = avlDelete(root, oldRoot);
cout << "After delete root(" << oldRoot << "): valid=" << isAVL(root) << "\n";

// Delete non-existent value
root = avlDelete(root, 99);
cout << "After delete 99 (not found): valid=" << isAVL(root) << "\n";

inorder(root); cout << "\n";
```

---

## PART E — Full Test Harness

### Exercise E1 — The Degeneration Test

This proves AVL fixes the BST problem:

```cpp
#include <iostream>
#include <chrono>
using namespace std;

// Implement both BST and AVL insert
struct BSTNode { int data; BSTNode* left; BSTNode* right; BSTNode(int v):data(v),left(nullptr),right(nullptr){} };
BSTNode* bstInsert(BSTNode* root, int v) {
    if (!root) return new BSTNode(v);
    if (v < root->data) root->left  = bstInsert(root->left,  v);
    else                root->right = bstInsert(root->right, v);
    return root;
}
int bstHeight(BSTNode* r) { return r ? 1+max(bstHeight(r->left),bstHeight(r->right)) : -1; }

int main() {
    const int N = 10000;
    
    // Insert 1..N in sorted order
    BSTNode* bstRoot = nullptr;
    Node*    avlRoot = nullptr;
    
    for (int i = 1; i <= N; i++) {
        bstRoot = bstInsert(bstRoot, i);
        avlRoot = avlInsert(avlRoot, i);
    }
    
    cout << "N = " << N << " (sorted insertion)\n";
    cout << "BST height: " << bstHeight(bstRoot) << "\n";     // expected: N-1 = 9999
    cout << "AVL height: " << avlRoot->height    << "\n";     // expected: ~13-14
    cout << "Theoretical max AVL: ~" << (int)(1.44 * log2(N)) << "\n\n";
    
    // Verify AVL is still valid
    cout << "AVL property holds: " << isAVL(avlRoot) << "\n";
    
    return 0;
}
```

**Predicted outputs before running:**
```
BST height: _____ (formula: N - 1 = _____)
AVL height: _____ (formula: ~1.44 * log2(10000) ≈ _____)
```

---

### Exercise E2 — Random Insert Stress Test

```cpp
#include <cstdlib>
#include <ctime>

int main() {
    srand(42);  // fixed seed for reproducibility
    Node* root = nullptr;
    
    int inserted = 0;
    for (int i = 0; i < 1000; i++) {
        int v = rand() % 10000;
        root = avlInsert(root, v);
        inserted++;
        
        // Verify AVL property every 100 inserts
        if (inserted % 100 == 0) {
            if (!isAVL(root)) {
                cout << "AVL VIOLATED after " << inserted << " inserts!\n";
                return 1;
            }
        }
    }
    cout << "All 1000 insertions: AVL valid ✅\n";
    cout << "Final height: " << root->height << "\n";
    
    // Now delete 500 random elements
    srand(42);  // same seed = same values
    int deleted = 0;
    for (int i = 0; i < 500; i++) {
        int v = rand() % 10000;
        root = avlDelete(root, v);
        deleted++;
        
        if (deleted % 100 == 0) {
            if (!isAVL(root)) {
                cout << "AVL VIOLATED after " << deleted << " deletes!\n";
                return 1;
            }
        }
    }
    cout << "All 500 deletions: AVL valid ✅\n";
    return 0;
}
```

---

## PART F — Edge Cases

Test each edge case. State what should happen, then verify with code.

---

### Exercise F1 — Empty Tree Operations

```cpp
Node* root = nullptr;

// What should happen for each?
root = avlInsert(root, 10);
cout << "Insert into empty: root=" << root->data << " height=" << root->height << "\n";
// expected: ___

root = avlDelete(root, 10);
cout << "Delete only node: root is " << (root ? "not null" : "null") << "\n";
// expected: ___

root = avlDelete(root, 10);  // delete from empty tree
cout << "Delete from empty: root is " << (root ? "not null" : "null") << "\n";
// expected: ___
```

---

### Exercise F2 — Duplicate Insert

```cpp
Node* root = nullptr;
root = avlInsert(root, 10);
root = avlInsert(root, 10);  // duplicate
root = avlInsert(root, 10);  // another duplicate

cout << "Height after 3 identical inserts: " << root->height << "\n";
// expected: 0 (only one node)
cout << "AVL valid: " << isAVL(root) << "\n";
// expected: 1
```

---

### Exercise F3 — Delete Non-Existent Value

```cpp
Node* root = nullptr;
for (int v : {5, 3, 7}) root = avlInsert(root, v);

root = avlDelete(root, 99);  // not in tree
cout << "After deleting non-existent 99:\n";
cout << "  Root: " << root->data << "\n";     // expected: 5 (unchanged)
cout << "  AVL valid: " << isAVL(root) << "\n";  // expected: 1
```

---

### Exercise F4 — Delete Root Repeatedly

```cpp
Node* root = nullptr;
for (int v : {1,2,3,4,5}) root = avlInsert(root, v);

cout << "Deleting root repeatedly:\n";
while (root) {
    cout << "Root: " << root->data << " height=" << root->height;
    root = avlDelete(root, root->data);
    cout << " → AVL: " << (root ? (isAVL(root) ? "✅" : "❌") : "null") << "\n";
}
```

**Predicted sequence of roots:** `___________`

---

### Exercise F5 — All 4 Rotation Cases In One Sequence

Construct minimal sequences that trigger each case:

```cpp
// LL Case: insert ?, ?, ? (3 values that trigger right rotation)
// Your sequence: ___________

// RR Case:
// Your sequence: ___________

// LR Case: insert ?, ?, ? (3 values that trigger double rotation)
// Your sequence: ___________

// RL Case:
// Your sequence: ___________

// For each, verify:
// 1. After 2 inserts: no rotation needed
// 2. After 3rd insert: rotation triggered
// 3. Final height: 1 (all 3 nodes, balanced)
```

---

## PART G — Bug Hunt in Complete AVL Implementation

Each program compiles but produces wrong results. Find the bug.

---

### Bug G1 — Insert produces wrong root

```cpp
Node* avlInsert(Node* root, int value) {
    if (!root) return new Node(value);
    if (value < root->data) root->left  = avlInsert(root->left,  value);
    else if (value > root->data) root->right = avlInsert(root->right, value);
    else return root;
    updateHeight(root);   // ← bug
    return root;          // ← bug
}
// Inserting 30, 20, 10 gives height 2 instead of 1
```

Bug: `___________` Fix: `___________`

---

### Bug G2 — Delete leaves unbalanced tree

```cpp
Node* avlDelete(Node* root, int value) {
    if (!root) return nullptr;
    if (value < root->data)      root->left  = avlDelete(root->left,  value);
    else if (value > root->data) root->right = avlDelete(root->right, value);
    else {
        if (!root->left || !root->right) {
            Node* child = root->left ? root->left : root->right;
            delete root;
            return child;
        }
        Node* succ = root->right;
        while (succ->left) succ = succ->left;
        root->data  = succ->data;
        root->right = avlDelete(root->right, succ->data);
    }
    updateHeight(root);  // ← bug (two lines instead of one)
    return root;         // ← bug
}
```

Bug: `___________` Fix: `___________`

---

### Bug G3 — rotateRight corrupts T2

```cpp
Node* rotateRight(Node* Z) {
    Node* Y  = Z->left;
    Node* T2 = Y->right;
    Y->right = Z;
    Z->left  = Y;     // ← bug — Z->left should point to T2
    updateHeight(Z);
    updateHeight(Y);
    return Y;
}
```

Bug: `___________`
Consequence: `___________`
Fix: `___________`

---

### Bug G4 — Wrong BF check for RL

```cpp
if (bf == -2) {
    if (getBalance(node->right) <= 0) return rotateLeft(node);    // RR
    else { node->left = rotateRight(node->right); return rotateLeft(node); }  // ← bug
}
```

Bug: `___________`
Consequence: `___________`
Fix: `___________`

---

### Bug G5 — Height not updated before BF check in rebalance

```cpp
Node* rebalance(Node* node) {
    // updateHeight(node);  ← this line is MISSING
    int bf = getBalance(node);  // uses stale height!
    if (bf == 2) { ... }
    if (bf == -2) { ... }
    return node;
}
```

Bug: `___________`
When does it cause wrong behavior: `___________`

---

## PART H — Challenge: AVL Property Verifier

Implement a complete AVL validator that checks:
1. BST property (all values in bounds)
2. Height correctness (stored height == computed height)
3. Balance factor validity (|BF| ≤ 1 at every node)

```cpp
bool isValidAVL(Node* root, long long lo = LLONG_MIN, long long hi = LLONG_MAX) {
    if (!root) return true;

    // Check 1: BST property
    if (root->data <= lo || root->data >= hi) {
        cout << "BST VIOLATION at " << root->data << "\n";
        return false;
    }

    // Check 2: Height correctness
    int computedHeight = 1 + max(getHeight(root->left), getHeight(root->right));
    if (root->height != computedHeight) {
        cout << "HEIGHT WRONG at " << root->data
             << " stored=" << root->height
             << " computed=" << computedHeight << "\n";
        return false;
    }

    // Check 3: Balance factor
    int bf = getBalanceFactor(root);
    if (bf > 1 || bf < -1) {
        cout << "BALANCE VIOLATED at " << root->data << " BF=" << bf << "\n";
        return false;
    }

    return isValidAVL(root->left,  lo,          root->data) &&
           isValidAVL(root->right, root->data,  hi);
}
```

**Challenge extension:** Deliberately break the AVL tree (manually set a wrong height or wrong pointer) and verify your validator catches it:

```cpp
Node* root = nullptr;
for (int v : {1,2,3,4,5}) root = avlInsert(root, v);

cout << "Valid: " << isValidAVL(root) << "\n";  // should print: 1

// Deliberately corrupt:
root->height = 99;  // wrong height
cout << "After corruption: " << isValidAVL(root) << "\n";  // should print: 0
```

---

## SOLUTIONS — Part B

### B1 — rotateRight
```cpp
Node* rotateRight(Node* Z) {
    Node* Y  = Z->left;
    Node* T2 = Y->right;
    Y->right = Z;
    Z->left  = T2;
    updateHeight(Z);
    updateHeight(Y);
    return Y;
}
```

### B2 — rotateLeft
```cpp
Node* rotateLeft(Node* Z) {
    Node* Y  = Z->right;
    Node* T2 = Y->left;
    Y->left  = Z;
    Z->right = T2;
    updateHeight(Z);
    updateHeight(Y);
    return Y;
}
```

### B3 — rotateLeftRight
```cpp
Node* rotateLeftRight(Node* Z) {
    Z->left = rotateLeft(Z->left);
    return rotateRight(Z);
}
```

### B4 — rotateRightLeft
```cpp
Node* rotateRightLeft(Node* Z) {
    Z->right = rotateRight(Z->right);
    return rotateLeft(Z);
}
```

---

## SOLUTIONS — Part C

### C1 — rebalance
```cpp
Node* rebalance(Node* node) {
    updateHeight(node);
    int bf = getBalanceFactor(node);
    if (bf == 2) {
        if (getBalanceFactor(node->left) >= 0) return rotateRight(node);
        else { node->left = rotateLeft(node->left); return rotateRight(node); }
    }
    if (bf == -2) {
        if (getBalanceFactor(node->right) <= 0) return rotateLeft(node);
        else { node->right = rotateRight(node->right); return rotateLeft(node); }
    }
    return node;
}
```

### C2 — avlInsert
```cpp
Node* avlInsert(Node* root, int value) {
    if (!root) return new Node(value);
    if (value < root->data)      root->left  = avlInsert(root->left,  value);
    else if (value > root->data) root->right = avlInsert(root->right, value);
    else return root;
    return rebalance(root);
}
```

### C3 — Insert Trace for 5,2,8,1,3
| After insert | Root | Height | Rotation |
|---|---|---|---|
| 5 | 5 | 0 | No |
| 2 | 5 | 1 | No |
| 8 | 5 | 1 | No |
| 1 | 5 | 2 | No (BF(5)=+1) |
| 3 | 5 | 2 | No (BF(2)=-1, BF(5)=+1, all valid) |

---

## SOLUTIONS — Part F

### F4 — Predicted deletion sequence
```
Sorted 1-5 AVL tree root = 2 (after rotations from sorted insert):
Actually for 1,2,3,4,5:
- Insert 1: root=1
- Insert 2: root=1, h=1, BF=-1
- Insert 3: BF=-2 at 1, RR case → rotateLeft(1) → root=2
- Insert 4: 2's right subtree gets 4 under 3 → BF(2)=-1, OK
- Insert 5: BF at 3=-2 → rotateLeft(3) → 4 rises
  Final: root=2, left=1, right=4, 4's left=3, 4's right=5

Deleting roots in sequence:
  Delete 2: inorder successor = 3. Replace 2 with 3. Now root=3, left=1, right=4(left=null,right=5)
    BF(4)=-1 OK, BF(3)=0... actually BF(3)=h(1)-h(4)=0-1=-1 OK
  Delete 3: inorder successor = 4. Replace 3 with 4. Root=4, left=1, right=5
    BF(4)=0 OK
  Delete 4: inorder successor = 5. Replace 4 with 5. Root=5, left=1, right=null
    BF(5)=+1 OK
  Delete 5: root=1, no rotation needed
  Delete 1: null
```

### F5 — Sequences for each case
```
LL: 30, 20, 10  → 10<20<30, all go left → rotateRight(30)
RR: 10, 20, 30  → all go right → rotateLeft(10)
LR: 30, 10, 20  → 20 in right subtree of 10 which is left child → LR
RL: 10, 30, 20  → 20 in left subtree of 30 which is right child → RL
```

---

## SOLUTIONS — Part G

### G1: Missing `return rebalance(root)` — just updating height is not enough. Must call rebalance to potentially rotate. Fix: replace last two lines with `return rebalance(root);`

### G2: Same as G1 — should be `return rebalance(root)` not `updateHeight + return root`.

### G3: `Z->left = Y` should be `Z->left = T2`. This creates a cycle (Z->left points back to Y, which is Z's new parent) and loses T2 entirely. Fix: `Z->left = T2;`

### G4: `node->left = rotateRight(node->right)` — sets LEFT child when it should set RIGHT. Fix: `node->right = rotateRight(node->right);`

### G5: Without `updateHeight(node)`, `getBalance` uses the node's old height (from before its subtrees changed). This means the BF check operates on stale data — the rotation might not be triggered when needed, or the wrong rotation applied.
