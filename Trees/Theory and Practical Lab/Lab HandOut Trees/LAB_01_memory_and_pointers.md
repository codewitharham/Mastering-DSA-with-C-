# LAB 01 — C++ Memory & Pointer Mechanics
## Hands-On Practice: From Pointer Basics to Tree Node Memory

> **How to use this lab:** Work through each Part in order. For every exercise, write your answer **before** looking at the solution. The goal is prediction and reasoning, not just running code.

---

## PART A — Pointer Reading Drills
### Predict the Output Before Running

---

### Exercise A1 — Basic Dereference

```cpp
#include <iostream>
using namespace std;

int main() {
    int x = 42;
    int* p = &x;

    cout << x    << "\n";   // Line 1
    cout << p    << "\n";   // Line 2
    cout << *p   << "\n";   // Line 3

    *p = 100;
    cout << x    << "\n";   // Line 4
    cout << *p   << "\n";   // Line 5

    return 0;
}
```

**Your prediction:**
```
Line 1: ___________
Line 2: ___________   (hint: not a specific number)
Line 3: ___________
Line 4: ___________
Line 5: ___________
```

---

### Exercise A2 — Arrow Operator vs Dot Operator

```cpp
#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
};

int main() {
    Node a;
    a.data = 10;
    a.next = nullptr;

    Node* p = &a;

    cout << a.data    << "\n";   // Line 1
    cout << p->data   << "\n";   // Line 2
    cout << (*p).data << "\n";   // Line 3

    p->data = 99;
    cout << a.data    << "\n";   // Line 4

    return 0;
}
```

**Your prediction:**
```
Line 1: ___________
Line 2: ___________
Line 3: ___________
Line 4: ___________
```

**Question:** Lines 2 and 3 both compile. Are they identical? Why?
```
Answer: ___________________________________________
```

---

### Exercise A3 — Pointer vs Reference

```cpp
#include <iostream>
using namespace std;

void byValue(int x)    { x = 999; }
void byPointer(int* x) { *x = 999; }
void byReference(int& x) { x = 999; }

int main() {
    int a = 1, b = 2, c = 3;

    byValue(a);
    byPointer(&b);
    byReference(c);

    cout << a << " " << b << " " << c << "\n";
    return 0;
}
```

**Your prediction:** `___________`

---

### Exercise A4 — The Node Pointer Trap

```cpp
#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int v) : data(v), left(nullptr), right(nullptr) {}
};

void tryInsert(Node* node, int val) {
    if (node == nullptr) {
        node = new Node(val);  // ← does this work?
    }
}

int main() {
    Node* root = nullptr;
    tryInsert(root, 42);

    if (root == nullptr)
        cout << "root is still NULL\n";
    else
        cout << "root->data = " << root->data << "\n";

    return 0;
}
```

**Your prediction:** `___________`

**Critical question:** WHY? What is the fundamental reason this fails?
```
Answer: ___________________________________________
___________________________________________
```

---

### Exercise A5 — The Reference Fix

Same as A4, but now with the fix. Predict what changes:

```cpp
void tryInsert(Node*& node, int val) {   // ← Node*& instead of Node*
    if (node == nullptr) {
        node = new Node(val);
    }
}

int main() {
    Node* root = nullptr;
    tryInsert(root, 42);

    if (root == nullptr)
        cout << "root is still NULL\n";
    else
        cout << "root->data = " << root->data << "\n";

    return 0;
}
```

**Your prediction:** `___________`

**What changed and why does it work now?**
```
Answer: ___________________________________________
___________________________________________
```

---

### Exercise A6 — Return-and-Rewire Pattern

```cpp
#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int v) : data(v), left(nullptr), right(nullptr) {}
};

Node* rewire(Node* root) {
    if (root == nullptr) return new Node(99);
    root->data += 1;
    return root;
}

int main() {
    Node* a = nullptr;
    Node* b = new Node(5);

    a = rewire(a);
    b = rewire(b);

    cout << a->data << "\n";   // Line 1
    cout << b->data << "\n";   // Line 2
    return 0;
}
```

