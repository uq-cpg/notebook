#pragma once

#include <bits/stdc++.h>

using namespace std;

// z[i]: length of the longest common prefix between s and
// its substring starting at i
vector<int> zFunction(const string& s) {
    int n = s.length();
    vector<int> z(n);
    z[0] = n;
    int l = 0;
    int r = 0;

    for (int i = 1; i < n; i++) {
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
