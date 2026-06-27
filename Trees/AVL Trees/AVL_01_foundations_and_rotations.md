# AVL Trees — Foundations & Rotations
## Why BSTs Break, How AVL Fixes Them, and Every Rotation Explained

---

## Table of Contents
1. [The Problem — How BSTs Degenerate](#1-the-problem--how-bsts-degenerate)
2. [The AVL Solution — The Balance Invariant](#2-the-avl-solution--the-balance-invariant)
3. [Balance Factor — The Core Metric](#3-balance-factor--the-core-metric)
4. [Height Tracking — Why Every Node Stores Its Height](#4-height-tracking--why-every-node-stores-its-height)
5. [The AVL Node Struct](#5-the-avl-node-struct)
6. [The 4 Imbalance Cases](#6-the-4-imbalance-cases)
7. [Right Rotation — Fixes LL Imbalance](#7-right-rotation--fixes-ll-imbalance)
8. [Left Rotation — Fixes RR Imbalance](#8-left-rotation--fixes-rr-imbalance)
9. [Left-Right Rotation — Fixes LR Imbalance](#9-left-right-rotation--fixes-lr-imbalance)
10. [Right-Left Rotation — Fixes RL Imbalance](#10-right-left-rotation--fixes-rl-imbalance)
11. [The Rotation Decision Tree](#11-the-rotation-decision-tree)
12. [C++ Rotation Implementations](#12-c-rotation-implementations)

---

## 1. The Problem — How BSTs Degenerate

You already know this from BST study. Let's make it concrete with numbers.

### Inserting sorted values: 10, 20, 30, 40, 50

```mermaid
graph TD
    subgraph "After insert 10, 20, 30, 40, 50 in sorted order"
        N10["10"] --> R1["null"]
        N10 --> N20["20"]
        N20 --> R2["null"]
        N20 --> N30["30"]
        N30 --> R3["null"]
        N30 --> N40["40"]
        N40 --> R4["null"]
        N40 --> N50["50"]
    end
```

```mermaid
graph LR
    STATS["Height = 4 = n-1\nSearch for 50 = 5 comparisons = O(n)\nThis is a linked list wearing a tree costume"]
```

| # nodes | Balanced height | Degenerate height | Penalty |
|---|---|---|---|
| 7 | 2 | 6 | 3× worse |
| 15 | 3 | 14 | 5× worse |
| 1023 | 9 | 1022 | 114× worse |
| 1,000,000 | 19 | 999,999 | 52,631× worse |

**The core problem:** BST insert gives you no guarantee about height. You get O(log n) only with random data. With sorted (or nearly sorted) data — which is extremely common in practice — you get O(n).

---

## 2. The AVL Solution — The Balance Invariant

In 1962, Soviet mathematicians **Adelson-Velsky and Landis** published the first self-balancing BST. Their insight: after every insert or delete, check if any node became too unbalanced. If yes, fix it immediately with a rotation. The tree is always kept balanced.

> **AVL Invariant:** For every node in the tree, the heights of its left and right subtrees differ by **at most 1**.

```mermaid
graph TD
    subgraph "NOT AVL — difference of 2 at node 10"
        BAD10["10\nBF = -2 ❌"]
        BAD20["20"]
        BAD30["30"]
        BAD10 --> NULLL["null\n(height -1)"]
        BAD10 --> BAD20
        BAD20 --> NULLL2["null"]
        BAD20 --> BAD30
    end

    subgraph "AVL — all differences ≤ 1"
        G20["20\nBF = 0 ✅"]
        G10["10\nBF = 0 ✅"]
        G30["30\nBF = 0 ✅"]
        G20 --> G10
        G20 --> G30
    end
```

### Why the invariant guarantees O(log n)

An AVL tree with n nodes has height at most **1.44 × log₂(n)** — proved by considering the minimum number of nodes in an AVL tree of height h.

Let N(h) = minimum nodes in AVL tree of height h:
- N(0) = 1 (single node)
- N(1) = 2
- N(h) = 1 + N(h-1) + N(h-2) ← Fibonacci-like recurrence

This grows exponentially in h, meaning h grows at most logarithmically in n. Therefore all operations remain **O(log n) in the worst case**.

---

## 3. Balance Factor — The Core Metric

The **Balance Factor (BF)** of a node is:

```
BF(node) = height(node->left) - height(node->right)
```

Where `height(nullptr) = -1` by convention.

```mermaid
graph TD
    subgraph "Computing Balance Factors"
        A["Node A\nLeft height = 2\nRight height = 1\nBF = 2-1 = +1 ✅"]
        B["Node B\nLeft height = 0\nRight height = 2\nBF = 0-2 = -2 ❌ IMBALANCED"]
        C["Node C\nLeft height = -1 (null)\nRight height = -1 (null)\nBF = 0 ✅ (leaf)"]
    end
```

| BF Value | Meaning | Status |
|---|---|---|
| `+2` or more | Left subtree too tall | ❌ **Left-heavy, rebalance!** |
| `+1` | Left slightly taller | ✅ Valid |
| `0` | Perfectly balanced | ✅ Valid |
| `-1` | Right slightly taller | ✅ Valid |
| `-2` or less | Right subtree too tall | ❌ **Right-heavy, rebalance!** |

**Key insight:** BF can only reach ±2 immediately after an insert or delete (because the tree was balanced before). A single rotation (or double rotation) always restores it.

---

## 4. Height Tracking — Why Every Node Stores Its Height

In a plain BST, nodes only store `data`, `left`, `right`. For AVL we add `height`.

**Why not compute height on the fly?** Computing height requires traversing the subtree — O(n) per call. If we need it at every node during insertion (which goes O(log n) nodes deep), that's O(n log n) just for height checks. Storing height makes each check O(1).

```mermaid
graph TD
    subgraph "Height values in a balanced tree"
        R["20\nheight=2"]
        L["10\nheight=1"]
        RI["30\nheight=0"]
        LL["5\nheight=0"]
        LR["15\nheight=0"]

        R --> L
        R --> RI
        L --> LL
        L --> LR
    end
```

### Height update rule:

```
height(node) = 1 + max(height(node->left), height(node->right))
```

**Critical:** You MUST update heights **bottom-up** — children's heights must be correct before you can compute a parent's height. This is why the update happens during the recursive unwind (after recursing into children, before returning).

---

## 5. The AVL Node Struct

```cpp
struct Node {
    int data;
    Node* left;
    Node* right;
    int height;      // ← the only addition over plain BST

    Node(int val) : data(val), left(nullptr), right(nullptr), height(0) {}
    //                                                         height=0 for a new leaf
};

// ─── Helper utilities ───────────────────────────────────────────────────────

// Safe height — handles nullptr (returns -1)
int getHeight(Node* node) {
    return (node == nullptr) ? -1 : node->height;
}

// Balance Factor = left height - right height
int getBalanceFactor(Node* node) {
    if (node == nullptr) return 0;
    return getHeight(node->left) - getHeight(node->right);
}

// Recompute height from children (call after any structural change)
void updateHeight(Node* node) {
    if (node == nullptr) return;
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
}
```

---

## 6. The 4 Imbalance Cases

After every insertion, walk back up the tree. If any node has `|BF| == 2`, you have an imbalance. The TYPE of imbalance determines which rotation to apply.

The imbalance type is named after **where the new node was inserted** relative to the imbalanced node:

```mermaid
graph TD
    IMB["Node Z has BF = ±2\n(imbalanced)"]
    IMB --> LEFT_HEAVY{"BF = +2\n(left heavy)"}
    IMB --> RIGHT_HEAVY{"BF = -2\n(right heavy)"}

    LEFT_HEAVY --> LL["Child Y is ALSO left-heavy or balanced\nBF(Y) >= 0\n→ LL Case\n→ Fix: SINGLE Right Rotation"]
    LEFT_HEAVY --> LR_CASE["Child Y is right-heavy\nBF(Y) < 0\n→ LR Case\n→ Fix: LEFT rotation on Y, then RIGHT on Z"]

    RIGHT_HEAVY --> RR["Child Y is ALSO right-heavy or balanced\nBF(Y) <= 0\n→ RR Case\n→ Fix: SINGLE Left Rotation"]
    RIGHT_HEAVY --> RL_CASE["Child Y is left-heavy\nBF(Y) > 0\n→ RL Case\n→ Fix: RIGHT rotation on Y, then LEFT on Z"]

    style LL fill:#27ae60,color:#fff
    style RR fill:#3498db,color:#fff
    style LR_CASE fill:#e67e22,color:#fff
    style RL_CASE fill:#9b59b6,color:#fff
```

### Visual Summary — All 4 Cases

```mermaid
graph LR
    subgraph "LL: New node in left-left"
        LL_Z["Z\nBF=+2"] --> LL_Y["Y\nBF=+1 or 0"] --> LL_X["X\n(new node here)"]
        LL_Z --> LL_T4["T4"]
        LL_Y --> LL_T3["T3"]
    end

    subgraph "RR: New node in right-right"
        RR_Z["Z\nBF=-2"] --> RR_T1["T1"]
        RR_Z --> RR_Y["Y\nBF=-1 or 0"]
        RR_Y --> RR_T2["T2"]
        RR_Y --> RR_X["X\n(new node here)"]
    end

    subgraph "LR: New node in left-right"
        LR_Z["Z\nBF=+2"] --> LR_Y["Y\nBF=-1"]
        LR_Z --> LR_T4["T4"]
        LR_Y --> LR_T1["T1"]
        LR_Y --> LR_X["X\n(new node here)"]
    end

    subgraph "RL: New node in right-left"
        RL_Z["Z\nBF=-2"] --> RL_T1["T1"]
        RL_Z --> RL_Y["Y\nBF=+1"]
        RL_Y --> RL_X["X\n(new node here)"]
        RL_Y --> RL_T4["T4"]
    end
```

---

## 7. Right Rotation — Fixes LL Imbalance

### Scenario

Inserting into the **left subtree of a left child** causes a node `Z` to become left-heavy (BF = +2). Its left child `Y` is left-heavy or balanced (BF ≥ 0).

```mermaid
graph TD
    subgraph "BEFORE Right Rotation — Z is imbalanced"
        Z["Z\nBF=+2"]
        Y["Y\nBF=+1"]
        T1["T1\n(new node caused\nimbalance here)"]
        T2["T2"]
        T3["T3"]
        Z --> Y
        Z --> T3
        Y --> T1
        Y --> T2
    end
```

### What Right Rotation Does

Y "rises" to take Z's position. Z "falls" to become Y's right child. Y's old right subtree (T2) becomes Z's new left subtree (the only pointer that needs careful handling).

```mermaid
graph TD
    subgraph "AFTER Right Rotation — Y is now root of this subtree"
        YNEW["Y\n(new root of subtree)"]
        T1NEW["T1"]
        ZNEW["Z\n(demoted — was root)"]
        T2NEW["T2\n(moved: was Y's right,\nnow Z's left)"]
        T3NEW["T3"]
        YNEW --> T1NEW
        YNEW --> ZNEW
        ZNEW --> T2NEW
        ZNEW --> T3NEW
    end
```

### Pointer Changes — Step by Step

```mermaid
sequenceDiagram
    participant Code
    participant Tree

    Note over Tree: Z->left = Y, Y->left = T1, Y->right = T2, Z->right = T3
    Code->>Tree: Node* newRoot = Z->left (= Y)
    Code->>Tree: Z->left = newRoot->right (= T2) ← T2 moves to Z's left
    Code->>Tree: newRoot->right = Z           ← Z becomes Y's right child
    Code->>Tree: updateHeight(Z)              ← Z's height changed (it lost T1, gained T2)
    Code->>Tree: updateHeight(newRoot)        ← Y's height changed (it gained Z subtree)
    Code->>Tree: return newRoot               ← Y is now the root of this subtree
```

### C++ Implementation

```cpp
Node* rotateRight(Node* Z) {
    Node* Y  = Z->left;        // Y will become the new root
    Node* T2 = Y->right;       // T2 will be relocated

    // Perform rotation
    Y->right = Z;              // Z falls down to become Y's right child
    Z->left  = T2;             // T2 moves: was Y's right, now Z's left

    // Update heights — Z first (it's now lower), then Y (it's now higher)
    updateHeight(Z);
    updateHeight(Y);

    return Y;   // Y is the new root of this subtree — caller must wire this in
}
```

### Why T2 Must Move to Z->left

T2 contains values **between Y and Z** (they're in Y's right subtree, so > Y; and in Z's left subtree, so < Z). After rotation, T2 still needs to satisfy both constraints. Z is now Y's right child — T2 as Z's left child is still > Y and still < Z. ✅

---

## 8. Left Rotation — Fixes RR Imbalance

### Scenario

Inserting into the **right subtree of a right child** — mirror image of LL. Node `Z` is right-heavy (BF = -2), its right child `Y` is right-heavy or balanced (BF ≤ 0).

```mermaid
graph TD
    subgraph "BEFORE Left Rotation"
        Z2["Z\nBF=-2"]
        T12["T1"]
        Y2["Y\nBF=-1"]
        T22["T2"]
        T32["T3\n(new node here)"]
        Z2 --> T12
        Z2 --> Y2
        Y2 --> T22
        Y2 --> T32
    end

    subgraph "AFTER Left Rotation"
        YNEW2["Y\n(new root)"]
        ZNEW2["Z\n(demoted)"]
        T1N["T1"]
        T2N["T2\n(moved: was Y's left,\nnow Z's right)"]
        T3N["T3"]
        YNEW2 --> ZNEW2
        YNEW2 --> T3N
        ZNEW2 --> T1N
        ZNEW2 --> T2N
    end
```

```cpp
Node* rotateLeft(Node* Z) {
    Node* Y  = Z->right;       // Y will become the new root
    Node* T2 = Y->left;        // T2 will be relocated

    // Perform rotation
    Y->left  = Z;              // Z falls down to become Y's left child
    Z->right = T2;             // T2 moves: was Y's left, now Z's right

    // Update heights — Z first (lower), then Y (higher)
    updateHeight(Z);
    updateHeight(Y);

    return Y;   // Y is the new root
}
```

**Why T2 moves to Z->right:** T2 has values between Z and Y (> Z, < Y). After rotation, Z is Y's left child — T2 as Z's right child is still > Z and still < Y. ✅

---

## 9. Left-Right Rotation — Fixes LR Imbalance

### Scenario

Node `Z` is left-heavy (BF = +2), but its left child `Y` is **right-heavy** (BF = -1). The new node is in Y's right subtree. A single right rotation on Z would NOT fix this — the tree would still be unbalanced after.

**This requires TWO rotations:** Left rotate Y first (converts it to LL case), then right rotate Z.

```mermaid
graph TD
    subgraph "INITIAL STATE — LR Imbalance"
        Z_LR["Z\nBF=+2"]
        Y_LR["Y\nBF=-1"]
        X_LR["X\n(new node,\ncaused imbalance)"]
        T1_LR["T1"]
        T2_LR["T2"]
        T3_LR["T3"]
        T4_LR["T4"]
        Z_LR --> Y_LR
        Z_LR --> T4_LR
        Y_LR --> T1_LR
        Y_LR --> X_LR
        X_LR --> T2_LR
        X_LR --> T3_LR
    end
```

**Step 1 — Left Rotate Y (about Y):**

```mermaid
graph TD
    subgraph "AFTER Step 1: Left Rotation on Y — now looks like LL"
        Z_LR2["Z\nBF=+2\n(still imbalanced)"]
        X_LR2["X\n(promoted by rotation)"]
        Y_LR2["Y\n(demoted)"]
        T1_LR2["T1"]
        T2_LR2["T2"]
        T3_LR2["T3"]
        T4_LR2["T4"]
        Z_LR2 --> X_LR2
        Z_LR2 --> T4_LR2
        X_LR2 --> Y_LR2
        X_LR2 --> T3_LR2
        Y_LR2 --> T1_LR2
        Y_LR2 --> T2_LR2
    end
```

**Step 2 — Right Rotate Z (about Z):**

```mermaid
graph TD
    subgraph "AFTER Step 2: Right Rotation on Z — BALANCED ✅"
        X_LR3["X\n(new root, BF=0)"]
        Y_LR3["Y\nBF=0"]
        Z_LR3["Z\nBF=0"]
        T1_LR3["T1"]
        T2_LR3["T2"]
        T3_LR3["T3"]
        T4_LR3["T4"]
        X_LR3 --> Y_LR3
        X_LR3 --> Z_LR3
        Y_LR3 --> T1_LR3
        Y_LR3 --> T2_LR3
        Z_LR3 --> T3_LR3
        Z_LR3 --> T4_LR3
    end
```

```cpp
Node* rotateLeftRight(Node* Z) {
    Z->left = rotateLeft(Z->left);   // Step 1: Left rotate Y
    return rotateRight(Z);           // Step 2: Right rotate Z
}
```

**Why one rotation fails:** After a single right rotation on Z with Y left-heavy, X (Y's right child) becomes Z's left child. X's own two subtrees are unbalanced. The double rotation ensures X ends up as the new root with Y and Z as its children — perfectly balanced.

---

## 10. Right-Left Rotation — Fixes RL Imbalance

### Scenario

Mirror of LR. Node `Z` is right-heavy (BF = -2), but right child `Y` is **left-heavy** (BF = +1). New node is in Y's left subtree.

**Two rotations:** Right rotate Y first, then left rotate Z.

```mermaid
graph TD
    subgraph "INITIAL STATE — RL Imbalance"
        Z_RL["Z\nBF=-2"]
        T1_RL["T1"]
        Y_RL["Y\nBF=+1"]
        X_RL["X\n(new node)"]
        T4_RL["T4"]
        T2_RL["T2"]
        T3_RL["T3"]
        Z_RL --> T1_RL
        Z_RL --> Y_RL
        Y_RL --> X_RL
        Y_RL --> T4_RL
        X_RL --> T2_RL
        X_RL --> T3_RL
    end
```

```mermaid
graph TD
    subgraph "AFTER Step 1: Right Rotation on Y"
        Z_RL2["Z\nBF=-2\n(still imbalanced)"]
        T1_RL2["T1"]
        X_RL2["X\n(promoted)"]
        Y_RL2["Y\n(demoted)"]
        T2_RL2["T2"]
        T3_RL2["T3"]
        T4_RL2["T4"]
        Z_RL2 --> T1_RL2
        Z_RL2 --> X_RL2
        X_RL2 --> T2_RL2
        X_RL2 --> Y_RL2
        Y_RL2 --> T3_RL2
        Y_RL2 --> T4_RL2
    end

    subgraph "AFTER Step 2: Left Rotation on Z — BALANCED ✅"
        X_RL3["X\n(new root, BF=0)"]
        Z_RL3["Z\nBF=0"]
        Y_RL3["Y\nBF=0"]
        T1_RL3["T1"]
        T2_RL3["T2"]
        T3_RL3["T3"]
        T4_RL3["T4"]
        X_RL3 --> Z_RL3
        X_RL3 --> Y_RL3
        Z_RL3 --> T1_RL3
        Z_RL3 --> T2_RL3
        Y_RL3 --> T3_RL3
        Y_RL3 --> T4_RL3
    end
```

```cpp
Node* rotateRightLeft(Node* Z) {
    Z->right = rotateRight(Z->right);  // Step 1: Right rotate Y
    return rotateLeft(Z);              // Step 2: Left rotate Z
}
```

---

## 11. The Rotation Decision Tree

After inserting at any node, check its balance factor on the way back up. This decision tree tells you exactly what to do:

```mermaid
graph TD
    CHECK{"Check BF of\ncurrent node"}
    CHECK -->|"BF == +2\n(left heavy)"| LEFT{"Check BF of\nleft child"}
    CHECK -->|"BF == -2\n(right heavy)"| RIGHT{"Check BF of\nright child"}
    CHECK -->|"-1 ≤ BF ≤ +1"| OK["No rotation needed ✅\nJust update height"]

    LEFT -->|"BF ≥ 0\n(left-heavy or balanced)"| LL_FIX["LL Case\n→ rotateRight(node)\nSINGLE rotation"]
    LEFT -->|"BF < 0\n(right-heavy)"| LR_FIX["LR Case\n→ rotateLeft(node->left)\n   rotateRight(node)\nDOUBLE rotation"]

    RIGHT -->|"BF ≤ 0\n(right-heavy or balanced)"| RR_FIX["RR Case\n→ rotateLeft(node)\nSINGLE rotation"]
    RIGHT -->|"BF > 0\n(left-heavy)"| RL_FIX["RL Case\n→ rotateRight(node->right)\n   rotateLeft(node)\nDOUBLE rotation"]

    style LL_FIX fill:#27ae60,color:#fff
    style RR_FIX fill:#3498db,color:#fff
    style LR_FIX fill:#e67e22,color:#fff
    style RL_FIX fill:#9b59b6,color:#fff
```

### The Memory Aid

```
BF = +2 → Left heavy → look at LEFT child's BF:
    Left child BF ≥ 0  →  LL  →  rotateRight
    Left child BF < 0  →  LR  →  rotateLeft(child) then rotateRight

BF = -2 → Right heavy → look at RIGHT child's BF:
    Right child BF ≤ 0  →  RR  →  rotateLeft
    Right child BF > 0  →  RL  →  rotateRight(child) then rotateLeft
```

---

## 12. C++ Rotation Implementations

Complete, copy-ready implementations with all edge cases handled:

```cpp
#include <iostream>
#include <algorithm>
using namespace std;

// ─── Node ────────────────────────────────────────────────────────────────────
struct Node {
    int data;
    Node* left;
    Node* right;
    int height;
    Node(int val) : data(val), left(nullptr), right(nullptr), height(0) {}
};

// ─── Height & Balance Utilities ──────────────────────────────────────────────
int getHeight(Node* n) {
    return n ? n->height : -1;
}

int getBalanceFactor(Node* n) {
    return n ? getHeight(n->left) - getHeight(n->right) : 0;
}

void updateHeight(Node* n) {
    if (n) n->height = 1 + max(getHeight(n->left), getHeight(n->right));
}

// ─── Right Rotation (fixes LL) ───────────────────────────────────────────────
//
//        Z                   Y
//       / \                 / \
//      Y   T3    →→→      T1   Z
//     / \                     / \
//   T1   T2                  T2  T3
//
Node* rotateRight(Node* Z) {
    Node* Y  = Z->left;
    Node* T2 = Y->right;

    Y->right = Z;
    Z->left  = T2;

    updateHeight(Z);    // Z first — it's now lower in the tree
    updateHeight(Y);    // Y second — it's now higher

    return Y;           // Y is the new subtree root
}

// ─── Left Rotation (fixes RR) ────────────────────────────────────────────────
//
//     Z                       Y
//    / \                     / \
//   T1   Y       →→→       Z   T3
//       / \               / \
//     T2   T3           T1   T2
//
Node* rotateLeft(Node* Z) {
    Node* Y  = Z->right;
    Node* T2 = Y->left;

    Y->left  = Z;
    Z->right = T2;

    updateHeight(Z);    // Z first — lower
    updateHeight(Y);    // Y second — higher

    return Y;
}

// ─── Left-Right Rotation (fixes LR) ─────────────────────────────────────────
//
//     Z            Z               X
//    /            /               / \
//   Y    →→→     X      →→→     Y   Z
//    \           / \
//     X         Y   (X's right)
//
Node* rotateLeftRight(Node* Z) {
    Z->left = rotateLeft(Z->left);   // Step 1: convert to LL
    return rotateRight(Z);           // Step 2: fix LL
}

// ─── Right-Left Rotation (fixes RL) ─────────────────────────────────────────
//
//   Z              Z               X
//    \              \             / \
//     Y   →→→        X   →→→   Z   Y
//    /                \
//   X            (X's left)  Y
//
Node* rotateRightLeft(Node* Z) {
    Z->right = rotateRight(Z->right);  // Step 1: convert to RR
    return rotateLeft(Z);              // Step 2: fix RR
}

// ─── Rebalance — applies the right rotation based on BF ──────────────────────
Node* rebalance(Node* node) {
    updateHeight(node);                  // always update height first

    int bf = getBalanceFactor(node);

    // LEFT HEAVY (BF == +2)
    if (bf == 2) {
        if (getBalanceFactor(node->left) >= 0) {
            return rotateRight(node);    // LL case
        } else {
            return rotateLeftRight(node); // LR case
        }
    }

    // RIGHT HEAVY (BF == -2)
    if (bf == -2) {
        if (getBalanceFactor(node->right) <= 0) {
            return rotateLeft(node);     // RR case
        } else {
            return rotateRightLeft(node); // RL case
        }
    }

    return node;   // balanced — no rotation needed
}
```

---

## Summary — The Complete Mental Model

```mermaid
graph LR
    subgraph "AVL = BST + Balance Enforcement"
        A["BST Property\n(still holds! AVL is still a BST)"]
        B["Height stored per node\n(enables O(1) BF check)"]
        C["Balance Factor = h(left) - h(right)\nMust be -1, 0, or +1"]
        D["After every insert/delete:\ncheck BF on way back up,\napply rotation if |BF| == 2"]
        E["Result: height ≤ 1.44 log n\nAll ops O(log n) GUARANTEED"]
    end
```

```
ROTATION CHEAT SHEET:
  BF = +2, left child BF ≥ 0   →  LL  →  rotateRight(Z)
  BF = +2, left child BF < 0   →  LR  →  rotateLeft(Z->left), rotateRight(Z)
  BF = -2, right child BF ≤ 0  →  RR  →  rotateLeft(Z)
  BF = -2, right child BF > 0  →  RL  →  rotateRight(Z->right), rotateLeft(Z)

POINTER CHANGES IN EACH ROTATION:
  rotateRight(Z): Y=Z->left, Y->right=Z, Z->left=T2 (T2=old Y->right)
  rotateLeft(Z):  Y=Z->right, Y->left=Z, Z->right=T2 (T2=old Y->left)

HEIGHT UPDATE ORDER:
  ALWAYS update the LOWER node (Z) before the HIGHER node (Y)
  Z's height changes (lost/gained subtrees) → must be recalculated first
```
