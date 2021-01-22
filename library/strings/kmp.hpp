#pragma once

#include<bits/stdc++.h>

using namespace std;

// f[i]: length of the longest proper prefix of
// the substring s[0..i] which is also a suffix of
// this substring
vector<int> kmp(string& s) {
    int n = (int)s.length();
    vector<int> f(n);
    for (int i = 1; i < n; i++) {
        int j = f[i - 1];
        while (j > 0 && s[i] != s[j]) {
            j = f[j - 1];
        }
        if (s[i] == s[j]) {
            j++;
        }
        f[i] = j;
    }
    return f;
}