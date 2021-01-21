// Euclidean algorithm for GCD & LCM
// https://cp-algorithms.com/algebra/euclid-algorithm.html

#pragma once
#include <bits/stdc++.h>

int gcd (int a, int b) {
    return b ? gcd (b, a % b) : a;
}

// lcm(a,b) = a*b/(gcd(a,b))
int lcm (int a, int b) {
    return a / gcd(a, b) * b;
}