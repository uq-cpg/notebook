// https://cses.fi/problemset/task/1651
#include <bits/stdc++.h>
using namespace std;

 // Floor of log_2(x); index of highest 1-bit
inline int log2Floor(int x) {
    return x ? 32 - 1 - __builtin_clz(x) : -1;
}

inline int leastPow2Geq(int x) {
    assert(x > 0);
    return 1 << log2Floor(2 * x - 1);
}

template <typename T, T empty = T()>
class SegmentTree {
    struct Node {
        T val;
        T lazy;
        bool is_lazy;
        int from, to;

        Node(T val_, T lazy_=empty, bool is_lazy_=false)
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

    T query(int from, int to, int node) {
        if (from <= t[node].from && t[node].to <= to) {
            return t[node].val;
        }
        if (to < t[node].from || t[node].to < from) {
            return empty;
        }
        pushDown(node);
        return merge(
            query(from, to, left(node)),
            query(from, to, right(node))
        );
    }

    void update(int from, int to, T d, int node) {
        if (from <= t[node].from && t[node].to <= to) {
            apply(t[node].val, d);
            apply(t[node].lazy, d);
            t[node].is_lazy = true;
            return;
        }
        if (to < t[node].from || t[node].to < from) {
            return;
        }
        pushDown(node);
        update(from, to, d, left(node));
        update(from, to, d, right(node));
        t[node].val = merge(t[left(node)].val, t[right(node)].val);
    }

public:
    SegmentTree(vector<T>& a, Merge merge_, Apply apply_)
        : n(a.size()), merge(merge_), apply(apply_) {
        n = leastPow2Geq(a.size());
        t.resize(n << 1, Node(empty));
        for (size_t i = 0; i < t.size() - n; i++) {
            if (i < a.size()) t[n + i].val = a[i];
            t[n + i].from = i;
            t[n + i].to = i;
        }
        for (int i = n - 1; i > 0; i--) {
            t[i].val = merge(t[left(i)].val, t[right(i)].val);
            t[i].from = t[left(i)].from;
            t[i].to = t[right(i)].to;
        }
    }

    T query(int from, int to) { return query(from, to, 1); }
    void update(int from, int to, T d) { return update(from, to, d, 1); }
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
