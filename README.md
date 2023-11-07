# Algorithm templates

## Misc

It is written

1. in c++23, but uses only up to c++17 features .
2. the coding styles would be as follows

    - `snake_case` for variables and functions
    - `PascalCase` for classes and structs
    - `UPPER_SNAKE_CASE` for macros and constants
    - `using namespace std;` is used in the global scope
    - maximize the usage of standard library
    - minimize the usage of pointer
    - only in linked list, tree and other data structures, in which, there has to be indefinite number of nodes, pointer is used so that struct can be validly defined. However, only use raw pointers instead of smart pointers.
    - minimize the usage of bitwise operators, unless it is necessary. We believe that compilers are smart enough to optimize the code.

## Contents

1. Segment Tree

    - [ZKW Segment Tree](./segment_tree/zkw_segment_tree.cxx)

2. Binary Indexed Tree

    - [Binary Indexed Tree](./binary_indexed_tree/binary_indexed_tree.cxx)

3. Shortest path

    - [Dijkstra](./graph/shortest_path/dijkstra.cxx)
    - [Bellman-Ford](./graph/shortest_path/bellman_ford.cxx)
    - [Floyd](./graph/shortest_path/floyd.cxx)

4. Minimal Spanning Tree

    - [Prim](./graph/minimal_spanning_tree/prim.cxx)
    - [Kruskal](./graph/minimal_spanning_tree/kruskal.cxx)

5. Other Tree-Related

    -[Trie](./tree/trie.cxx)
    -[Huffman](./tree/huffman.cxx)

6. Bisect

    - [Bisect](./bisect/bisect.cxx)
    - [Binary Search Tree](./bisect/binary_search_tree.cxx)
    - [Red-Black Tree](./bisect/rb_tree.cxx)

7. Sort

    - [Quick Sort](./sort/quick_sort.cxx)
    - [Merge Sort](./sort/merge_sort.cxx)
    - [Buckle Sort](./sort/buckle_sort.cxx)

8. Other Graph-Related

    - [Critical Path](./graph/critical_path.cxx)
    - [Disjoint Set](./graph/disjoint_set.cxx)
