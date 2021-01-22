#pragma once

#include <bits/stdc++.h>

using namespace std;

template <typename T>
using BinOp = function<T(T, T)>;

template <typename T>
struct SegmentTree {
    struct Node {
        int from;
        int to;
        T val;
        T lazy;
        bool is_lazy;
    };

    int n;
    vector<Node> t;
    T dlazy;
    BinOp<T> merge;
    T dquery;

    SegmentTree(vector<int>& a, T dlazy_, BinOp<T> merge, T dquery_) :
        n(a.size()), t(n * 4), dlazy(dlazy_), merge(merge), dquery(dquery_) {
        build(a, 0, 0, n - 1);
    }

    virtual void apply(int u, T delta) = 0;
    virtual void pushDown(int u) = 0;

    inline int left(int u)  { return 2 * u + 1; }
    inline int right(int u) { return 2 * u + 2; }

    void build(vector<int>& a, int u, int from, int to) {
        if (from == to) {
            t[u] = Node({from, to, a[from], dlazy, false});
            return;
        }

        int l = left(u);
        int r = right(u);
        int mid = (from + to) / 2;
        build(a, l, from, mid);
        build(a, r, mid + 1, to);
        T val = merge(t[l].val, t[r].val);
        t[u] = Node({from, to, val, dlazy, false});
    }

    T query(int from, int to, int u=0) {
        if (from <= t[u].from && t[u].to <= to) return t[u].val;
        if (to < t[u].from || t[u].to < from) return dquery;
        pushDown(u);
        return merge(query(from, to, left(u)),
                     query(from, to, right(u)));
    }

    void update(int from, int to, T delta, int u=0) {
        if (from > to) return;

        if (from == t[u].from && to == t[u].to) {
            apply(u, delta);
            return;
        }

        pushDown(u);
        int l = left(u);
        int r = right(u);
        int mid = (t[u].from + t[u].to) / 2;
        update(from, min(to, mid), delta, l);
        update(max(from, mid + 1), to, delta, r);
        t[u].val = merge(t[l].val, t[r].val);
    }
};

template <typename T>
struct SegmentAssignUpdate : public SegmentTree<T> {
    SegmentAssignUpdate(vector<int>& a, BinOp<T> merge_, int dquery_) :
        SegmentTree<T>(a, 0, merge_, dquery_) {}

    virtual void apply(int u, T delta) {
        auto& t = this->t;
        t[u].val = delta;
        t[u].is_lazy = true;
    }

    virtual void pushDown(int u) {
        auto& t = this->t;
        int l = this->left(u);
        int r = this->right(u);
        if (t[u].is_lazy) {
            t[l].val = t[r].val = t[u].val;
            t[l].is_lazy = t[r].is_lazy = true;
            t[u].is_lazy = false;
        }
    }
};

template <typename T>
struct SegmentAddUpdate : SegmentTree<T> {
    SegmentAddUpdate(vector<int>& a, int dlazy_, BinOp<T> merge_, int dquery_) :
            SegmentTree<T>(a, dlazy_, merge_, dquery_) {}

    virtual void apply(int u, T delta) {
        auto& t = this->t;
        t[u].val += delta;
        t[u].lazy += delta;
    }

    virtual void pushDown(int u) {
        auto& t = this->t;
        int l = this->left(u);
        int r = this->right(u);
        t[l].val += t[u].lazy;
        t[l].lazy += t[u].lazy;
        t[r].val += t[u].lazy;
        t[r].lazy += t[u].lazy;
        t[u].lazy = 0;
    }
};