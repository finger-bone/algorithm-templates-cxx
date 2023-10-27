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
    - only in linked list, tree and other data structures, in which, there has to be indefinite number of nodes, pointer is used so that struct can be validly defined.
    - minimize the usage of bitwise operators, unless it is necessary. We believe that compilers are smart enough to optimize the code.

## Contents

1. Segment Tree

    - [zkw segment tree](./segment_tree/zkw_segment_tree.cxx)

2. Tree Like Array

    - [binary indexed tree](./tree_array/tree_array.cxx)

3. Graph-Related

    - [Critical Path](./graph/critical_path.cxx)
    - Shortest path

        - [Dijkstra](./graph/shortest_path/dijkstra.cxx)
        - [Bellman-Ford](./graph/shortest_path/bellman_ford.cxx)
        - [Floyd](./graph/shortest_path/floyd.cxx)
    - Minimal Spanning Tree

        - [Prim](./graph/minimal_spanning_tree/prim.cxx)
        - [Kruskal](./graph/minimal_spanning_tree/kruskal.cxx)

4. Bisect

    - [Bisect](./bisect/bisect.cxx)