**Your prediction:**
```
Line 1: ___________
Line 2: ___________
```

---

### Exercise A7 — Stack vs Heap Lifetime

```cpp
#include <iostream>
using namespace std;

struct Node {
    int data;
    Node(int v) : data(v) {}
};

Node* makeHeap() {
    Node* p = new Node(77);  // on heap
    return p;                // returning address of heap object — SAFE
}

Node* makeStack() {
    Node n(88);              // on STACK
    return &n;               // returning address of stack object — DANGER!
}

int main() {
    Node* hp = makeHeap();
    Node* sp = makeStack();  // sp now holds address of DESTROYED object

    cout << hp->data << "\n";  // Line 1
    cout << sp->data << "\n";  // Line 2 — undefined behavior!

    delete hp;
    return 0;
}
```

**Question:** What does Line 1 print? What might Line 2 print? What is the technical term for what sp is after makeStack returns?

```
Line 1: ___________
Line 2: ___________  (could be anything — explain why)
Technical term: ___________
```

---

### Exercise A8 — nullptr Check Chain

```cpp
#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int v) : data(v), left(nullptr), right(nullptr) {}
};

int main() {
    Node* root = new Node(10);
    root->left = new Node(5);
    // root->right is nullptr

    // Which of these crash? Which print safely?
    cout << root->data        << "\n";   // A
    cout << root->left->data  << "\n";   // B
    // cout << root->right->data << "\n"; // C ← commented out intentionally

    bool check1 = (root != nullptr);
    bool check2 = (root->right != nullptr);
    bool check3 = (root->right != nullptr && root->right->data > 5);

    cout << check1 << "\n";   // D
    cout << check2 << "\n";   // E
    cout << check3 << "\n";   // F

    return 0;
}
```

**Your prediction:**
```
A: ___   B: ___   C: would crash? ___
D: ___   E: ___   F: ___
```

**Why is check3 safe even though root->right is nullptr?**
```
Answer: ___________________________________________
```

---

## PART B — Fix the Broken Code
### Each program has exactly one bug. Find it and fix it.

---

### Bug B1 — The Silent Insert Failure

```cpp
struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int v) : data(v), left(nullptr), right(nullptr) {}
};

// Bug: tree never grows beyond root
void insert(Node* root, int val) {
    if (root == nullptr) {
        root = new Node(val);
        return;
    }
    if (val < root->data) insert(root->left, val);
    else                  insert(root->right, val);
}

int main() {
    Node* root = nullptr;
    insert(root, 10);
    insert(root, 5);
    if (root == nullptr) cout << "Tree is empty!\n";
}
```

**Identify the bug:**
```
Bug location: line ___
What's wrong: ___________________________________________
Fixed signature: ___________________________________________
```

---

### Bug B2 — The Infinite Loop

```cpp
void inorder(Node* root) {
    if (root == nullptr) return;
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->left);   // ← subtle
}
```

**Identify the bug:**
```
Bug location: line ___
What's wrong: ___________________________________________
Fix: ___________________________________________
```

---

### Bug B3 — The Memory Leak in Delete

```cpp
Node* deleteLeaf(Node* root, int val) {
    if (root == nullptr) return nullptr;
    if (val < root->data) {
        root->left = deleteLeaf(root->left, val);
        return root;
    }
    if (val > root->data) {
        root->right = deleteLeaf(root->right, val);
        return root;
    }
    // val == root->data, and it's a leaf
    if (root->left == nullptr && root->right == nullptr) {
        return nullptr;   // ← bug is here
    }
    return root;
}
```

**Identify the bug:**
```
Bug location: line "return nullptr"
What's wrong: ___________________________________________
Fix: ___________________________________________
```

---

### Bug B4 — The Wrong Minimum

```cpp
// Supposed to find smallest value in BST
int findMin(Node* root) {
    if (root == nullptr) return -1;
    if (root->left == nullptr) return root->data;
    return findMin(root->right);   // ← bug
}
```

**Identify the bug:**
```
What's wrong: ___________________________________________
Fix: ___________________________________________
```

---

### Bug B5 — The Null Dereference in Height

