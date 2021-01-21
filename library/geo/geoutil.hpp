#pragma once

#include <bits/stdc++.h>

using namespace std;

const double PI = acos(-1);

template <typename T>
int sgn(T x) {
    if (x > 0) return 1;
    if (x < 0) return -1;
    return 0;
}

int inc(int i, int n, int by=1) {
    i += by;
    if (i >= n) i -= n;
    return i;
}

double degToRad(double d) {
    return d * PI / 180.0;
}

double radToDeg(double r) {
    return r * 180.0 / PI;
}