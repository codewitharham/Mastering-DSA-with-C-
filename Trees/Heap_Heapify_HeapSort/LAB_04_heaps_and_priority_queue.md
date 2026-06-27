# LAB 04 — Heaps & Priority Queue
## Array Mapping → Heapify → Sort → STL → Graph Bridge

---

## PART A — Array-to-Tree Mapping Drills

The core skill: given an array, draw the tree. Given a tree, write the array.

**Formulas (memorize):**
```
Left child of i  = 2i + 1
Right child of i = 2i + 2
Parent of i      = (i - 1) / 2
Last non-leaf    = (size / 2) - 1
```

---

### Exercise A1 — Array to Tree

Draw the complete binary tree for each array:

**Array 1:** `[10, 8, 9, 6, 7, 5, 4]`
```
Your tree:

         ___[0]
        /       \
     ___[1]    ___[2]
     /   \     /   \
  ___[3] ___[4] ___[5] ___[6]
```

Is this a valid Max Heap? Check: every parent ≥ both children.

| Parent (idx) | Left child (idx) | Right child (idx) | Heap property? |
|---|---|---|---|
| 10 (0) | 8 (1) | 9 (2) | |
| 8 (1) | 6 (3) | 7 (4) | |
| 9 (2) | 5 (5) | 4 (6) | |

Valid Max Heap? ___

---

**Array 2:** `[3, 9, 2, 1, 4, 5, 8, 7, 6, 10]`

```
Your tree (10 nodes — last leaf at index 9):

              ___[0]
            /         \
         ___[1]       ___[2]
         /   \         /   \
      ___[3] ___[4] ___[5] ___[6]
      /   \  /
   ___[7] ___[8] ___[9]
```

Is this a valid Max Heap? Find ALL violations:

| Violation | Why |
|---|---|
| | |
| | |

Last non-leaf index = `(10/2) - 1 = ___`

---

### Exercise A2 — Tree to Array

Convert this tree to an array (fill indices in order):

```
              50
           /      \
          30        70
         /  \      /  \
        20   40   60   80
            /
           35
```

```
Index:  [0]  [1]  [2]  [3]  [4]  [5]  [6]  [7]
Value: [___][___][___][___][___][___][___][___]
```

Is this a valid Max Heap? ___ (find any violation)

---

### Exercise A3 — Index Formula Quiz

For a heap of size 10:

| Node | Index | Left child idx | Right child idx | Parent idx |
|---|---|---|---|---|
| Root | 0 | | | N/A |
| | 3 | | | |
| | 4 | | | |
| | 7 | | | |
| Last non-leaf | | | | |
| Last leaf | 9 | N/A | N/A | |

---

### Exercise A4 — Identify Leaves vs Non-Leaves

For array size = 7, mark each index as Leaf or Non-Leaf:

| Index | Value | Leaf or Non-Leaf? |
|---|---|---|
| 0 | | |
| 1 | | |
| 2 | | |
| 3 | | |
| 4 | | |
| 5 | | |
| 6 | | |

**Rule:** Index > `(size/2) - 1` → Leaf. Last non-leaf = `size/2 - 1 = ___`

---

## PART B — Heapify Manual Traces

---

### Exercise B1 — Single Heapify Call

Array: `[3, 10, 9, 6, 7, 5, 8]` (size=7)

This tree is:
```
         3[0]
        /    \
     10[1]   9[2]
     /  \   /  \
   6[3] 7[4] 5[5] 8[6]
```

Is the heap property violated at index 0? ___

Call `Heapify(arr, 7, 0)`:

| Step | Compare root idx ___ with children | Largest is at idx | Swap? | Array state |
|---|---|---|---|---|
| 1 | 3 vs 10 vs 9 | | | |
| 2 | (heapify continues at new index) | | | |
| 3 | | | | |

**Final array after Heapify(arr, 7, 0):** `[___, ___, ___, ___, ___, ___, ___]`

---

### Exercise B2 — Heapify Reaches a Leaf

Array: `[1, 9, 8, 7, 6, 5, 4]` (size=7)

Trace `Heapify(arr, 7, 0)`:

