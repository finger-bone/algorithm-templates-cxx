#include <vector>

using namespace std;

struct Edge {
    int from;
    int to;
    int weight;
    Edge(int from, int to, int weight) : from(from), to(to), weight(weight) {}
};

// bellman_ford applies to the graph that has no negative weight cycles
vector<int> bellman_ford(vector<Edge> es) {
    int n = es.size();
    constexpr int INF = 0x3f3f3f3f;
    vector<int> dist(n, INF);
    dist[0] = 0;

    // relax n - 1 times, if there were restrictions on the maximum length of the path, we could relax fewer times.
    for(int i = 0; i < n - 1; ++i) {
        // for each edge, relax
        for(Edge& e : es) {
            int u = e.from;
            int v = e.to;
            int w = e.weight;
            if(dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
            }
        }
    }

    return dist;
}