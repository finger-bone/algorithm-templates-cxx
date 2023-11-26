#include <vector>
#include <queue>

using namespace std;

// Node is just type with data and weight, doesn't indicate it's an edge nor a node in graph
struct Node {
    int n;
    int weight;
    Node(int n, int weight) : n(n), weight(weight) {}
    bool operator<(const Node& other) const {
        return weight > other.weight;
    }
};

// dijkstra applies to the graph that has no negative weight edges
// g is represented as an adjacency list
vector<int> dijkstra(vector<vector<Node>> g, int source) {
    int n = g.size();
    priority_queue<Node> pq;
    constexpr int INF = 0x3f3f3f3f;
    vector<int> dist(n, INF);
    vector<char> vis(g.size(), false);
    pq.push(Node(source, 0));
    dist[source] = 0;
    
    // for each round, choose the node that is the nearest to the last node
    while(!pq.empty()) {
        Node node = pq.top();
        pq.pop();
        int u = node.n;

        // this also filters out previously added element
        // since the distance to the last node is certainly smaller than that of the previous ones
        // so if a node presents in pq twice or more, the latest one must be the shortest, that is, the one at the front.
        if(vis[u]) continue;
        vis[u] = true;

        // update the distance to the last node
        for(Node& next : g[u]) {
            int v = next.n;
            int w = next.weight;
            // relax
            if(dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                // if dist[v] is not updated, it must have been added to pq before
                pq.push(Node(v, dist[v]));
            }
        }
    }

    return dist;
}

#ifdef DEBUG

int main() {
    vector<vector<Node>> g = {
        {Node(1, 1), Node(2, 12)},
        {Node(2, 9), Node(3, 3)},
        {Node(4, 5)},
        {Node(2, 4), Node(4, 13), Node(5, 15)},
        {Node(5, 4)},
        {Node(6, 13)},
        {Node(4, 3), Node(5, 5)}
    };
    vector<int> dist = dijkstra(g, 0);
    for(int i = 0; i < dist.size(); i++) {
        printf("%d: %d\n", i, dist[i]);
    }
    return 0;
}

#endif