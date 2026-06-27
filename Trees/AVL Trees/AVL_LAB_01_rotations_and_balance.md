# AVL LAB 01 — Rotations & Balance Factor
## Calculate → Identify → Trace → Fix Bugs → Full Insert Trace

> **Lab Rule:** Always write your answer before checking the solution. The act of being wrong and correcting is how the rotation logic becomes muscle memory.

---

## PART A — Balance Factor Calculation Drills

For each tree, compute the **height** and **balance factor (BF)** of every node.

**Formulas:**
```
height(leaf)    = 0
height(nullptr) = -1
height(node)    = 1 + max(height(left), height(right))
BF(node)        = height(left) - height(right)
```

---

### Exercise A1 — Simple Tree

```
        20
       /  \
      10   30
```

Fill the table:

| Node | h(left) | h(right) | height | BF | Valid AVL? |
|---|---|---|---|---|---|
| 10 | -1 | -1 | ___ | ___ | ___ |
| 30 | -1 | -1 | ___ | ___ | ___ |
| 20 | ___ | ___ | ___ | ___ | ___ |

---

### Exercise A2 — One-sided Tree

```
        30
       /
      20
     /
    10
```

| Node | h(left) | h(right) | height | BF | Valid AVL? |
|---|---|---|---|---|---|
| 10 | | | | | |
| 20 | | | | | |
| 30 | | | | | |

**Which node first becomes invalid?** ___
**What is its BF?** ___

---

### Exercise A3 — After One Rotation

After inserting 10, 20, 30 into an AVL tree (triggers RR rotation), you get:

```
      20
     /  \
    10   30
```

Verify: compute all BFs and confirm this is valid AVL.

| Node | BF | Valid? |
|---|---|---|
| 10 | | |
| 30 | | |
| 20 | | |

---

### Exercise A4 — Larger Tree

```
            40
           /  \
          20   60
         /  \    \
        10   30   70
                 /
                65
```

Compute height and BF for every node bottom-up:

| Node | h(left) | h(right) | height | BF | Valid? |
|---|---|---|---|---|---|
| 10 | -1 | -1 | 0 | 0 | ✅ |
| 30 | | | | | |
| 65 | | | | | |
| 70 | | | | | |
| 20 | | | | | |
| 60 | | | | | |
| 40 | | | | | |

**Is this a valid AVL tree?** ___ **If not, which node is the problem?** ___

---

### Exercise A5 — The Sneaky Violation

```
            50
           /  \
          25   75
         /  \
        10   40
            /  \
           30   45
```

Compute all BFs. Find the violation:

| Node | height | BF | Valid? |
|---|---|---|---|
| 10 | | | |
| 30 | | | |
| 45 | | | |
| 40 | | | |
| 25 | | | |
| 75 | | | |
| 50 | | | |

---

### Exercise A6 — Write the BF Calculator

```cpp
// Implement both functions
int getHeight(Node* n) {
    // YOUR CODE — must handle nullptr
}

int getBalanceFactor(Node* n) {
    // YOUR CODE
}

// Test: for a leaf node, getBalanceFactor should return 0
// For nullptr, getBalanceFactor should return 0
```

---

## PART B — Identify the Imbalance Case

For each imbalanced subtree, identify: **Which case? (LL/RR/LR/RL)** and **Which rotation(s) to apply?**

**Decision rule:**
```
BF = +2 AND left child BF ≥ 0  → LL  → rotateRight
BF = +2 AND left child BF < 0  → LR  → rotateLeft(child), rotateRight
BF = -2 AND right child BF ≤ 0 → RR  → rotateLeft
BF = -2 AND right child BF > 0 → RL  → rotateRight(child), rotateLeft
```

---

### Exercise B1

```
      30 (BF=+2)
     /
    20 (BF=+1)
   /
  10
```

Case: ___ Rotation: ___

---

### Exercise B2

```
      10 (BF=-2)
        \
         20 (BF=-1)
           \
            30
```

Case: ___ Rotation: ___

---

### Exercise B3

```
      30 (BF=+2)
     /
    10 (BF=-1)
      \
       20
```

Case: ___ Rotation: ___

---