```
Step 1: Compare arr[0]=1 with arr[1]=9 and arr[2]=8
        Largest = ___ at index ___
        Swap arr[0] and arr[___]: [___, ___, ___, ___, ___, ___, ___]

Step 2: Now heapify at index ___
        Children at index ___ and ___
        Values: ___ and ___
        Largest = ___ at index ___
        Swap? ___

Step 3: Continue until no swap or leaf reached
```

After all steps, array = `[___, ___, ___, ___, ___, ___, ___]`

---

### Exercise B3 — Heapify Your Code

Using your `main.cpp` Heapify function, trace `Heapify(arr, 10, 0)` for:
`arr = [3, 9, 8, 7, 4, 5, 2, 1, 6, 10]`

(This is the state after BuildMaxHeap step for index=1 in your code)

```
At index 0: arr[0]=3, left=arr[1]=9, right=arr[2]=8
  largest = ___. Swap? ___. Array: [___,___,___,___,___,___,___,___,___,___]

At index ___: arr[___]=3, left=arr[___]=___, right=arr[___]=___
  largest = ___. Swap? ___. Array: [___,___,___,...]

Continue...
```

---

## PART C — BuildMaxHeap Full Trace

---

### Exercise C1 — Small Array

Build max heap from: `[4, 10, 3, 5, 1]` (size=5)

```
Starting array: [4, 10, 3, 5, 1]
Last non-leaf = (5/2)-1 = ___

Tree:
       4[0]
      /    \
   10[1]   3[2]
   /  \
 5[3] 1[4]
```

**Iteration at index=1:** (arr[1]=10, children: arr[3]=5, arr[4]=1)
```
Compare 10 with 5 and 1. Largest = ___ at index ___. Swap? ___
Array after: [___, ___, ___, ___, ___]
```

**Iteration at index=0:** (arr[0]=4, children: arr[1]=10, arr[2]=3)
```
Compare 4 with 10 and 3. Largest = ___ at index ___. Swap!
Array after swap: [___, ___, ___, ___, ___]
Heapify continues at index ___:
  Compare ___ with children. Swap? ___
  Array: [___, ___, ___, ___, ___]
```

**Final Max Heap:** `[___, ___, ___, ___, ___]`

**Verify:** Draw the tree and check all parent ≥ children:
```
Tree:
       ___[0]
      /    \
   ___[1]  ___[2]
   /  \
___[3] ___[4]
```

---

### Exercise C2 — Your Array

BuildMaxHeap trace for: `[3, 9, 2, 1, 4, 5, 8, 7, 6, 10]`

This is your exact `main.cpp` array. The theory document showed the full trace. Now do it yourself:

```
Size=10, last non-leaf = ___

Index 4 (arr[4]=4): children arr[9]=10, arr[10]=OOB
  Swap 4 and ___. Array: [3, 9, 2, 1, ___, 5, 8, 7, 6, ___]

Index 3 (arr[3]=1): children arr[7]=7, arr[8]=6
  Swap ___ and ___. Array: [...]

Index 2 (arr[2]=2): children arr[5]=5, arr[6]=8
  Swap ___ and ___. Array: [...]

Index 1 (arr[1]=9): children arr[3]=___, arr[4]=___
  Largest = ___. Swap? ___. Array: [...]
  Continue heapify at ___...

Index 0 (arr[0]=3): ...
  (trace all the way down)
```

**Final Max Heap:** `[___, ___, ___, ___, ___, ___, ___, ___, ___, ___]`

**Expected answer:** `[10, 9, 8, 7, 4, 5, 2, 1, 6, 3]`

---

## PART D — Implement MaxHeap Class From Scratch

Build a complete MaxHeap class using an array. No STL heap utilities.