```cpp
int height(Node* root) {
    return 1 + max(height(root->left), height(root->right));  // ← bug
}
```

**Identify the bug:**
```
What's wrong: ___________________________________________
What happens when root is nullptr: ___________________________________________
Fix: ___________________________________________
```

---

## PART C — Memory Diagram Exercises
### Draw the stack and heap state after each step

---

### Exercise C1

Draw the exact memory state after each numbered line executes:

```cpp
// Step 1
Node* root = nullptr;

// Step 2
root = new Node(10);

// Step 3
root->left = new Node(5);

// Step 4
root->right = new Node(15);

// Step 5
Node* temp = root->left;

// Step 6
temp->data = 99;
```

**After Step 1:**
```
STACK:          HEAP:
root = [NULL]   (empty)
```

**After Step 2:**
```
STACK:              HEAP:
root = [0x???]  →  [data=10, left=null, right=null]
```

**After Step 3:** (draw yourself)
```
STACK:          HEAP:
root = [    ]   
                [    ]  ←  addr: 0x100
                [    ]  ←  addr: 0x200
```

**After Step 5 and 6 — Critical question:**
What is `root->left->data` after Step 6?
```
Answer: ___ — Why? ___________________________________________
```

---

### Exercise C2 — Tracing delete

```cpp
Node* p = new Node(10);    // Step 1
Node* q = p;               // Step 2
delete p;                  // Step 3
p = nullptr;               // Step 4
// cout << q->data;        // Step 5 — DANGER
```

**After Step 2:** How many pointers point to the Node? ___

**After Step 3:** The Node's memory is freed. What does `q` still hold? ___

**After Step 4:** `p` is safe (nullptr). Is `q` safe? ___

**Why is Step 5 dangerous?**
```
Answer: ___________________________________________
```

---

## PART D — Implement From Scratch
### No looking at your old code. Write from memory, then compare.

---

### Exercise D1 — Complete the Node struct

Write a complete Node struct for a binary tree with an integer value. Include a constructor that initializes all fields correctly.

```cpp
// YOUR IMPLEMENTATION:
struct Node {
    // ...
};
```

---

### Exercise D2 — Implement createNode (TWO ways)

**Version 1:** Using the `Node*&` approach (your original style):
```cpp
void createNode(Node*& node, int value) {
    // YOUR IMPLEMENTATION
}
```

**Version 2:** Using return value (modern style):
```cpp
Node* createNode(int value) {
    // YOUR IMPLEMENTATION
}
```

Which is more common in competitive programming and why?
```
Answer: ___________________________________________
```

---

### Exercise D3 — Implement destroyTree

Implement a function that frees ALL nodes in a binary tree, using postorder traversal (children before parent). This is the function your existing code is missing.

```cpp
void destroyTree(Node* root) {
    // YOUR IMPLEMENTATION
    // Hint: what traversal order ensures children are deleted before parent?
}
```

---

### Exercise D4 — Implement height (From Scratch)

```cpp
// Returns height of tree (-1 for empty tree, 0 for single node)
int height(Node* root) {
    // YOUR IMPLEMENTATION
}
```

Test your implementation mentally:
- `height(nullptr)` should return: ___
- `height(single node)` should return: ___
- `height(root with two children, no grandchildren)` should return: ___

---

## PART E — Edge Case Gauntlet

For each scenario, state what should happen and verify with code:

---

### Exercise E1 — Operations on Empty Tree

```cpp
Node* root = nullptr;
```

What should happen for each operation?

| Operation | Expected behavior | Safe or Crash? |
|---|---|---|
| `inorder(root)` | | |
| `insert(root, 5)` with `Node*&` | | |
| `search(root, 5)` | | |
| `deleteNode(root, 5)` | | |
| `height(root)` | | |

---

### Exercise E2 — Single Node Tree

```cpp
Node* root = new Node(10);
```

| Operation | Expected output/behavior |
|---|---|
| Inorder traversal | |
| Height | |
| Delete node 10 | |
| Delete node 5 (not in tree) | |
| Insert 5 | |
| Insert 10 (duplicate) | |

