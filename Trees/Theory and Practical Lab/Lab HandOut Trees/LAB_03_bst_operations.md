# LAB 03 — BST Operations
## Validate → Insert → Delete → Fix Bugs → Advanced Problems

---

## PART A — BST Validity Drills

For each tree, determine: **Is this a valid BST?** If not, identify which node violates the invariant and explain why.

---

### Exercise A1

```
     10
    /  \
   5    15
  / \
 3   7
```
Valid BST? ___ If not, which node? ___ Why? ___

---

### Exercise A2

```
     10
    /  \
   5    15
  / \     \
 3   7     20
      \
       12
```
Valid BST? ___

**Critical:** Is 12 valid here? Check ALL constraints:
- 12 > 7 (parent) ✅
- 12 > 5 (grandparent) ✅
- 12 > 10 (great-grandparent)? ___
- 12 is in the LEFT subtree of 10, so it must be < 10. Is it? ___

**Verdict:** ___

---

### Exercise A3

```
     50
    /  \
   25   75
  / \   / \
 10  30 60  80
     /
    20
```
Valid BST? ___

Check node 20:
- 20 < 30 (parent) ✅
- 20 < 25 (grandparent) ✅
- 20 < 50 (root) ✅
- But: 20 > 10? Is there any constraint violated? ___

---

### Exercise A4 — The Sneaky Failure

```
     20
    /  \
   10   30
  / \
 5   25
```
Valid BST? ___

**Key test:** Node 25 is in the LEFT subtree of 20. Therefore 25 must be ___ 20. Is it? ___

---

### Exercise A5 — The Boundary Edge Case

```
     INT_MAX
    /
  INT_MAX - 1
```
Valid BST? ___

Now what about:
```
     INT_MAX
    /  \
  (anything)  ???
```
Can INT_MAX have a RIGHT child? ___ Why? ___

---

### Exercise A6 — Write the Validator

```cpp
// Validate BST correctly using min/max bounds passed down
bool isValidBST(Node* root, long long lo, long long hi) {
    // YOUR CODE
    // Base case: null is valid
    // Check: root->data must be > lo AND < hi
    // Recurse: left subtree — what are the new bounds?
    //          right subtree — what are the new bounds?
}

// Caller: isValidBST(root, LLONG_MIN, LLONG_MAX)
```

Test it on Exercise A4 — it should return false. Trace why:
```
isValidBST(20, -INF, +INF): 20 in range ✅, recurse left
  isValidBST(10, -INF, 20): 10 in range ✅, recurse right
    isValidBST(25, 10, 20): 25 in range (-INF..20)?
      25 < 20? ___ → returns ___
```

---

## PART B — Manual Insertion Traces

For each insertion sequence, draw the resulting BST step by step. Show the tree after EACH insertion.

---

### Exercise B1 — Standard Sequence

Insert in order: `50, 30, 70, 20, 40, 60, 80`

Draw after each insertion:

```
After 50:         After 30:          After 70:
   50               50                  50
                   /                   /  \
                  30                  30   70

After 20:         After 40:          After 60:         After 80:
(draw)            (draw)             (draw)            (draw)
```

**Final inorder traversal:** `___________`

---

### Exercise B2 — Sorted Insertion (The Pathological Case)

Insert in order: `1, 2, 3, 4, 5`

Draw the resulting tree:
```
After all insertions:

1
 \
  2
   \
    3
     ...
```

**Height of resulting tree:** ___ (should be n-1 = 4)
**Height of balanced BST with 5 nodes:** ___ (should be 2)
**Conclusion:** Why is inserting sorted data bad for BST?
```
Answer: ___________________________________________
```

---

### Exercise B3 — Reverse Sorted (Also Bad)

Insert: `5, 4, 3, 2, 1`. Draw the tree. What's the height?

---

### Exercise B4 — Find the Optimal Insert Order

Given values `{1, 2, 3, 4, 5, 6, 7}`, find an insertion order that produces the most balanced BST.

**Hint:** Insert the median first, then medians of each half.

```
Your insertion order: ___________
Resulting tree height: ___
```

---

## PART C — Implement Insert (Three Ways)

---

### Exercise C1 — Recursive (Node*& style) — From Memory

```cpp
void insertNode(Node*& node, int value) {
    // YOUR CODE — no looking!
}
```

---

### Exercise C2 — Recursive (Return Value style)

```cpp
Node* insertNode(Node* root, int value) {
    // YOUR CODE
    // This is the cleaner modern style — return the root of the modified subtree
}
// Usage: root = insertNode(root, value);
```

---

### Exercise C3 — Iterative Insert (Challenging — no recursion)

