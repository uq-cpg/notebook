// https://judge.yosupo.jp/submission/63281
#include <bits/stdc++.h>
using namespace std;

/**
 * z[i]: length of the longest common prefix of s and s[i:]
**/
vector<int> zFunction(const string& s) {
    int n = s.length();
    vector<int> z(n);
    z[0] = n;
    for (int l = 0, r = 0, i = 1; i < n; i++) {
        if (i <= r) {
            z[i] = min(z[i - l], r - i + 1);
        }
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
            z[i]++;
        }
        if (i + z[i] - 1 > r) {
            l = i;
            r = i + z[i] - 1;
        }
    }
    return z;
}

struct ZFunction : vector<int> {
    ZFunction(const string& s) : vector<int>(s.size(), 0) {
        auto& z = *this;
        int n = z.size();
        z[0] = n;
        for (int i = 1, l = 0, r = 0; i < n; ++i) {
            if (i <= r) {
                z[i] = std::min(r - i + 1, z[i - l]);
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
    cout << endl;
    return 0;
}