```cpp
#include <vector>
#include <stdexcept>
using namespace std;

class MaxHeap {
private:
    vector<int> heap;

    int parent(int i) { return (i - 1) / 2; }
    int left(int i)   { return 2 * i + 1; }
    int right(int i)  { return 2 * i + 2; }

    // Sift UP: used after insert
    // New element at end might be larger than parent — swap up
    void siftUp(int i) {
        // YOUR CODE
        // While i > 0 AND heap[i] > heap[parent(i)]:
        //   swap heap[i] with heap[parent(i)]
        //   i = parent(i)
    }

    // Sift DOWN: used after extract and after buildHeap
    // Element at i might be smaller than children — swap down
    void siftDown(int i) {
        // YOUR CODE
        // Find largest among heap[i], heap[left(i)], heap[right(i)]
        // If largest != i: swap and recurse/loop
    }

public:
    // Insert new value
    void insert(int val) {
        // YOUR CODE
        // 1. Add to end of heap array
        // 2. Sift up to restore heap property
    }

    // Get maximum (peek, no removal)
    int getMax() {
        if (heap.empty()) throw runtime_error("Heap is empty");
        // YOUR CODE
    }

    // Remove and return maximum
    int extractMax() {
        if (heap.empty()) throw runtime_error("Heap is empty");
        // YOUR CODE
        // 1. Save root (max)
        // 2. Move last element to root
        // 3. Remove last element
        // 4. Sift down root to restore heap property
        // 5. Return saved max
    }

    // Build heap from unsorted vector — O(n)
    void buildFromArray(vector<int>& arr) {
        // YOUR CODE
        // 1. Copy arr into heap
        // 2. Start from last non-leaf: (size/2)-1
        // 3. Call siftDown on each index going toward 0
    }

    // HeapSort — sorts heap array in place (ascending order)
    // After this, heap property is destroyed
    vector<int> heapSort() {
        // YOUR CODE
        // Build max heap first
        // Repeatedly: swap root with last, reduce size, siftDown
    }

    bool empty() { return heap.empty(); }
    int size()   { return heap.size(); }

    void print() {
        for (int x : heap) cout << x << " ";
        cout << "\n";
    }
};
```

**Test harness:**

```cpp
int main() {
    MaxHeap h;

    // Test insert
    for (int v : {5, 3, 8, 1, 9, 2, 7}) {
        h.insert(v);
        cout << "After insert " << v << ": max = " << h.getMax() << "\n";
    }

    // Test extractMax
    cout << "Extracting in order: ";
    while (!h.empty()) {
        cout << h.extractMax() << " ";
    }
    cout << "\n";
    // Expected: 9 8 7 5 3 2 1

    // Test buildFromArray
    MaxHeap h2;
    vector<int> arr = {3, 9, 2, 1, 4, 5, 8, 7, 6, 10};
    h2.buildFromArray(arr);
    cout << "Built heap: "; h2.print();
    // Expected: 10 9 8 7 4 5 2 1 6 3

    return 0;
}
```

---

## PART E — HeapSort Implementation and Trace

---

### Exercise E1 — HeapSort Manual Trace

Starting array after BuildMaxHeap: `[10, 9, 8, 7, 4, 5, 2, 1, 6, 3]`

Trace each HeapSort iteration:

| Iteration | Swap root with | Array after swap | Heapify gives | Sorted section |
|---|---|---|---|---|
| 1 | arr[9]=3 | [3,9,8,7,4,5,2,1,6 \| 10] | [_,_,_,_,_,_,_,_,_ \| 10] | [10] |
| 2 | arr[8]=__ | | | [9,10] |
| 3 | | | | |
| 4 | | | | |
| 5 | | | | |
| 6 | | | | |
| 7 | | | | |
| 8 | | | | |
| 9 | | | | |

**Final sorted array:** `[___, ___, ___, ___, ___, ___, ___, ___, ___, ___]`

---

### Exercise E2 — Implement HeapSort Standalone

```cpp
void heapSort(vector<int>& arr) {
    int n = arr.size();

    // Phase 1: Build max heap
    for (int i = n/2 - 1; i >= 0; i--) {
        // YOUR CODE: call heapify on each non-leaf from bottom up
    }

    // Phase 2: Extract elements one by one
    for (int lastIdx = n - 1; lastIdx > 0; lastIdx--) {
        // YOUR CODE:
        // swap arr[0] with arr[lastIdx]
        // heapify the reduced heap (size = lastIdx)
    }
}

void heapify(vector<int>& arr, int size, int i) {
    // YOUR CODE (same as before, but on vector<int> directly)
}
```

---

