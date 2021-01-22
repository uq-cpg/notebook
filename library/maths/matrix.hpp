#pragma once

#include <bits/stdc++.h>

using namespace std;

template <typename T>
struct vec2d : public vector<vector<T>> {
vec2d(int n=0, int m=0, T t=T())
        : vector<vector<T>>(n, vector<T>(m, t)) {}
};

template <typename T>
struct Matrix : vec2d<T> {
    int n;

    Matrix(int n_, T t=T()) : vec2d<T>(n_, n_, t), n(n_) {}

    Matrix operator+(const Matrix& o) const {
        assert(n == o.n);
        const Matrix& a = *this;
        Matrix res(n);

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                res[i][j] = a[i][j] + o[i][j];
            }
        }

        return res;
    }

    Matrix operator-(const Matrix& o) const {
        assert(n == o.n);
        const Matrix& a = *this;
        Matrix res(n);

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                res[i][j] = a[i][j] - o[i][j];
            }
        }

        return res;
    }

    Matrix operator*(const Matrix& o) const {
        assert(n == o.n);
        const Matrix& a = *this;
        Matrix res(n, 0);

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                for (int k = 0; k < n; k++) {
                    res[i][j] = res[i][j] + a[i][k] * o[k][j];
                }
            }
        }
        return res;
    }

    void identity() {
        Matrix& a = *this;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i == j) a[i][j] = 1;
                else a[i][j] = 0;
            }
        }
    }

    // Gauss method. Complexity: $O(n^3)$
    friend T determinant(const Matrix& mat) {
        int n = mat.n;
        Matrix a(n);

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                a[i][j] = mat[i][j];
            }
        }

        const double EPS = 1E-9;
        T det = 1;

        for (int i = 0; i < n; ++i) {
            int k = i;

            for (int j= i + 1; j < n; j++) {
                if (abs(a[j][i]) > abs(a[k][i])) {
                    k = j;
                }
            }

            if (abs(a[k][i]) < EPS) {
                det = 0;
                break;
            }

            swap(a[i], a[k]);

            if (i != k) det = -det;

            det = det * a[i][i];

            for (int j = i + 1; j < n; j++) {
                a[i][j] = a[i][j] / a[i][i];
            }

            for (int j = 0; j < n; j++) {
                if (j != i && abs(a[j][i]) > EPS) {
                    for (int k = i + 1; k < n; k++) {
                        a[j][k] = a[j][k] - a[i][k] * a[j][i];
                    }
                }
            }
        }

        return det;
    }
};