### Exercise B4

```
      10 (BF=-2)
        \
         30 (BF=+1)
        /
       20
```

Case: ___ Rotation: ___

---

### Exercise B5

```
         50 (BF=+2)
        /
       30 (BF=+1)
      /  \
     20   40
    /
   10
```

Imbalanced node: ___ BF of imbalanced node: ___
BF of its relevant child: ___
Case: ___ Rotation: ___

---

### Exercise B6

```
         50 (BF=-2)
           \
            70 (BF=+1)
           /  \
          60   80
               \
                90
```

Case: ___ Rotation: ___

---

### Exercise B7 — Tricky: Compute BF First

```
         40
        /  \
       20   60
      /       \
     10        70
                 \
                  80
```

First compute all BFs. Then identify:
- Which node is imbalanced? ___
- Its BF: ___
- Relevant child's BF: ___
- Case: ___

---

### Exercise B8 — Post-Insert Imbalance Trace

After inserting 5 into this AVL tree:
```
         20
        /  \
       10   30
      /
     7
```

Step 1: Where is 5 inserted? ___
Step 2: Walk up from 5. At which node does |BF| = 2? ___
Step 3: What is that node's BF? ___
Step 4: What is the relevant child's BF? ___
Step 5: Which case? ___ Which rotation? ___

---

## PART C — Manual Rotation Traces

Perform each rotation on paper. Draw the BEFORE and AFTER tree.

---

### Exercise C1 — Right Rotation

Perform `rotateRight` on node Z:

```
BEFORE:
         Z (= 30)
        /         \
       Y (= 20)   T3 (= null)
      /     \
    T1(=10)  T2(=25)
```

After rotateRight(Z), fill in:
```
AFTER:
         ___ (new root = ?)
        /         \
      ___           ___
                   /   \
                  ___   ___
```

What moved where?
- Y (20) is now: ___
- Z (30) is now: ___
- T2 (25) moved from: ___ to: ___
- T1 (10) stayed at: ___

Heights after rotation:
- h(Z = 30) = ___ (only has T2 as left child and T3 as right)
- h(Y = 20) = ___

---

### Exercise C2 — Left Rotation

Perform `rotateLeft` on node Z:

```
BEFORE:
      Z (= 10)
     /        \
   T1(=null)   Y (= 20)
              /     \
           T2(=15)  T3(=30)
```

```
AFTER:
         ___
        /   \
      ___   ___
     /   \
   ___   ___
```

---

### Exercise C3 — Left-Right Double Rotation

```
BEFORE:
         Z (= 30)
        /           \
       Y (= 10)    T4(=null)
      /     \
   T1(=null) X (= 20)
            /    \
          T2(=15) T3(=25)
```

**Step 1 — rotateLeft(Y=10):**
Draw tree after rotating 10:
```
         Z (= 30)
        /           \
       ___          T4
      /   \
    ___   ___
         /   \
       ___   ___
```

**Step 2 — rotateRight(Z=30):**
Draw final tree:
```
(your drawing)
```

Final root after LR rotation: ___
Final inorder traversal: ___

---

### Exercise C4 — Right-Left Double Rotation

```
BEFORE:
       Z (= 10)
      /          \
    T1(=null)    Y (= 30)
               /     \
             X(=20)  T4(=null)
            /    \
          T2(=15) T3(=25)
```

Perform RL rotation (rotateRight(Y) then rotateLeft(Z)):

**Step 1 — rotateRight(Y=30):**
```
(draw)
```

**Step 2 — rotateLeft(Z=10):**
```
(draw)
```

Final root: ___ Final inorder: ___

---

## PART D — Rotation Pointer Rewiring

Fill in the exact pointer assignments that happen in each rotation. No diagrams — just code understanding.

---

### Exercise D1 — rotateRight(Z) pointer table

| Before rotation | After rotation |
|---|---|
| `Z->left = Y` | `Y->right = ___` |
| `Y->right = T2` | `Z->left = ___` |
| `Z->right = T3` | T3: unchanged at `Z->right` |
| `Y->left = T1` | T1: unchanged at `Y->left` |

Height update order:
1. First update: `___` (why? _____)
2. Second update: `___` (why? _____)