## PART F — STL priority_queue Exercises

The STL `priority_queue` is your real tool for graph algorithms.

---

### Exercise F1 — Basic Max and Min Heap

```cpp
#include <queue>
using namespace std;

int main() {
    // MAX HEAP
    priority_queue<int> maxPQ;
    for (int v : {5, 2, 8, 1, 9, 3}) {
        maxPQ.push(v);
    }
    cout << "Max heap extract order: ";
    while (!maxPQ.empty()) {
        cout << maxPQ.top() << " ";
        maxPQ.pop();
    }
    cout << "\n";
    // Predict: ___________

    // MIN HEAP
    priority_queue<int, vector<int>, greater<int>> minPQ;
    for (int v : {5, 2, 8, 1, 9, 3}) {
        minPQ.push(v);
    }
    cout << "Min heap extract order: ";
    while (!minPQ.empty()) {
        cout << minPQ.top() << " ";
        minPQ.pop();
    }
    cout << "\n";
    // Predict: ___________
}
```

**Predictions:**
- Max heap: `___________`
- Min heap: `___________`

---

### Exercise F2 — Priority Queue with Pairs

Pairs are compared lexicographically (first element first, then second as tiebreaker).

```cpp
priority_queue<pair<int,int>> pq;  // max heap — largest pair on top
pq.push({3, 10});
pq.push({1, 20});
pq.push({3, 5});
pq.push({2, 15});

while (!pq.empty()) {
    auto [a, b] = pq.top(); pq.pop();
    cout << a << "," << b << "  ";
}
```

**Predict the output:** `___________`

**Now with min heap (greater<pair<int,int>>):** `___________`

---

### Exercise F3 — Kth Largest Element

Use a min-heap of size K to find the Kth largest element in a stream:

```cpp
int kthLargest(vector<int>& nums, int k) {
    // YOUR CODE
    // Use a min-heap of size k
    // If heap size < k: push
    // If new element > heap.top(): pop and push new
    // At the end, heap.top() = kth largest
}
```

Test: `nums = {3, 2, 1, 5, 6, 4}`, k=2 → expected: 5

---

### Exercise F4 — Sort by Custom Priority

You have tasks with priorities. Process highest priority first; tie-break by earlier arrival:

```cpp
struct Task {
    int priority;
    int arrivalTime;
    string name;

    // For max heap: higher priority = processed first
    // Tie-break: earlier arrival = processed first (smaller arrivalTime = higher priority)
    bool operator<(const Task& other) const {
        if (priority != other.priority) return priority < other.priority;
        return arrivalTime > other.arrivalTime;  // ← note: reversed for earlier first
    }
};

int main() {
    priority_queue<Task> pq;
    pq.push({3, 2, "TaskA"});
    pq.push({1, 1, "TaskB"});
    pq.push({3, 1, "TaskC"});
    pq.push({2, 3, "TaskD"});

    while (!pq.empty()) {
        Task t = pq.top(); pq.pop();
        cout << t.name << " (P=" << t.priority << ", T=" << t.arrivalTime << ")\n";
    }
    // Expected order: TaskC, TaskA, TaskD, TaskB
    // Why? ___________
}
```

---

### Exercise F5 — Merge K Sorted Arrays

Given K sorted arrays, merge them into one sorted array using a min-heap:

```cpp
vector<int> mergeKSorted(vector<vector<int>>& arrays) {
    // Min heap stores {value, arrayIndex, elementIndex}
    priority_queue<
        tuple<int,int,int>,
        vector<tuple<int,int,int>>,
        greater<tuple<int,int,int>>
    > minPQ;

    // YOUR CODE:
    // 1. Push first element of each array into heap
    // 2. While heap not empty:
    //    - Pop minimum {val, arrayIdx, elemIdx}
    //    - Add val to result
    //    - If arrays[arrayIdx] has more elements, push next one
}
```

---

## PART G — Bridge: Dijkstra's Algorithm Preview

You now have all the prerequisites. Here is the Dijkstra skeleton — fill in the blanks.

---

### Exercise G1 — Dijkstra with Priority Queue

