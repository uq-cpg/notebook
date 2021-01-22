#pragma once

#include <bits/stdc++.h>

using namespace std;

// Euler's totient function
// $\phi(i)$ = number of coprime numbers of n in the range $[1..n]$
// Multiplicative property: $\phi(a * b) = phi(a) * phi(b)$
// Complexity: $O(\sqrt(n))$
int eulerPhi(int n) {
    int res = n;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            while (n % i == 0) {
                n /= i;
            }
            res -= res / i;
        }
    }
    if (n > 1) {
        res -= res / n;
    }
    return res;
}

// Complexity: $O(n\log\log(n))$
vector<int> eulerPhiN(int n) {
    vector<int> phi(n + 1);
    phi[0] = 0;
    phi[1] = 1;

    for (int i = 2; i <= n; i++) phi[i] = i;

    for (int i = 2; i <= n; i++) {
        if (phi[i] == i) {
            for (int j = i; j <= n; j += i) {
                phi[j] -= phi[j] / i;
            }
        }
    }

    return phi;
}
