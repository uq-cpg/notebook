#include <bits/stdc++.h>
using namespace std;

/**
 * https://judge.yosupo.jp/submission/63580
 * z[i]: length of longest substring starting at i that is also a prefix of s
**/
struct ZFunction : vector<int> {
    ZFunction(const string& s) : vector<int>(s.size(), 0) {
        auto& z = *this;
        int n = z.size();
        z[0] = n;
        for (int i = 1, l = 0, r = 0; i < n; ++i) {
            if (i <= r) {
                z[i] = min(r - i + 1, z[i - l]);
            }
            while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
                ++z[i];
            }
            if (i + z[i] - 1 > r) {
                l = i;
                r = i + z[i] - 1;
            }
        }
    }
};

int main() {
    string s; cin >> s;
    ZFunction z(s);
    for (int i = 0; i < (int) z.size(); i++) cout << z[i] << ' ';
    cout << '\n';
    return 0;
}