```cpp
#include <vector>
#include <queue>
#include <climits>
using namespace std;

// adj[u] = list of {neighbor, weight}
vector<int> dijkstra(vector<vector<pair<int,int>>>& adj, int src) {
    int n = adj.size();
    vector<int> dist(n, ____);  // ← initialize all distances to?

    // Min heap: {distance, vertex}
    // Why min heap and not max heap?
    // Answer: ___________________________________________
    priority_queue<pair<int,int>,
                   vector<pair<int,int>>,
                   ____<pair<int,int>>> pq;  // ← greater or less?

    dist[src] = 0;
    pq.push({0, src});

    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();

        // Why do we skip if d > dist[u]?
        // Answer: ___________________________________________
        if (d > dist[u]) continue;

        for (auto [v, w] : adj[u]) {
            // Relaxation: if path through u is shorter than known path to v
            if (dist[u] + w < dist[v]) {
                dist[v] = ____;          // ← update distance
                pq.push({____, ____});   // ← push what into the queue?
            }
        }
    }
    return dist;
}
```

---

### Exercise G2 — Trace Dijkstra Manually

Graph:
```
     (4)
A --------- B
|           |
|(1)        |(2)
|           |
C --------- D
     (5)
```

Edges: A→B:4, A→C:1, C→B:2 (via C then B costs 1+2=3 < 4), C→D:5, B→D:1

Starting from A:

| Step | Pop | dist[A] | dist[B] | dist[C] | dist[D] | Queue after |
|---|---|---|---|---|---|---|
| Init | — | 0 | ∞ | ∞ | ∞ | [(0,A)] |
| 1 | (0,A) | 0 | 4 | 1 | ∞ | [(1,C),(4,B)] |
| 2 | (1,C) | 0 | ___ | 1 | ___ | |
| 3 | | | | | | |
| 4 | | | | | | |

**Final distances from A:**
- dist[A] = ___  dist[B] = ___  dist[C] = ___  dist[D] = ___

---

### Exercise G3 — Why Heap > Array for Dijkstra

| Implementation | Find min | Update distance | Total time |
|---|---|---|---|
| Simple array | O(V) | O(1) | O(V²) |
| Binary heap (priority_queue) | O(log V) | O(log V) | O((V+E) log V) |

**Which is better for:**
- Dense graph (E ≈ V²): `___________`
- Sparse graph (E ≈ V): `___________`

---

## PART H — Hard Challenges

---

### Challenge H1 — Median of a Data Stream

Insert numbers one at a time. After each insertion, find the median.

**Trick:** Use TWO heaps:
- Max heap for the lower half of numbers
- Min heap for the upper half of numbers
- Keep them balanced (sizes differ by at most 1)
- Median = top of max heap (if odd total) or average of both tops (if even)

```cpp
class MedianFinder {
    priority_queue<int> lowerHalf;                                   // max heap
    priority_queue<int, vector<int>, greater<int>> upperHalf;        // min heap

public:
    void addNum(int num) {
        // YOUR CODE
        // 1. Push to appropriate heap
        // 2. Rebalance if sizes differ by more than 1
    }

    double getMedian() {
        // YOUR CODE
    }
};
```

---

### Challenge H2 — Top K Frequent Elements

Given array of integers, return the k most frequent elements.

```cpp
vector<int> topKFrequent(vector<int>& nums, int k) {
    // Step 1: Count frequencies using unordered_map
    // Step 2: Use min-heap of size k keyed by frequency
    // Return k elements in the heap
}
```

---

## SOLUTIONS — Part A

### A1 Array 1 — Valid Max Heap ✅
```
10 > 8 and 10 > 9 ✅
8 > 6 and 8 > 7 ✅
9 > 5 and 9 > 4 ✅
```

### A1 Array 2 — INVALID
Last non-leaf = 4. Check all non-leaf parents:
- `arr[0]=3`: children 9,2 → 3 < 9 ❌ VIOLATION
- `arr[1]=9`: children 1,4 → 9 > all ✅
- `arr[2]=2`: children 5,8 → 2 < 5 and 2 < 8 ❌ VIOLATION
- `arr[3]=1`: children 7,6 → 1 < 7 and 1 < 6 ❌ VIOLATION
- `arr[4]=4`: child 10 → 4 < 10 ❌ VIOLATION

