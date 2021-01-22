#pragma once

#include <bits/stdc++.h>

using namespace std;

#pragma once

// Bipartite matching. Vertices from both halves start from 0
// Time complexity: $O(\sqrt(|V|)|E|)$
struct HopcroftKarp {
    const int INF = (int) 1e9;
    int nu;
    int nv;
    vector<vector<int>> adj;
    vector<int> layer;
    vector<int> u_mate;
    vector<int> v_mate;

    HopcroftKarp(int nu, int nv) : nu(nu), nv(nv) {
        adj.resize(nu);
        layer.resize(nu);
        u_mate.resize(nu, -1);
        v_mate.resize(nv, -1);
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
    }

    bool bfs() {
        // Find all possible augmenting paths
        queue<int> q;

        for (int u = 0; u < nu; u++) {
            // Consider only unmatched edges
            if (u_mate[u] == -1) {
                layer[u] = 0;
                q.push(u);
            } else {
                layer[u] = INF;
            }
        }

        bool has_path = false;

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (int &v : adj[u]) {
                if (v_mate[v] == -1) {
                    has_path = true;
                } else if (layer[v_mate[v]] == INF) {
                    layer[v_mate[v]] = layer[u] + 1;
                    q.push(v_mate[v]);
                }
            }
        }

        return has_path;
    }

    bool dfs(int u) {
        if (layer[u] == INF) return false;

        for (int v : adj[u]) {
            if ((v_mate[v] == -1) ||
                (layer[v_mate[v]] == layer[u] + 1 && dfs(v_mate[v]))) {
                v_mate[v] = u;
                u_mate[u] = v;
                return true;
            }
        }

        return false;
    }

    vector<pair<int, int>> maxMatching() {
        int matching = 0;

        while (bfs()) { // there is at least 1 augmenting path
            for (int u = 0; u < nu; u++) {
                if (u_mate[u] == -1 && dfs(u)) {
                    ++matching;
                }
            }
        }

        vector<pair<int, int>> res;

        for (int u = 0; u < nu; u++) {
            if (u_mate[u] == -1) continue;
            res.emplace_back(u, u_mate[u]);
        }
        assert(res.size() == matching);
        return res;
    }
};