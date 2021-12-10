/**
 * Problem: https://judge.yosupo.jp/problem/lca
 * LCA with binary lifting - sub: https://judge.yosupo.jp/submission/63568
**/

#include <bits/stdc++.h>
using namespace std;

struct Graph {
    int n;
    int log_h_max; // $\approx \max(\log_2(h)) \leq \log_2(n)$
    vector<vector<int>> adj;
    vector<int> depth;
    vector<vector<int>> p; // p[u][j]: $2^j$th ancestor/predecessor of $u$

    Graph(int n_) : n(n_), adj(n), depth(n, 0) {
        log_h_max = 1;
        while ((1 << log_h_max++) <= n);
        p.resize(n, vector<int>(log_h_max, -1));
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
    }

    void dfs(int u) {
        for (int v : adj[u]) {
            depth[v] = depth[u] + 1;
            p[v][0] = u;
            for (int j = 1; j < log_h_max; j++) {
                if (p[v][j - 1] == -1) break;
                p[v][j] = p[p[v][j - 1]][j - 1];
            }
            dfs(v);
        }
    }

    int lca(int u, int v) {
        if (depth[u] < depth[v]) {
            swap(u, v);
        }
        int d = depth[u] - depth[v];
        for (int j = log_h_max - 1; j > -1; j--) {
            if (d & (1 << j)) {
                u = p[u][j];
            }
        }
        if (u == v) return u;
        for (int j = log_h_max - 1; j > -1; j--) {
            if (p[u][j] != p[v][j]) {
                u = p[u][j];
                v = p[v][j];
            }
        }
        return p[u][0];
    }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, q; cin >> n >> q;
    Graph g(n);
    for (int i = 1; i < n; i++) {
        int p; cin >> p;
        g.addEdge(p, i);
    }
    g.dfs(0);
    for (int i = 0; i < q; i++) {
        int u, v; cin >> u >> v;
        cout << g.lca(u, v) << '\n';
    }
    return 0;
}
