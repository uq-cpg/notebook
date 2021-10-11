// https://cses.fi/problemset/task/1651
#include <bits/stdc++.h>
using namespace std;
 
template <typename T, T empty = T()>
class SegmentTree {
    struct Node {
        T val;
        T lazy;
        bool is_lazy;
 
        Node(T val_, T lazy_ = empty, bool is_lazy_ = false)
            : val(val_), lazy(lazy_), is_lazy(is_lazy_) {}
    };
 
    using Merge = function<T(const T&, const T&)>;
    using Apply = function<void(T&, const T&)>;
 
    int n;
    vector<Node> t;
    Merge merge;
    Apply apply;
 
    inline int left(int i) { return i << 1; }
    inline int right(int i) { return (i << 1) + 1; }
 
    void build(vector<T>& a) {
        n = 1;
        while (n < (int)a.size()) n <<= 1;
        t.resize(n << 1, Node(empty));
        for (int i = 0; i < (int)a.size(); i++) {
            t[n + i].val = a[i];
        }
        for (int i = n - 1; i > 0; i--) {
            t[i].val = merge(t[left(i)].val, t[right(i)].val);
        }
    }
 
    void pushDown(int node) {
        if (t[node].is_lazy) {
            apply(t[left(node)].val, t[node].lazy);
            apply(t[left(node)].lazy, t[node].lazy);
            apply(t[right(node)].val, t[node].lazy);
            apply(t[right(node)].lazy, t[node].lazy);
            t[node].lazy = empty;
            t[node].is_lazy = false;
            t[left(node)].is_lazy = t[right(node)].is_lazy = true;
        }
    }
 
    T query(int from, int to, int node, int node_from, int node_to) {
        if (from <= node_from && node_to <= to) {
            return t[node].val;
        }
        if (to < node_from || node_to < from) {
            return 0;
        }
        pushDown(node);
        int mid = (node_from + node_to) / 2;
        return query(from, to, left(node), node_from, mid) +
               query(from, to, right(node), mid + 1, node_to);
    }
 
    void update(int from, int to, T d, int node, int node_from, int node_to) {
        if (from <= node_from && node_to <= to) {
            apply(t[node].val, d);
            apply(t[node].lazy, d);
            t[node].is_lazy = true;
            return;
        }
        if (to < node_from || node_to < from) {
            return;
        }
        pushDown(node);
        int mid = (node_from + node_to) / 2;
        update(from, to, d, left(node), node_from, mid);
        update(from, to, d, right(node), mid + 1, node_to);
        t[node].val = merge(t[left(node)].val, t[right(node)].val);
    }
 
public:
    SegmentTree(vector<T>& a, Merge merge_, Apply apply_)
        : n(a.size()), merge(merge_), apply(apply_) {
        n = 1;
        while (n < (int)a.size()) n <<= 1;
        t.resize(n << 1, Node(empty));
        build(a);
    }
 
    T query(int from, int to) { return query(from, to, 1, 0, n - 1); }
 
    void update(int from, int to, T d) {
        return update(from, to, d, 1, 0, n - 1);
    }
};
 
int main() {
    int n, q; cin >> n >> q;
    vector<int64_t> x(n);
    for (int i = 0; i < n; i++) cin >> x[i];
    auto apply = [](int64_t& val, const int64_t& d) {
        return val += d;
    };
    auto merge = [](const int64_t& a, const int64_t& b) {
        return a + b;
    };
    SegmentTree<int64_t> st(x, merge, apply);
    for (int i = 0; i < q; i++) {
        int t; cin >> t;
        if (t == 1) {
            int a, b, u; cin >> a >> b >> u; a--; b--;
            st.update(a, b, u);
        } else {
            int k; cin >> k; k--;
            cout << st.query(k, k) << '\n';
        }
    }
    return 0;
}