---

### Exercise E3 — Complete Edge Case Test Program

Write a test program that:
1. Creates an empty BST
2. Inserts: 50, 25, 75, 10, 30, 60, 80
3. Prints inorder (verify sorted)
4. Searches for 30 (should find), 35 (should not find)
5. Deletes leaf (10), one-child node (75 after adding 70 only as its left child), two-child node (25)
6. Prints inorder after each delete

```cpp
// YOUR TEST PROGRAM:
#include <iostream>
using namespace std;

struct Node { /* ... */ };

// ... your functions ...

int main() {
    // Test 1: Build tree
    
    // Test 2: Inorder verification
    
    // Test 3: Search tests
    
    // Test 4: Delete leaf
    
    // Test 5: Delete one-child
    
    // Test 6: Delete two-child
    
    return 0;
}
```

---

## PART F — Pointer Reasoning Questions

Answer these conceptually (no code needed):

**F1.** You have `Node* p = new Node(5)`. You pass `p` to a function `f(Node* x)`. Inside f, you do `x = new Node(99)`. After f returns, what does `p` point to? What leaked?

```
p points to: ___________
What leaked: ___________
```

**F2.** You write `Node* p = new Node(5); Node* q = p; delete p; p = nullptr;`. Is `q` safe to use? What is the technical name for q?

```
Safe? ___________
Technical name: ___________
```

**F3.** In your recursive `insertNode(Node*& node, int val)`, when the base case fires (`node == NULL`) and you do `node = new Node(val)`, which variable in the caller actually gets updated?

```
The caller's variable that gets updated: ___________
```

**F4.** Your `deleteNode` has signature `Node* deleteNode(Node*& root, int value)`. It takes `Node*&` AND returns `Node*`. Is the `Node*&` parameter actually needed given the return value is also wired back?

```
Answer: ___________________________________________
Hint: look at the recursive calls inside — are they using the return value or the reference?
```

---

## SOLUTIONS — Part A

### A1
```
Line 1: 42       (x directly)
Line 2: 0x...    (an address — some hex number, system-dependent)
Line 3: 42       (*p dereferences — same as x)
Line 4: 100      (x was changed via *p = 100)
Line 5: 100      (*p still points to x, which is now 100)
```

### A2
```
Line 1: 10       (direct field access)
Line 2: 10       (pointer -> field, same as (*p).data)
Line 3: 10       (explicit dereference then dot)
Line 4: 99       (p->data changed a, they share the same memory)
```
Lines 2 and 3 are **completely identical**. `p->data` is syntactic sugar for `(*p).data`. The compiler generates identical machine code for both.

### A3
```
Output: 1 999 999
```
- `byValue`: copy made, original `a` unchanged → still 1
- `byPointer`: `*x = 999` dereferences and modifies the original → `b` = 999
- `byReference`: `x` is alias for `c`, modifying x modifies c → `c` = 999

### A4
```
Output: "root is still NULL"
```
**Why:** `tryInsert(Node* node, ...)` receives a COPY of `root`. `node` is a local variable holding a copy of the address. `node = new Node(val)` changes the local copy — it does NOT change the caller's `root`. The new Node is created on the heap but immediately leaked (no pointer to it remains after the function returns).

### A5
```
Output: "root->data = 42"
```
**What changed:** `Node*& node` makes `node` an alias for the caller's `root`. `node = new Node(val)` directly writes into the caller's `root` variable. No copy is made.

### A6
```
Line 1: 99    (a was nullptr, rewire returned new Node(99), a = that node)
Line 2: 6     (b->data was 5, rewire did root->data += 1 = 6, returned b)
```

### A7
```
Line 1: 77     (heap object survives function return — address is valid)
Line 2: UNDEFINED — could print 88, 0, garbage, or crash
```
`sp` is a **dangling pointer** — it holds the address of a stack variable that was destroyed when makeStack returned. That memory may be reused for other purposes. Accessing it is undefined behavior.

