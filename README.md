---
runme:
  id: 01HSA4D7PV9VR4DEXBXGVP748S
  version: v3
---

# Algorithm templates


## Misc

It was written

+ in c++23, but uses only up to c++17 features .
+ the coding styles would be as follows

   - `snake_case` for variables and functions
   - `PascalCase` for classes and structs
   - `UPPER_SNAKE_CASE` for macros and constants
   - `using namespace std;` is used in the global scope
   - maximize the usage of standard library
   - minimize the usage of pointer
   - only in linked list, tree and other data structures, in which, there has to be indefinite number of nodes, pointer is used so that struct can be validly defined. However, only use raw pointers instead of smart pointers.
   - minimize the usage of bitwise operators, unless it is necessary. We believe that compilers are smart enough to optimize the code.

## Contents

+ Segment Tree
   - [ZKW Segment Tree](./segment_tree/zkw_segment_tree.cxx)
   - [Segment Tree](./segment_tree/segment_tree.cxx)

+ Binary Indexed Tree
   - [Binary Indexed Tree](./binary_indexed_tree/binary_indexed_tree.cxx)

+ Shortest path
   - [Dijkstra](./shortest_path/dijkstra.cxx)
   - [Bellman-Ford](./shortest_path/bellman_ford.cxx)
   - [Floyd](./shortest_path/floyd.cxx)
   - [A Star](./shortest_path/a_star.cxx)

+ Minimal Spanning Tree
   - [Prim](./graph/minimal_spanning_tree/prim.cxx)
   - [Kruskal](./graph/minimal_spanning_tree/kruskal.cxx)

+ Other Tree-Related
   - [Heap](./tree/heap.cxx)
   - [Trie](./tree/trie.cxx)
   - [Huffman](./tree/huffman.cxx)

+ Bisect
   - [Bisect](./bisect/bisect.cxx)
   - [Binary Search Tree](./bisect/binary_search_tree.cxx)
   - [Red-Black Tree](./bisect/rb_tree.cxx)

+ Sort
   - [Quick Sort](./sort/quick_sort.cxx)
   - [Merge Sort](./sort/merge_sort.cxx)
   - [Bucket Sort](./sort/bucket_sort.cxx)

+ Other Graph-Related
   - [Critical Path](./graph/critical_path.cxx)
   - [Disjoint Set](./graph/disjoint_set.cxx)
   - [Max Flow](./graph/max_flow.cxx)

+ Geometry
   - [Closest Pair](./geometry/closest_pair.cxx)
   - [Convex Hull](./geometry/convex_hull.cxx)

+ Uncategorized
   - [KMP](./misc/kmp.cxx)
   - [K Largest By Divide and Decrease](./misc/k_largest.cxx)