Return value: `___`

---

### Exercise D2 — rotateLeft(Z) pointer table

| Before rotation | After rotation |
|---|---|
| `Z->right = Y` | `Y->left = ___` |
| `Y->left = T2` | `Z->right = ___` |

Height update order: 1st: `___`, 2nd: `___`
Return value: `___`

---

### Exercise D3 — LR rotation pointer sequence

For `rotateLeftRight(Z)`:
1. First call: `___` returns new `___` stored in `Z->left`
2. Second call: `___` returns new subtree root
3. Return value of rotateLeftRight: `___`

---

## PART E — Bug Hunt in Rotation Code

Each function has exactly one bug. Find it and explain the consequence.

---

### Bug E1 — Wrong rotation direction

```cpp
Node* rotateRight(Node* Z) {
    Node* Y  = Z->right;   // ← bug
    Node* T2 = Y->left;    // ← bug (consequence of first bug)
    Y->left  = Z;
    Z->right = T2;
    updateHeight(Z);
    updateHeight(Y);
    return Y;
}
```

Bug: `___________` — This is actually `___` rotation, not right rotation.

---

### Bug E2 — Wrong T2 assignment

```cpp
Node* rotateLeft(Node* Z) {
    Node* Y  = Z->right;
    Node* T2 = Y->right;   // ← bug — which child of Y should T2 be?
    Y->left  = Z;
    Z->right = T2;
    updateHeight(Z);
    updateHeight(Y);
    return Y;
}
```

Bug: `___________`
Consequence: `___________`

---

### Bug E3 — Wrong height update order

```cpp
Node* rotateRight(Node* Z) {
    Node* Y  = Z->left;
    Node* T2 = Y->right;
    Y->right = Z;
    Z->left  = T2;
    updateHeight(Y);   // ← wrong order
    updateHeight(Z);
    return Y;
}
```

Bug: `___________`
Consequence: `___________`

---

### Bug E4 — Missing return in rebalance

```cpp
Node* rebalance(Node* node) {
    updateHeight(node);
    int bf = getBalance(node);
    if (bf == 2) {
        if (getBalance(node->left) >= 0) rotateRight(node);  // ← bug
        else { node->left = rotateLeft(node->left); rotateRight(node); }  // ← bug
    }
    if (bf == -2) {
        if (getBalance(node->right) <= 0) return rotateLeft(node);
        else { node->right = rotateRight(node->right); return rotateLeft(node); }
    }
    return node;
}
```

Bug: `___________`
Consequence: `___________`

---

### Bug E5 — Wrong case detection

```cpp
Node* rebalance(Node* node) {
    updateHeight(node);
    int bf = getBalance(node);
    if (bf == 2) {
        if (getBalance(node->left) > 0)    return rotateRight(node);  // ← LL check
        else                               // ← LR case
            { node->left = rotateLeft(node->left); return rotateRight(node); }
    }
    if (bf == -2) {
        if (getBalance(node->right) < 0)   return rotateLeft(node);   // ← RR check
        else
            { node->right = rotateRight(node->right); return rotateLeft(node); }
    }
    return node;
}
```

Subtle bug: The LL check uses `> 0` instead of `>= 0`. What case does this miss?
```
Missing case: when left child has BF = ___, which should be ___ case,
              but the code falls through to ___ case instead.
              This causes ___________
```

---

## PART F — Full AVL Insert Trace

Insert this sequence one by one. After EACH insert: draw the tree, compute all BFs, and note if a rotation was needed.

**Sequence:** 10, 20, 30, 40, 50, 25

---

### Step F1 — Insert 10

```
Tree:    10
         h=0, BF=0
Any rotation? ___
```

---

### Step F2 — Insert 20

```
Tree:
(draw)

All BFs: 10→___, 20→___
Any rotation? ___
```

---

### Step F3 — Insert 30 ← TRIGGERS ROTATION

```
Before rotation:
(draw the unbalanced tree with BFs)

Imbalanced node: ___, BF=___
Child BF: ___
Case: ___
Rotation: ___

After rotation:
(draw the balanced tree)

All BFs after: ___
```

