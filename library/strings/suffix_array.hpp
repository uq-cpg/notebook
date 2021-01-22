#include <bits/stdc++.h>

using namespace std;

// sa[i] = the starting index of the ith suffix (starting at 0)
// sorted in lexicographic order
vector<int> suffix_array(const string& s_, int alpha=256) {
    string s = s_ + '\0';
    int n = s.size();
    vector<int> p(n);
    vector<int> cnt(max(alpha, n), 0);

    for (int i = 0; i < n; i++) cnt[s[i]]++;
    for (int i = 1; i < alpha; i++) cnt[i] += cnt[i - 1];
    for (int i = 0; i < n; i++) p[--cnt[s[i]]] = i;

    vector<int> g(n);
    g[p[0]] = 0;

    for (int i = 1; i < n; i++) {
        g[p[i]] = g[p[i - 1]] + (s[p[i]] != s[p[i - 1]]);
    }

    vector<int> pn(n);
    vector<int> gn(n);

    for (int len = 1; len < n; len <<= 1) {
        for (int i = 0; i < n; i++) {
            pn[i] = p[i] - len; // transfer the pos from second to pair
            if (pn[i] < 0) pn[i] += n; // cyclic
        }

        int num_groups = g[p[n - 1]] + 1;
        fill(cnt.begin(), cnt.begin() + num_groups, 0);

        // Radix sort
        for (int i = 0; i < n; i++) cnt[g[pn[i]]]++;
        for (int i = 1; i < num_groups; i++) cnt[i] += cnt[i - 1];
        for (int i = n - 1; i >= 0; i--) p[--cnt[g[pn[i]]]] = pn[i];
        gn[p[0]] = 0;

        for (int i = 1; i < n; i++) {
            pair<int, int> prev, cur;
            prev.first = g[p[i - 1]];
            cur.first = g[p[i]];
            prev.second = g[p[i - 1] + len - (p[i - 1] + len >= n ? n : 0)];
            cur.second = g[p[i] + len - (p[i] + len >= n ? n : 0)];
            gn[p[i]] = gn[p[i - 1]] + (cur != prev);
        }
        g.swap(gn);
    }
    p.erase(p.begin());
    return p;
}