### A2 — Array from tree:
`[50, 30, 70, 20, 40, 60, 80, null, 35]`
With valid null: `arr = [50, 30, 70, 20, 40, 60, 80, -, -, 35]` where 35 is arr[9] (right of 40 at index 4).
Wait — 35 is LEFT child of 40: `arr[4]=40`, left = `2*4+1=9`. So arr[9]=35.

Violation: arr[4]=40, child arr[9]=35 → 40 > 35 ✅. No violation found; this is a valid max heap.

### A3 — Index Formula Answers:
| Node | Index | Left | Right | Parent |
|---|---|---|---|---|
| Root | 0 | 1 | 2 | N/A |
| | 3 | 7 | 8 | 1 |
| | 4 | 9 | 10 | 1 |
| | 7 | 15 | 16 | 3 |
| Last non-leaf | 4 | 9 | 10 | 1 |
| Last leaf | 9 | — | — | 4 |

### A4 — Leaves vs Non-Leaves (size=7, last non-leaf = 2):
Indices 0,1,2 = Non-Leaf. Indices 3,4,5,6 = Leaf.

---

## SOLUTIONS — Part D (MaxHeap class)

```cpp
void siftUp(int i) {
    while (i > 0 && heap[i] > heap[parent(i)]) {
        swap(heap[i], heap[parent(i)]);
        i = parent(i);
    }
}

void siftDown(int i) {
    int n = heap.size();
    while (true) {
        int largest = i;
        int l = left(i), r = right(i);
        if (l < n && heap[l] > heap[largest]) largest = l;
        if (r < n && heap[r] > heap[largest]) largest = r;
        if (largest == i) break;
        swap(heap[i], heap[largest]);
        i = largest;
    }
}

void insert(int val) {
    heap.push_back(val);
    siftUp(heap.size() - 1);
}

int getMax() { return heap[0]; }

int extractMax() {
    int maxVal = heap[0];
    heap[0] = heap.back();
    heap.pop_back();
    if (!heap.empty()) siftDown(0);
    return maxVal;
}

void buildFromArray(vector<int>& arr) {
    heap = arr;
    for (int i = heap.size()/2 - 1; i >= 0; i--) {
        siftDown(i);
    }
}
```

---

## SOLUTIONS — Part G

### G1 — Dijkstra blanks:
```cpp
vector<int> dist(n, INT_MAX);        // initialize to infinity
greater<pair<int,int>>               // min heap: smallest distance on top
dist[v] = dist[u] + w;              // update to new shorter distance
pq.push({dist[v], v});              // push {new distance, vertex}
```

**Why min heap:** We always want to process the vertex with the smallest known distance first (greedy: once settled, it's final).

**Why skip if d > dist[u]:** Stale entry — a shorter path to u was found after this entry was pushed. If we process it, we'd relax edges using an outdated (longer) distance. Skipping it is the "lazy deletion" optimization.

### G2 — Dijkstra trace:
| Step | Pop | dist[B] | dist[C] | dist[D] |
|---|---|---|---|---|
| 2 | (1,C) | min(4, 1+2)=3 | 1 | 1+5=6 |
| 3 | (3,B) | 3 | 1 | min(6, 3+1)=4 |
| 4 | (4,D) | 3 | 1 | 4 |

**Final:** dist[A]=0, dist[B]=3, dist[C]=1, dist[D]=4

### H1 — Median Finder:
```cpp
void addNum(int num) {
    if (lowerHalf.empty() || num <= lowerHalf.top()) {
        lowerHalf.push(num);
    } else {
        upperHalf.push(num);
    }
    // Rebalance
    if (lowerHalf.size() > upperHalf.size() + 1) {
        upperHalf.push(lowerHalf.top()); lowerHalf.pop();
    } else if (upperHalf.size() > lowerHalf.size()) {
        lowerHalf.push(upperHalf.top()); upperHalf.pop();
    }
}

double getMedian() {
    if (lowerHalf.size() > upperHalf.size()) return lowerHalf.top();
    return (lowerHalf.top() + upperHalf.top()) / 2.0;
}
```