---

### Step F4 — Insert 40

```
After inserting 40 into the tree from Step F3:
(draw)

All BFs: ___
Any rotation? ___
```

---

### Step F5 — Insert 50 ← TRIGGERS ROTATION

```
Before rotation:
(draw with BFs)

Imbalanced node: ___, BF=___
Case: ___
Rotation: ___

After rotation:
(draw)
```

---

### Step F6 — Insert 25 ← TRIGGERS DOUBLE ROTATION

```
Where does 25 insert? ___

Before rotation:
(draw with BFs marked — find the imbalanced node)

Imbalanced node: ___, BF=___
Child BF: ___
Case: ___
Rotation needed: ___

Step 1 of rotation:
(draw intermediate state)

Step 2 of rotation:
(draw final balanced tree)

Final inorder traversal: ___
```

---

## SOLUTIONS — Part A

### A1
| Node | h(left) | h(right) | height | BF | Valid? |
|---|---|---|---|---|---|
| 10 | -1 | -1 | 0 | 0 | ✅ |
| 30 | -1 | -1 | 0 | 0 | ✅ |
| 20 | 0 | 0 | 1 | 0 | ✅ |

### A2
| Node | h(left) | h(right) | height | BF |
|---|---|---|---|---|
| 10 | -1 | -1 | 0 | 0 |
| 20 | 0 | -1 | 1 | +1 |
| 30 | 1 | -1 | 2 | **+2 ❌** |

Node 30 is first invalid. BF = +2.

### A4
| Node | h(left) | h(right) | height | BF | Valid? |
|---|---|---|---|---|---|
| 10 | -1 | -1 | 0 | 0 | ✅ |
| 30 | -1 | -1 | 0 | 0 | ✅ |
| 65 | -1 | -1 | 0 | 0 | ✅ |
| 70 | 0 | -1 | 1 | +1 | ✅ |
| 20 | 0 | 0 | 1 | 0 | ✅ |
| 60 | -1 | 1 | 2 | **-2 ❌** | |
| 40 | 1 | 2 | 3 | -1 | ✅ |

Node **60** has BF = -2. Not valid AVL. (60 has no left child and right child of height 1.)

### A5
| Node | height | BF | Valid? |
|---|---|---|---|
| 10 | 0 | 0 | ✅ |
| 30 | 0 | 0 | ✅ |
| 45 | 0 | 0 | ✅ |
| 40 | 1 | 0 | ✅ |
| 25 | 2 | **+2 ❌** | |
| 75 | 0 | 0 | ✅ |
| 50 | 3 | +1 | ✅ but only if 25 were fixed |

Node **25** is invalid: h(left=10)=0, h(right=40)=1+1=2... wait:
h(40) = 1+max(h(30),h(45)) = 1+max(0,0) = 1
h(25) = 1+max(h(10),h(40)) = 1+max(0,1) = 2
BF(25) = 0-1 = **-1** ✅ Actually valid!

h(50) = 1+max(h(25),h(75)) = 1+max(2,0) = 3
BF(50) = h(25)-h(75) = 2-0 = **+2 ❌**

Node **50** is the violator.

---

## SOLUTIONS — Part B

| Exercise | Case | Rotation |
|---|---|---|
| B1 | LL (BF=+2, child BF=+1≥0) | rotateRight(30) |
| B2 | RR (BF=-2, child BF=-1≤0) | rotateLeft(10) |
| B3 | LR (BF=+2, child BF=-1<0) | rotateLeft(10), rotateRight(30) |
| B4 | RL (BF=-2, child BF=+1>0) | rotateRight(30), rotateLeft(10) |
| B5 | LL (BF(50)=+2, BF(30)=+1≥0) | rotateRight(50) |
| B6 | RL (BF(50)=-2, BF(70)=+1>0) | rotateRight(70), rotateLeft(50) |
| B7 | 60 has BF=-2, right child 70 has BF=-1≤0 → RR → rotateLeft(60). (Wait: node 40 has BF: h(20)=1, h(60)=2 → BF=-1 ✅. Node 60: h(null)=-1, h(70)=1 → BF=-2 ❌.) Case RR, rotateLeft(60). |
| B8 | 5 inserted at 7->left. Walk up: 7(BF=+1), 10(BF=+2). Left child(7) BF=+1≥0 → LL → rotateRight(10) |

