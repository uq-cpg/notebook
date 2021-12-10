#include <bits/stdc++.h>
using namespace std;

struct Query {
    int from, to, index;
    Query(int f, int t, int i) : from(f), to(t), index(i) {}
};

struct MoSolver {
    vector<int> a;
    vector<Query> queries;

    MoSolver(vector<int>& a_) : a(a_) {}

    virtual void add(int index) = 0; // add a[index] to current range
    virtual void remove(int index) = 0; // remove a[index] from current range
    virtual int getAnswer() = 0; // get result of current range

    void addQuery(int from, int to) {
        queries.emplace_back(from, to, queries.size());
    }

    vector<int> solve() {
        const int blockSize = 700;
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
                from--; add(from);
            }
            while (to < q.to) {
                to++; add(to);
            }
            while (from < q.from) {
                remove(from); from++;
            }
            while (to > q.to) {
                remove(to); to--;
            }
            ans[q.index] = getAnswer();
        }
        return ans;
    }
};

struct Solver : MoSolver { // https://www.spoj.com/problems/DQUERY/
    const int MAX = 1e6 + 1;
    vector<int> cnt;
    int distinct;

    Solver(vector<int>& a_) : MoSolver(a_), cnt(MAX, 0), distinct(0) {}

    void add(int index) {
        if (cnt[a[index]] == 0) distinct++;
        cnt[a[index]]++;
    }

    void remove(int index) {
        if (cnt[a[index]] == 1) distinct--;
        cnt[a[index]]--;
    }

    int getAnswer() {
        return distinct;
    }
};

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n; cin >> n;
    vector<int> a(n); for (int i = 0; i < n; i++) cin >> a[i];
    int q; cin >> q;
    Solver solver(a);
    for (int i = 0; i < q; i++) {
        int from, to; cin >> from >> to; from--; to--;
        solver.addQuery(from, to);
    }
    vector<int> ans = solver.solve();
    for (int x : ans) cout << x << '\n';
    return 0;
}
