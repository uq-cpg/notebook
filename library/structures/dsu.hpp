#pragma once

#include <bits/stdc++.h>

using namespace std;

struct DSU {
    int n;
    vector<int> p;
    vector<int> d;

    DSU(int n_): n(n_), p(n), d(n, 0) {
        for (int i = 0; i < n; i++) p[i] = i;
    }

    int get(int u) {
        while (u != p[u]) u = p[u]; return u;
    }

    bool merge(int u, int v) {
        u = get(u);
        v = get(v);
        if (u == v) return false;
        if (d[u] < d[v]) {
            p[u] = v;
        } else if (d[u] > d[v]) {
            p[v] = u;
        } else {
            p[u] = v;
            d[v]++;
        }
        return true;
    }
};
