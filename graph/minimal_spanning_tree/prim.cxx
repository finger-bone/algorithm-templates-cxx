#include <vector>
#include <queue>

using namespace std;

// Node is just type with data and weight, doesn't indicate it's an edge nor a node in graph
struct Node {
    int n;
    int weight;
    Node(int n, int weight) : n(n), weight(weight) {}
    Node() {}
    bool operator<(const Node& rhs) const {
        return weight > rhs.weight;
    }
};

// g is represented by an adjacency list
vector<Node> prim(vector<vector<Node>> g) {
    int n = g.size();
    vector<Node> mst;
    vector<char> vis(n, false);
    priority_queue<Node> pq;
    
    // starts from zero
    pq.push(Node(0, 0));
    // similar to dijkstra
    // just replace the distance with the weight of adjacent edge
    while(!pq.empty()) {
        Node t = pq.top();
        pq.pop();
        if(vis[t.n]) continue;
        vis[t.n] = true;

        // if t is the edges that is in the pq and has the smallest weight
        // then it must be in the mst
        mst.push_back(t);

        // push all the adjacent edges of t into pq, if it's not visited
        // no need to worry about multiple pushes of the same edges, since we have vis
        for(auto n: g[t.n]) {
            if(!vis[n.n]) {
                pq.push(n);
            }
        }
    }
    return mst;
}

#ifdef DEBUG

#include <iostream>

int main() {
    vector<vector<Node>> g(5);
    g[0].push_back(Node(1, 1));
    g[0].push_back(Node(2, 2));
    g[0].push_back(Node(3, 3));
    g[1].push_back(Node(0, 1));
    g[1].push_back(Node(2, 2));
    g[2].push_back(Node(0, 2));
    g[2].push_back(Node(1, 2));
    g[2].push_back(Node(3, 1));
    g[2].push_back(Node(4, 1));
    g[3].push_back(Node(0, 3));
    g[3].push_back(Node(2, 1));
    g[4].push_back(Node(2, 1));

    vector<Node> mst = prim(g);
    for(auto n: mst) {
        cout << n.n << " " << n.weight << endl;
    }
    return 0;
}

#endif