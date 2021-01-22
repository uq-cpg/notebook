#include <bits/stdc++.h>

using namespace std;

struct Query {
    int from, to, index;
    Query(int from, int to, int index) :
        from(from), to(to), index(index) {}
};

struct MoSolver {
    vector<int> a;
    vector<Query> queries;
    int n;
    int k;
    int total;
    unordered_map<int, int> freq;

    MoSolver(vector<int>& a, vector<Query>& queries, int n, int k)
        : a(a), queries(queries), n(n), k(k), total(0) {}

    void add(int index) {
        int x = a[index];
        if (freq.find(x) == freq.end()) freq[x] = 0;
        int y = k - x;

        if (freq.find(y) != freq.end()) {
            if (y != x) {
                if (freq[y] > freq[x]) {
                    total++;
                }
            } else {
                if (freq[x] % 2 == 1) {
                    total++;
                }
            }
        }

        freq[x]++;
    }

    void remove(int index) {
        int x = a[index];
        int y = k - x;

        if (freq.find(y) != freq.end()) {
            if (y != x) {
                if (freq[y] >= freq[x]) {
                    total--;
                }
            } else {
                if (freq[x] % 2 == 0) {
                    total--;
                }
            }
        }

        freq[x]--;
    }

    vector<int> solve() {
        const int blockSize = sqrt(n);
        sort(queries.begin(), queries.end(),
            [&](const Query& q1, const Query& q2) {
                if (q1.from / blockSize != q2.from / blockSize) {
                    return q1.from / blockSize < q2.from / blockSize;
                }
                return q1.to < q2.to;
            }
        );

        vector<int> ans(queries.size());

        int from = 0, to = -1;

        for (Query& q : queries) {
            while (from > q.from) {
                from--;
                add(from);
            }
            while (to < q.to) {
                to++;
                add(to);
            }
            while (from < q.from) {
                remove(from);
                from++;
            }
            while (to > q.to) {
                remove(to);
                to--;
            }
            ans[q.index] = total;
        }

        return ans;
    }
};

struct Solver {
    Solver(int n, int m, int k) {
        vector<int> a(n);

        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }

        vector<Query> queries;

        for (int i = 0; i < m; i++) {
            int from, to;
            cin >> from >> to;
            from--; to--;
            if (from > to) swap(from, to);
            queries.emplace_back(from, to, i);
        }

        MoSolver moSolver(a, queries, n, k);
        vector<int> ans = moSolver.solve();

        for (int i = 0; i < (int) ans.size(); i++) {
            cout << ans[i] << '\n';
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    while (true) {
        int n, m, k;
        cin >> n >> m >> k;
        if (n == 0 && m == 0 && k == 0) break;
        Solver(n, m, k);
        cout << "\n";
    }

    return 0;
}