### A8
```
A: 10   B: 5   C: would crash (nullptr dereference)
D: 1    E: 0   F: 0
```
check3 is safe because of **short-circuit evaluation**. The `&&` operator evaluates left-to-right. If the left side (`root->right != nullptr`) is false, the right side (`root->right->data > 5`) is NEVER evaluated. So we never dereference the nullptr.

---

## SOLUTIONS — Part B

### B1
```cpp
// Bug: Node* root should be Node*& root
void insert(Node*& root, int val) { ... }
// OR use return value pattern:
Node* insert(Node* root, int val) {
    if (root == nullptr) return new Node(val);
    if (val < root->data) root->left = insert(root->left, val);
    else root->right = insert(root->right, val);
    return root;
}
```

### B2
```cpp
// Bug: last line says inorder(root->left) — should be inorder(root->right)
// This causes infinite recursion on the left subtree
void inorder(Node* root) {
    if (root == nullptr) return;
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);   // ← FIXED
}
```

### B3
```cpp
// Bug: memory leak — node is not deleted before returning nullptr
if (root->left == nullptr && root->right == nullptr) {
    delete root;        // ← MUST delete before returning
    return nullptr;
}
```

### B4
```cpp
// Bug: goes right instead of left — minimum is always leftmost
int findMin(Node* root) {
    if (root == nullptr) return -1;
    if (root->left == nullptr) return root->data;
    return findMin(root->left);   // ← FIXED: was root->right
}
```

### B5
```cpp
// Bug: no base case — crashes with nullptr dereference on first null child
int height(Node* root) {
    if (root == nullptr) return -1;   // ← base case added
    return 1 + max(height(root->left), height(root->right));
}
```

---

## SOLUTIONS — Part D

### D1
```cpp
struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int v) : data(v), left(nullptr), right(nullptr) {}
};
```

### D2
```cpp
// Version 1: Node*& style
void createNode(Node*& node, int value) {
    node = new Node(value);
}

// Version 2: return value style (more common in competitive programming)
Node* createNode(int value) {
    return new Node(value);
}
```
Return value style is more common in competitive programming because it's cleaner and works naturally with `root->left = createNode(5)`.

### D3
```cpp
void destroyTree(Node* root) {
    if (root == nullptr) return;
    destroyTree(root->left);    // delete left subtree first
    destroyTree(root->right);   // delete right subtree
    delete root;                // THEN delete this node
    // Postorder: children before parent
}
```

### D4
```cpp
int height(Node* root) {
    if (root == nullptr) return -1;
    return 1 + max(height(root->left), height(root->right));
}
// height(nullptr) = -1
// height(leaf)    = 1 + max(-1,-1) = 0
// height(root with 2 leaf children) = 1 + max(0,0) = 1
```

---

## SOLUTIONS — Part E

### E1
| Operation | Expected behavior | Safe or Crash? |
|---|---|---|
| `inorder(root)` | Does nothing (first line: if root==NULL return) | Safe ✅ |
| `insert(root, 5)` with `Node*&` | Creates new node, root now points to it | Safe ✅ |
| `search(root, 5)` | Returns nullptr/false (not found) | Safe ✅ |
| `deleteNode(root, 5)` | Returns nullptr (nothing to delete) | Safe ✅ |
| `height(root)` | Returns -1 | Safe ✅ |

### F Answers

**F1:** `p` still points to the original Node(5). The new Node(99) is created and immediately leaked — its address was stored in `x` (a local copy), which is destroyed when `f` returns. Memory leak of Node(99).

**F2:** NOT safe. `q` is a **dangling pointer** — it holds the address of memory that has been freed. The technical name is a dangling pointer. Accessing `q->data` is undefined behavior.

**F3:** The function updates `node->left` or `node->right` of the parent — whichever one we passed as the reference argument. In the base case for inserting at `root->left`, the variable that gets updated is `root->left` directly.

**F4:** In your code, the `Node*&` is technically not needed for the external call because of the return value. The recursive calls inside (`root->left = deleteNode(root->left, value)`) use the return value to rewire. The `Node*&` in the signature does allow direct modification but in this specific implementation, the return-and-rewire pattern does all the work. Both approaches work; the `Node*&` is redundant here but harmless.
