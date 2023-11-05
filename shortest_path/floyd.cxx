#include <vector>

using namespace std;

constexpr int INF = 0x3f3f3f3f;

// floyd applies to the graph that has no negative weight cycles
// g is represented as an adjacency matrix
vector<vector<int>> floyd(vector<vector<int>> g) {
    int n = g.size();
    vector<vector<int>> dist(n, vector<int>(n, INF));

    // initialize the distance matrix
    for(int i = 0; i < n; ++i) {
        dist[i][i] = 0;
        for(int j = 0; j < n; ++j) {
            if(g[i][j] != INF) {
                dist[i][j] = g[i][j];
            }
        }
    }

    // for each round, choose a node as the intermediate node
    for(int k = 0; k < n; ++k) {
        // for each pair of nodes, check if the distance can be updated
        for(int i = 0; i < n; ++i) {
            // if the distance from i to k is INF, then the distance from i to j must be INF
            // so we can skip this case
            if(dist[i][k] == INF) continue;
            for(int j = 0; j < n; ++j) {
                // if the distance from k to j is INF, then the distance from i to j must be INF
                // so we can skip this case
                if(dist[k][j] == INF) continue;
                // relax
                if(dist[i][j] > dist[i][k] + dist[k][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    return dist;
}

#ifdef DEBUG

#include <iostream>

int main() {
    vector<vector<int>> g = {
        {0, 1, 12, INF},
        {INF, 0, 9, 3},
        {INF, INF, 0, INF},
        {INF, INF, 4, 0}
    };

    vector<vector<int>> dist = floyd(g);

    for(int i = 0; i < dist.size(); ++i) {
        for(int j = 0; j < dist[i].size(); ++j) {
            cout << dist[i][j] << ' ';
        }
        cout << endl;
    }

    return 0;
}

#endif