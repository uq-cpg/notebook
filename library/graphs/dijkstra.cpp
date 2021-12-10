#include <bits/stdc++.h>

using namespace std;

struct Edge {
    int u, v, w;
    Edge(int u_, int v_, int w_) : u(u_), v(v_), w(w_) {}
};

struct Node {
    int u;
    int64_t d;
    Node(int u_, int64_t d_) : u(u_), d(d_) {}
    bool operator<(const Node& o) const {
        return d > o.d; // min-heap
    }
};

struct Graph {
    const int64_t inf = 1e18;
    int n;
    vector<vector<Edge>> adj;
    vector<int64_t> dist;
    vector<const Edge*> trace; // trace[u]: last edge to get to u from s

    Graph(int n_) : n(n_), adj(n), dist(n, inf), trace(n, NULL) {}

    void addEdge(int u, int v, int w) {
        adj[u].emplace_back(u, v, w);
    }

    int64_t dijkstra(int s, int t) {
        priority_queue<Node> pq;
        pq.emplace(s, 0);
        dist[s] = 0;
        while (!pq.empty()) {
            Node cur = pq.top(); pq.pop();
            int u = cur.u;
            int64_t d = cur.d;
            if (u == t) return dist[t];
            if (d > dist[u]) continue;
            for (const Edge& e : adj[u]) {
                int v = e.v;
                int w = e.w;
                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    trace[v] = &e;
                    pq.emplace(v, dist[v]);
                }
            }
        }
        return inf;
    }

    vector<Edge> getShortestPath(int s, int t) {
        assert(dist[t] != inf);
        vector<Edge> path;
        int v = t;
        while (v != s) {
            const Edge e = *trace[v];
            path.push_back(e);
            v = e.u;
        }
        reverse(path.begin(), path.end());
        return path;
    }
};


int main() {
    int n, m, s, t; cin >> n >> m >> s >> t;
    Graph g(n);
    for (int i = 0; i < m; i++) {
        int u, v, w; cin >> u >> v >> w;
        g.addEdge(u, v, w);
    }
    int64_t dist = g.dijkstra(s, t);
    if (dist != g.inf) {
        vector<Edge> path = g.getShortestPath(s, t);
        cout << dist << ' ' << path.size() << '\n';
        for (Edge e : path) cout << e.u << ' ' << e.v << '\n';
    } else {
        cout << "-1\n";
    }
    return 0;
}
