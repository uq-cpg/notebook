#pragma once

#include <bits/stdc++.h>

using namespace std;

template <typename T>
T gcd(T a, T b) {
    if (a < b) swap(a, b);
    while (b != 0) {
        int r = a % b;
        a = b;
        b = r;
    }
    return a;
}

template <typename T>
int64_t lcm(T a, T b) {
    return (int64_t) a / gcd(a, b) * b;
}