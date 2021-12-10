#pragma once

#include <bits/stdc++.h>
#include "mod_inverse.hpp"
using namespace std;

/**
 * Use:
 *     BinomialCoefficient C(N, mod);
 *     int five_choose_three = C(5, 3);
**/
struct BinomialCoefficient {
    const int N;
    int mod;
    vector<int> fact;
    vector<int> inv_fact;

    BinomialCoefficient(int N_, int mod_)
        : N(N_), mod(mod_), fact(N), inv_fact(N) {
        fact[0] = 1;
        for (int i = 1; i <= N; i++) {
            fact[i] = modMul(fact[i - 1], i, mod);
        }
        inv_fact[N] = modInv(fact[N], mod);
        for (int i = N - 1; i >= 0; i--) {
            inv_fact[i] = modMul(inv_fact[i + 1], i + 1, mod);
        }
    }

    int operator()(int n, int k) {
        int res =
            modMul(fact[n], modMul(inv_fact[k], inv_fact[n - k], mod), mod);
        return res;
    }
};
