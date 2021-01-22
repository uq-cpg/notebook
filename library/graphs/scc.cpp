#include <bits/stdc++.h>

using namespace std;

// https://judge.yosupo.jp/problem/scc
// Properties:
// - component graph is a DAG
// - traversed graph has the same sccs
// In this implementation, each component is sorted in topological order
struct Graph {
    int n;
    vector<vector<int>> adj;
    vector<vector<int>> adj_t;
    vector<int> mark;
    vector<int> order;
    vector<int> leader;
    vector<vector<int>> components;

    Graph(int n_) : n(n_), adj(n), adj_t(n),
        mark(n), leader(n) {}

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj_t[v].push_back(u);
    }

    void dfsForward(int u) {
        assert(mark[u] == 0);
        mark[u] = 1;

        for (int v : adj[u]) {
            if (mark[v] == 0) {
                dfsForward(v);
            }
        }

        order.push_back(u);
    }

    void dfsBackward(int u, int p) {
        assert(mark[u] == 1);
        mark[u] = 2;
        leader[u] = p;

        for (int v : adj_t[u]) {
            if (mark[v] == 1) {
                dfsBackward(v, p);
            }
        }

        components.back().push_back(u);
    }

    vector<vector<int>> scc() { // Kosaraju's algorithm
        fill(mark.begin(), mark.end(), 0);
        for (int u = 0; u < n; u++) {
            if (mark[u] == 0) {
                dfsForward(u);
            }
        }

        reverse(order.begin(), order.end());

        for (int u : order) {
            if (mark[u] == 1) {
                components.emplace_back();
                dfsBackward(u, u);
            }
        }

        return components;
    }
};

int main() {
    int n, m;
    cin >> n >> m;

    Graph g(n);

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        g.addEdge(u, v);
    }

    vector<vector<int>> components = g.scc();

    cout << components.size() << '\n';

    for (vector<int>& comp : components) {
        cout << comp.size() << ' ';
        for (int u : comp) {
            cout << u << ' ';
        }
        cout << '\n';
    }

    return 0;
}