#include <bits/stdc++.h>
using namespace std;

/// Sieve of Eratosthenes
/// Benchmark: 3314 ms/188.74 Mib for N = 5 * 1e8
/// Credit: KTH's notebook
constexpr int MAX_N = (int) 5 * 1e8;
bitset<MAX_N + 1> is_prime;
vector<int> primes;

void sieve(int N) {
    is_prime.set();
    is_prime[0] = is_prime[1] = 0;
    for (int i = 4; i <= N; i += 2) is_prime[i] = 0;
    for (int i = 3; i * i <= N; i += 2) {
        if (!is_prime[i]) continue;
        for (int j = i * i; j <= N; j += i * 2) {
            is_prime[j] = 0;
        }
    }
    for (int i = 2; i <= N; i++) {
        if (is_prime[i]) primes.push_back(i);
    }
}

// https://judge.yosupo.jp/problem/enumerate_primes
int main() {
    int N, a, b; cin >> N >> a >> b;
    sieve(N);
    int num_primes = primes.size();
    vector<int> res;
    for (int j = 0; a * j + b < num_primes; j++) {
        res.push_back(primes[a * j + b]);
    }
    cout << num_primes << ' ' << res.size() << '\n';
    for (int p : res) cout << p << ' ';
    cout << '\n';
}