---

## SOLUTIONS — Part C

### C1 — Right Rotation on Z=30
```
BEFORE:              AFTER:
    30(Z)               20(Y)
   /     \             /     \
  20(Y)  null         10(T1)  30(Z)
 /    \                      /    \
10(T1) 25(T2)             25(T2) null(T3)
```
- Y(20) is new root
- Z(30) is Y's right child
- T2(25) moved from Y's right to Z's left
- T1(10) unchanged at Y's left
- h(Z=30) = 1+max(h(T2=25)=0, h(T3=null)=-1) = 1+0 = 1
- h(Y=20) = 1+max(h(T1=10)=0, h(Z=30)=1) = 1+1 = 2

### C2 — Left Rotation on Z=10
```
AFTER:
      20(Y)
     /     \
   10(Z)   30(T3)
  /     \
null(T1) 15(T2)
```

---

## SOLUTIONS — Part D

### D1
| Before | After |
|---|---|
| Z->left = Y | Y->right = **Z** |
| Y->right = T2 | Z->left = **T2** |

Height order: 1st **Z** (it's now lower — lost T1, gained T2), 2nd **Y** (it now includes Z's subtree).
Return: **Y**

### D2
Y->left = **Z**, Z->right = **T2**.
Height order: 1st **Z**, 2nd **Y**. Return: **Y**

---

## SOLUTIONS — Part E

### E1: `Z->right` should be `Z->left`. This implements rotateLeft not rotateRight.

### E2: `T2 = Y->right` should be `T2 = Y->left`. In left rotation, T2 is Y's LEFT child (it needs to move to Z's right). Using Y->right takes the wrong subtree — BST ordering is violated.

### E3: `updateHeight(Y)` before `updateHeight(Z)`. Y's height computation uses Z's stale height (before T2 was moved). Fix: update Z first, then Y.

### E4: `rotateRight(node)` called without `return` — result is discarded, `node` is returned unchanged. The tree is structurally changed by the rotation but the parent sees the old (now wrong) pointer. Fix: `return rotateRight(node)`.

### E5: Left child BF = 0 (balanced left child) is a valid LL case. With `> 0`, BF=0 falls into the `else` branch and incorrectly applies LR rotation. Fix: `>= 0`.

---

## SOLUTIONS — Part F (Final States)

**After F3 (insert 30):**
```
      20
     /  \
    10   30
```
RR case triggered at 10. rotateLeft(10). Root becomes 20.

**After F5 (insert 50):**
```
      20
     /  \
    10   40
        /  \
       30   50
```
RR case at 30. rotateLeft(30). Root stays 20, right subtree: 40 with 30 left and 50 right.

**After F6 (insert 25):**
25 goes: 20→right(40)→left(30)→right. Inserting 25 at 30's right.

Walk up: 30(BF=-1), 40(BF=+2 — h(30)=1, h(50)=0). Left child(30) BF=-1 < 0 → **LR case**.
Step 1: rotateLeft(30) → 25 rises, 30 falls.
Step 2: rotateRight(40) → 25 rises to 40's position.

Final:
```
      20
     /  \
    10   25
        /  \
       ???  40
             \
             50
```
Wait, let me redo this carefully.

After F5: Tree is `[10, 20, 30, 40, 50]` → after rotations:
```
      30
     /  \
    20   40
   /       \
  10        50
```
Actually for sorted 10,20,30,40,50 with AVL the result is:
```
       30
      /  \
     20   40
    /       \
   10        50
```
Insert 25: 25 > 20, 25 < 30: goes to 20's right.
Tree:
```
       30
      /  \
     20   40
    /  \     \
   10   25    50
```
BFs: all valid (30: h(left=20)=2, h(right=40)=1... wait 40 has only right child 50 so h(40)=1, h(20)=1 since 20 has both 10 and 25)
BF(30) = 1-1 = 0. All valid! No rotation needed for insert 25 in this case.

Inorder: `10 20 25 30 40 50`