```cpp
void insertIterative(Node*& root, int value) {
    // YOUR CODE
    // Algorithm:
    // 1. If tree empty, create root, return
    // 2. Traverse: keep a 'current' pointer going left/right
    //    ALSO keep a 'parent' pointer (one step behind)
    // 3. When current == nullptr, create node and attach to parent
    //    (check if value < parent->data → left child, else right child)
}
```

**Test:** Insert `50, 30, 70, 20, 40` iteratively. Verify inorder = `20 30 40 50 70`.

---

## PART D — Delete Operations — All Three Cases

---

### Exercise D1 — Identify the Delete Case

For each deletion, identify which case applies (0 children / 1 child / 2 children):

Tree:
```
          50
        /    \
       30     70
      /  \   /  \
     20   40 60  80
    /
   10
```

| Delete | Case | Why |
|---|---|---|
| 10 | | |
| 60 | | |
| 20 | | |
| 30 | | |
| 70 | | |
| 50 (root) | | |

---

### Exercise D2 — Manual Delete Traces

Using the tree above, trace what happens when you delete 30:

```
Step 1: 30 has two children (20 and 40).
        What is the inorder successor of 30? ___
        How do you find it? ___________

Step 2: Copy inorder successor's value into node 30.
        Tree now: node where 30 was now holds value ___

Step 3: Delete the original successor.
        That successor node has ___ children.
        Apply case ___: ___________

Draw the tree after deletion:

          50
        /    \
       ___   70
      /  \   / \
    20   ___  60  80
    /
   10
```

---

### Exercise D3 — Tricky Delete: Delete Root with Two Children

Tree:
```
      10
     /  \
    5    15
   / \     \
  3   7     20
```

Delete 10 (the root).
- Inorder successor of 10: ___
- How many children does the successor have: ___
- Draw the tree after deletion:

```
(your drawing)
```

---

### Exercise D4 — Implement deleteNode From Scratch

```cpp
// Step 1: Helper to find inorder successor (minimum of right subtree)
Node* findInorderSuccessor(Node* node) {
    // YOUR CODE
    // Go right once, then as far left as possible
}

// Step 2: The full deleteNode
Node* deleteNode(Node* root, int value) {
    // YOUR CODE
    // Return the root of the modified subtree (return-and-rewire pattern)

    // Case 1: not found — return root unchanged
    // Case 2: go left or right
    // Case 3: found it — handle all 3 sub-cases
}
```

**Test sequence:** Start with `50, 30, 70, 20, 40, 60, 80`. Delete in order: 20 (leaf), 70 (one child after removing 80), 30 (two children). Print inorder after each.

---

### Exercise D5 — Verify Your findMinimum Bug Understanding

Given this function from your original code:

```cpp
Node* findMinimum(Node* root){
    Node* currentNode = root->right;   // ← starts at right
    while(currentNode != NULL && currentNode->left != NULL){
        currentNode = currentNode->left;
    }
    return currentNode;
}
```

Answer WITHOUT running code:

**Q1:** Called as `findMinimum(node_30)` on the tree above (30 has children 20 and 40). What does it return?
```
Starts at: root->right = ___
Goes left: 40->left = ___
Returns: ___

Is this the inorder successor of 30? ___
Is this the minimum of the WHOLE subtree rooted at 30? ___
```

**Q2:** What would a CORRECT `findMinimum(root)` return? Write it:
```cpp
Node* trueMinimum(Node* root) {
    // YOUR CODE — finds leftmost node
}
```

**Q3:** Rename the original function to something accurate: `___________`

---

## PART E — Bug Hunt in BST Operations

---

### Bug E1 — Search Returns Wrong Result

```cpp
bool search(Node* root, int value) {
    if (root == nullptr) return true;   // ← bug
    if (root->data == value) return true;
    if (value < root->data) return search(root->left, value);
    return search(root->right, value);
}
```

**Bug:** ___ **Fix:** ___

---

### Bug E2 — Insert Creates Wrong Structure

```cpp
Node* insertNode(Node* root, int value) {
    if (root == nullptr) return new Node(value);
    if (value < root->data)       root->right = insertNode(root->right, value);  // ← bug
    else if (value > root->data)  root->left  = insertNode(root->left,  value);  // ← bug
    return root;
}
```

**Bug:** ___ **Fix:** ___

---

### Bug E3 — Delete Forgets to Return

```cpp
Node* deleteNode(Node* root, int value) {
    if (root == nullptr) return nullptr;
    if (value < root->data) {
        deleteNode(root->left, value);   // ← bug
        return root;
    }
    if (value > root->data) {
        deleteNode(root->right, value);  // ← bug
        return root;
    }
    // ... rest of delete
}
```

**Bug:** ___ **Effect:** ___ **Fix:** ___

---

### Bug E4 — Two-Child Delete Crashes

