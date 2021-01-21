#pragma once

#include "mod.hpp"
#include "extended_euclidean.hpp"

/// This mod inverse function applies Fermat's little theorem
//  Can only be used if $m$ is prime, and $a$ and $m$ are coprime
int64_t modInvPrimeMod(int64_t a, int64_t m, int mod) {
    return modPow(a, m - 2, mod);
}

int64_t modInv(int64_t a, int mod) {
    int64_t x, y;
    int64_t g = extGcd(a, mod, x, y);
    assert(g == 1);
    return (x % mod + mod) % mod;
}

// Calculate the mod inverse of all number in range $[1, n]$
// Time: $O(n)$
vector<int> calcInv(int n, int mod) {
    vector<int> inv(n + 1);
    inv[1] = 1;

    for(int i = 2; i <= n; ++i) {
        inv[i] = mod - (mod / i) * inv[mod % i] % mod;
    }

    return inv;
}
