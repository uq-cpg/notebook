#pragma once

#include <bits/stdc++.h>

using namespace std;

template <typename T>
using BinOp = function<T(T, T)>;

// Queries on immutable array
template <typename T>
class SparseTable {
public:
    int n;
    vector<vector<T>> mat;
    BinOp<T> f;

    SparseTable(const vector<T>& a,  const BinOp<T>& f_) : f(f_) {
        n = static_cast<int>(a.size());
        int max_log = 32 - __builtin_clz(n);
        mat.resize(max_log);
        mat[0] = a;
        for (int j = 1; j < max_log; j++) {
            mat[j].resize(n - (1 << j) + 1);
            for (int i = 0; i <= n - (1 << j); i++) {
                mat[j][i] = f(mat[j - 1][i], mat[j - 1][i + (1 << (j - 1))]);
            }
        }
    }

    T get(int from, int to) const {
        assert(0 <= from && from <= to && to <= n - 1);
        int lg = 32 - __builtin_clz(to - from + 1) - 1;
        return f(mat[lg][from], mat[lg][to - (1 << lg) + 1]);
    }
};