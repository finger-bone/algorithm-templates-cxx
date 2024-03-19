#include <queue>
#include <vector>
#include <functional>
#include <tuple>

using namespace std;

struct Node {
    int x;
    int y;
    Node(int x, int y) : x(x), y(y) {}
};

struct NodeWithDist {
    int x;
    int y;
    int dist;
    NodeWithDist(int x, int y, int dist) : x(x), y(y), dist(dist) {}
};

// . for no-block, # for block, t for target
vector<vector<Node>> a_star(
    vector<vector<char>> g, 
    size_t target_x,
    size_t target_y,
    size_t start_x,
    size_t start_y,
    function<int(int, int, int, int)> heuristic,
    vector<Node> directions
) {
    size_t n = g.size();
    size_t m = g[0].size();
    vector<vector<Node>> prev(n, vector<Node>(m, Node(-1, -1)));
    vector<vector<int>> dist(n, vector<int>(m, -1));
    auto cmp = [](NodeWithDist a, NodeWithDist b) {
        return a.dist > b.dist;
    };
    priority_queue<NodeWithDist, vector<NodeWithDist>, decltype(cmp)> pq(cmp);
    pq.push(NodeWithDist(start_x, start_y, heuristic(start_x, start_y, target_x, target_y)));
    dist[start_x][start_y] = 0;
    while (!pq.empty()) {
        NodeWithDist cur = pq.top();
        pq.pop();
        if (cur.x == target_x && cur.y == target_y) {
            break;
        }
        for(auto each: directions){
            int dx = each.x;
            int dy = each.y;
            if (dx == 0 && dy == 0) {
                continue;
            }
            int nx = cur.x + dx;
            int ny = cur.y + dy;
            if (nx < 0 || nx >= n || ny < 0 || ny >= m) {
                continue;
            }
            if (g[nx][ny] == '#') {
                continue;
            }
            if (dist[nx][ny] == -1 || dist[nx][ny] > dist[cur.x][cur.y] + 1) {
                dist[nx][ny] = dist[cur.x][cur.y] + 1;
                prev[nx][ny] = Node(cur.x, cur.y);
                pq.push(NodeWithDist(nx, ny, dist[nx][ny] + heuristic(nx, ny, target_x, target_y)));
            }
        }
    }
    return prev;
}

vector<Node> get_path(
    vector<vector<Node>> prev,
    size_t target_x,
    size_t target_y,
    size_t start_x,
    size_t start_y
) {
    vector<Node> path;
    size_t cur_x = target_x;
    size_t cur_y = target_y;
    while (cur_x != start_x || cur_y != start_y) {
        path.push_back(Node(cur_x, cur_y));
        Node next = prev[cur_x][cur_y];
        cur_x = next.x;
        cur_y = next.y;
    }
    path.push_back(Node(start_x, start_y));
    reverse(path.begin(), path.end());
    return path;
}


#ifdef DEBUG

#include <iostream>
#include <chrono>

void print_graph_and_path(
    vector<vector<char>> g,
    vector<Node> path
) {
    for (size_t i = 0; i < g.size(); ++i) {
        for (size_t j = 0; j < g[i].size(); ++j) {
            bool is_path = false;
            for (size_t k = 0; k < path.size(); ++k) {
                if (path[k].x == i && path[k].y == j) {
                    is_path = true;
                    break;
                }
            }
            if (is_path) {
                cout << "x";
            } else {
                cout << g[i][j];
            }
        }
        cout << endl;
    }
}

int main() {
    size_t n = 100;
    size_t m = 100;
    vector<vector<char>> g = vector<vector<char>>(
        n, vector<char>(m, '.')
    );
    // randomly generate some blocks
    for (size_t i = 0; i < 500; ++i) {
        size_t x = rand() % 100;
        size_t y = rand() % 100;
        g[x][y] = '#';
    }
    size_t target_x = 89;
    size_t target_y = 89;
    size_t start_x = 0;
    size_t start_y = 0;

    auto start_time = chrono::high_resolution_clock::now();
    auto prev = a_star(
        g, target_x, target_y, start_x, start_y,
        [](int x, int y, int tx, int ty) {
            return abs(x - tx) + abs(y - ty);
        },
        {
            Node(0, 1),
            Node(0, -1),
            Node(1, 0),
            Node(-1, 0)
        }
    );
    auto end_time = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end_time - start_time).count();

    cout << "Execution time: " << duration << "ms" << endl;

    auto path = get_path(prev, target_x, target_y, start_x, start_y);
    print_graph_and_path(g, path);
    return 0;
}
#endif