```cpp
if (root->left != nullptr && root->right != nullptr) {
    Node* successor = findInorderSuccessor(root);
    root->data = successor->data;
    root->right = deleteNode(root->left, successor->data);  // ← bug
}
```

**Bug:** ___ **Fix:** ___

---

### Bug E5 — The Missing Return Warning Bug (From YOUR code)

```cpp
Node* deleteNode(Node*& root, int value) {
    if (root == NULL) return root;
    if (value < root->data) { root->left  = deleteNode(root->left,  value); return root; }
    if (value > root->data) { root->right = deleteNode(root->right, value); return root; }
    if (value == root->data) {
        if (root->left == NULL && root->right == NULL) { delete root; return NULL; }
        if (root->left  == NULL) { Node* t = root->right; delete root; return t; }
        if (root->right == NULL) { Node* t = root->left;  delete root; return t; }
        Node* temp = findMinimum(root);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
        return root;
    }
    // ← Warning fires here
}
```

**One-word fix** (change one keyword to eliminate the warning without changing behavior):

Before: `if (value == root->data) {`
After:  `___ {`

---

## PART F — Build BST From Sorted Array (Balanced)

---

### Exercise F1 — Manual Trace

Given sorted array: `[1, 2, 3, 4, 5, 6, 7]`

Find the insertion order that gives a balanced BST:
```
Median of whole array: 4 → root
Median of left [1,2,3]: ___ → left child
Median of right [5,6,7]: ___ → right child
Continue...
```

Draw the resulting tree.

---

### Exercise F2 — Implement It

```cpp
// Build a balanced BST from a SORTED array
Node* sortedArrayToBST(vector<int>& arr, int lo, int hi) {
    // YOUR CODE
    // Base case: lo > hi → return nullptr
    // Find mid = (lo + hi) / 2
    // root = new Node(arr[mid])
    // root->left  = recurse on arr[lo..mid-1]
    // root->right = recurse on arr[mid+1..hi]
    // return root
}
```

**Test:** `sortedArrayToBST({1,2,3,4,5,6,7}, 0, 6)` should give height 2.

---

## PART G — Advanced BST Algorithms

---

### Exercise G1 — Floor and Ceiling

- **Floor(x):** Largest value in BST that is ≤ x
- **Ceiling(x):** Smallest value in BST that is ≥ x

```cpp
int floor(Node* root, int x) {
    // YOUR CODE
    // If root == nullptr: return INT_MIN (no floor found)
    // If root->data == x: exact match, return x
    // If x < root->data: floor must be in left subtree
    // If x > root->data: floor could be root->data itself,
    //   or something larger in right subtree — take the max
}

int ceiling(Node* root, int x) {
    // YOUR CODE — symmetric to floor
}
```

**Test on tree `{10, 5, 15, 3, 7, 12, 20}`:**
- floor(6) = ___ ceiling(6) = ___
- floor(10) = ___ ceiling(10) = ___
- floor(1) = ___ ceiling(25) = ___

---

### Exercise G2 — Kth Smallest Element

```cpp
int kthSmallest(Node* root, int k) {
    // YOUR CODE
    // Use inorder traversal (gives sorted order)
    // Count nodes visited — when count == k, that's the answer
    // Use a reference parameter or class member for the counter
}
```

**Test:** kthSmallest on `{10,5,15,3,7,12,20}`:
- k=1 → ___ k=3 → ___ k=7 → ___

---

### Exercise G3 — Count Nodes in Range [lo, hi]

```cpp
int countInRange(Node* root, int lo, int hi) {
    // YOUR CODE
    // If root == nullptr: return 0
    // If root->data < lo: range is entirely in right subtree
    // If root->data > hi: range is entirely in left subtree
    // Otherwise: count = 1 + countInRange(left) + countInRange(right)
}
```

---

### Exercise G4 — Convert BST to Sorted Doubly Linked List (In-Place)

This is a classic interview problem. Convert the BST to a doubly linked list using the left pointer as `prev` and right pointer as `next`. No new nodes created.

```cpp
Node* prev = nullptr;
Node* head = nullptr;

void bstToDLL(Node* root) {
    if (!root) return;
    bstToDLL(root->left);                // process left first (inorder!)

    // YOUR CODE: link current node to prev
    if (prev == nullptr) {
        head = root;                     // first node in inorder = head of DLL
    } else {
        prev->right = root;              // prev's next = current
        root->left  = prev;             // current's prev = prev
    }
    prev = root;                         // update prev

    bstToDLL(root->right);
}
```

---

## PART H — Expression Tree Lab

---

### Exercise H1 — Build Expression Tree Manually

Build the expression tree for: `a + b * c - d`

