#include <vector>
#include <stack>

using namespace std;

/*
Critical path problem:

Given a directed acyclic graph with weighted edges, find the critical path.
The critical path is the path with the longest time.
The time of a path is the sum of the weights of the edges.
The time of a node is the max of the time of the previous node and the weight of the edge.
The earliest time of a node is the time of the node.
The latest time of a node is the min of the latest time of the next node and the weight of the edge.
The critical path is the path with the earliest time equal to the latest time.
*/

// Node is just type with data and weight, doesn't indicate it's an edge nor a node in graph
struct Node {
    int n;
    int weight;
    Node(int n, int weight) : n(n), weight(weight) {}
    Node() {}
};

// g is represented by an adjacency list
vector<int> critical_path(int n, vector<vector<Node>> g, int source, int destination) {
    // find the earliest time
    // earliest time is the max of the earliest time of the previous node and the weight of the edge
    vector<int> earliest(n, 0);
    stack<int> s;
    s.push(source);
    earliest[source] = 0;
    // dfs
    while(!s.empty()) {
        int t = s.top();
        s.pop();
        for(auto n: g[t]) {
            earliest[n.n] = max(earliest[n.n], earliest[t] + n.weight);
            s.push(n.n);
        }
    }

    // find the latest time
    // to do so, we must traverse the graph in reverse order
    vector<vector<Node>> reversed(n, vector<Node>());
    for(int i = 0; i < n; ++i) {
        for(auto n: g[i]) {
            reversed[n.n].push_back(Node(i, n.weight));
        }
    }
    constexpr int INF = 0x3f3f3f3f;
    vector<int> latest(n, INF);
    s.push(destination);
    latest[destination] = earliest[destination];
    while(!s.empty()) {
        int t = s.top();
        s.pop();
        for(auto n: reversed[t]) {
            latest[n.n] = min(latest[n.n], latest[t] - n.weight);
            s.push(n.n);
        }
    }

    // find the critical path
    vector<int> path;
    int t = source;
    path.push_back(t);
    while(t != destination) {
        for(auto n: g[t]) {
            if(earliest[n.n] == latest[n.n]) {
                path.push_back(n.n);
                t = n.n;
                break;
            }
        }
    }
    return path;
}

#ifdef DEBUG

#include <iostream>

int main() {
    // total vertices
    constexpr int n = 10;

    // graph, directed acyclic weighted
    vector<vector<Node>> g(n, vector<Node>());

    // add edges
    g[0].push_back(Node(1, 20));
    g[0].push_back(Node(2, 15));
    g[1].push_back(Node(3, 12));
    g[2].push_back(Node(3, 20));
    g[3].push_back(Node(4, 20));
    g[4].push_back(Node(5, 2));
    g[4].push_back(Node(6, 2));
    g[4].push_back(Node(7, 2));
    g[5].push_back(Node(8, 2));
    g[6].push_back(Node(8, 12));
    g[7].push_back(Node(8, 12));
    g[8].push_back(Node(9, 2));
    int source = 0;
    int destination = 9;

    for(auto it: critical_path(n, g, source, destination)) {
        cout << it << " ";
    }

    return 0;
}

#endif