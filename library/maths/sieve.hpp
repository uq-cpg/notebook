// Computes primes in the range [2, n] in n ln ln sqrt(n) + o(n) time.
// https://cp-algorithms.com/algebra/sieve-of-eratosthenes.html

#pragma once

#include <bits/stdc++.h>

using namespace std;

int main() {
    int n = 100;
    vector<char> is_prime(n+1, true);
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i * i <= n; i++) {
        if (is_prime[i]) {
            for (int j = i * i; j <= n; j += i)
                is_prime[j] = false;
        }
    }
    for (int i = 0; i < n; i++) {
        if (is_prime[i]) {
            cout << i << ' ';
        }
    }
}