**Step 1:** Convert to postfix using Shunting Yard:
```
Tokens: a + b * c - d
Stack: []  Output: []

Token a: operand → Output: [a]
Token +: operator → Stack: [+]
Token b: operand → Output: [a, b]
Token *: * > + → Stack: [+, *]
Token c: operand → Output: [a, b, c]
Token -: - <= + → pop +, pop nothing (- <= +? check...) → 

(work out the rest)
```

**Postfix result:** `___________`

---

### Exercise H2 — Build Tree from Postfix

Given postfix: `3 4 + 2 *`

Trace the node stack:

| Token | Action | Stack (top→bottom) |
|---|---|---|
| 3 | push Node(3) | [3] |
| 4 | push Node(4) | [4, 3] |
| + | create +(3,4) | [+] |
| 2 | push Node(2) | [2, +] |
| * | create *(+,2) | [*] |

Draw the resulting tree:
```
(your drawing)
```

What does inorder traversal give? `___________`
What is the value if 3=3, 4=4, 2=2? `___________`

---

### Exercise H3 — Evaluate Expression Tree

```cpp
int evaluate(Node* root) {
    // YOUR CODE
    // Leaves are operands (convert string to int)
    // Internal nodes are operators — apply to left and right evaluated results
}
```

---

## SOLUTIONS — Part A

### A1: Valid BST ✅ — all constraints satisfied.

### A2: **INVALID BST ❌** — Node 12 is in the left subtree of 10, so it must be < 10. But 12 > 10. The BST invariant is violated at 10's left subtree.

### A3: Valid BST ✅ — Node 20: 20 < 30 (parent) ✅, 20 < 25 ✅, 20 > 10 (no constraint violated — 20 only needs to be less than its ancestors on the right path, which are 25 and 50). 20 is in the left subtree of 25 and left subtree of 50 — both require it to be < 25 and < 50 ✅.

### A4: **INVALID BST ❌** — Node 25 is in the LEFT subtree of 20, so it must be < 20. But 25 > 20. Violated!

### A5: Valid ✅. INT_MAX cannot have a right child (there's no integer > INT_MAX to go there).

---

## SOLUTIONS — Part B

### B1 Final tree:
```
          50
        /    \
       30     70
      /  \   /  \
     20   40 60  80
```
Inorder: `20 30 40 50 60 70 80`

### B2: Height = 4 (n-1 for n=5). Balanced height = ⌊log₂5⌋ = 2.

### B4: Optimal order: `4, 2, 6, 1, 3, 5, 7` — gives balanced tree of height 2.

---

## SOLUTIONS — Part D

### D1 Delete Cases:
| Delete | Case | Why |
|---|---|---|
| 10 | 0 children | leaf |
| 60 | 0 children | leaf |
| 20 | 1 child | has left child 10 |
| 30 | 2 children | has both 20 and 40 |
| 70 | 2 children | has both 60 and 80 |
| 50 | 2 children | root has both subtrees |

### D2: Deleting 30 — inorder successor = 40 (30's right child, no left child). Replace 30 with 40. Delete old 40 (it's a leaf → Case 0).

### D3: Deleting root 10 — inorder successor = 15 (right child has no left child). Replace 10 with 15. Delete old 15 (has one right child 20 → Case 1, return 20).

---

## SOLUTIONS — Part E

### E1: `return true` should be `return false` — not found means absent, not present.
### E2: left/right assignments are swapped — `value < data` goes LEFT not right.
### E3: Missing `root->left = ` and `root->right = ` before recursive calls — return value not captured.
### E4: `root->left` should be `root->right` — delete successor from RIGHT subtree.
### E5: Change `if (value == root->data)` to `else` — the final branch is exhaustive.

---

## SOLUTIONS — Part G

### G1:
```cpp
int floorBST(Node* root, int x) {
    if (!root) return INT_MIN;
    if (root->data == x) return x;
    if (x < root->data) return floorBST(root->left, x);
    int rightFloor = floorBST(root->right, x);
    return (rightFloor == INT_MIN) ? root->data : rightFloor;
}
```
floor(6)=5, ceiling(6)=7, floor(10)=10, ceiling(10)=10, floor(1)=INT_MIN (none), ceiling(25)=INT_MAX (none)

### G2:
```cpp
int count = 0, result = -1;
void kthSmallestHelper(Node* root, int k) {
    if (!root || count >= k) return;
    kthSmallestHelper(root->left, k);
    if (++count == k) { result = root->data; return; }
    kthSmallestHelper(root->right, k);
}
// k=1→3, k=3→7, k=7→20
```

### G3:
```cpp
int countInRange(Node* root, int lo, int hi) {
    if (!root) return 0;
    if (root->data < lo) return countInRange(root->right, lo, hi);
    if (root->data > hi) return countInRange(root->left,  lo, hi);
    return 1 + countInRange(root->left, lo, hi) + countInRange(root->right, lo, hi);
}
```
