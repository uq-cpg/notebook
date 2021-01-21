// **Really important note**: inputs of the modAdd, modSub, and modMul
// functions must all be normalized (within the range [0..mod - 1]) before use

/// @status:
///   - modMul and modPow tested on:
///      https://cses.fi/problemset/task/1095
///      https://cses.fi/problemset/task/1712
///   - modAdd, modSub, modMul, extGcd, modInv tested on:
///      https://cses.fi/problemset/task/1082
///   - C (binary coefficient) tested on:
///      https://cses.fi/problemset/task/1079

#pragma once

#include <bits/stdc++.h>

using namespace std;

int modAdd(int a, int b, int mod) {
    a += b;
    if (a >= mod) a -= mod;
    return a;
}

int modSub(int a, int b, int mod) {
    a -= b;
    if (a < 0) a += mod;
    return a;
}

int modMul(int a, int b, int mod) {
    int64_t res = (int64_t) a * b;
    return (int) (res % mod);
}

int64_t binPow(int64_t a, int64_t x) {
    int64_t res = 1;
    while (x) {
        if (x & 1) res *= a;
        a *= a;
        x >>= 1;
    }
    return res;
}

int64_t modPow(int64_t a, int64_t x, int mod) {
    int res = 1;
    while (x) {
        if (x & 1) res = modMul(res, a, mod);
        a = modMul(a, a, mod);
        x >>= 1;
    }
    return res;
}

/// This solves the equation ax + by = gcd(a, b);
/// Input: a, b
//  Output: g (returned), x, y (passed by ref)
int64_t extGcd(int64_t a, int64_t b, int64_t& x, int64_t& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    int64_t x1, y1;
    int64_t g = extGcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    assert(g == 1);
    return g;
}

/// This mod inverse function applies Fermat's little theorem
//  Can only be used if m is prime, and a and m are coprime
int64_t modInvPrimeMod(int64_t a, int64_t m, int mod) {
    return modPow(a, m - 2, mod);
}

int64_t modInv(int64_t a, int mod) {
    int64_t x, y;
    int64_t g = extGcd(a, mod, x, y);
    assert(g == 1);
    return (x % mod + mod) % mod;
}

vector<int> calcInv(int n, int mod) {
    vector<int> inv(n + 1);
    inv[1] = 1;

    for(int i = 2; i <= n; ++i) {
        inv[i] = mod - (mod / i) * inv[mod % i] % mod;
    }

    return inv;
}

struct BinomialCoefficient {
    const int N;
    int mod;
    vector<int> fact;
    vector<int> inv_fact;

    BinomialCoefficient(int N_, int mod_) : N(N_), mod(mod_), fact(N), inv_fact(N) {
        fact[0] = 1;
        for (int i = 1; i <= N; i++) {
            fact[i] = modMul(fact[i - 1], i, mod);
        }
        inv_fact[N] = modInv(fact[N], mod);
        for (int i = N - 1; i >= 0; i--) {
            inv_fact[i] = modMul(inv_fact[i + 1], i + 1, mod);
        }
    }

    int C(int n, int k) {
        int res = modMul(fact[n], modMul(inv_fact[k], inv_fact[n - k], mod), mod);
        return res;
    }
};