#include<bits/stdc++.h>
using namespace std;

const int N = 1e5;
int lpf[N + 1];
vector<int> primes;
bitset<N + 1> is_prime;

// use bitset<N> is_prime; to have O(N/64) memory complexity
// using bitset you can solve upto around N = 10^8 in 1s

void sieve() {
    is_prime.set();
    for (ll i = 2; i * i <= N; ++i) {
        if (is_prime[i]) {
            for (ll j = i * i; j < N; j += i)
                is_prime[j] = 0;
        }
    }
    for (int i = 0; i <= N; ++i)
        if (is_prime[i])
            primes.push_back(i);
}

void sieve_lpf() {
    for (int i = 2; i < N; i++) {
        lpf[i] = i;
    }
    for (int i = 2; i * i < N; i++) {
        if (lpf[i] == i) {
            for (int j = i * i; j < N; j += i) {
                lpf[j] =i;
            }
        }
    }
    for (int i = 2; i < N; i++) {
        if (lpf[i] == i) {
            primes.push_back(i);
        }
    }
}
int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  sieve();
  cout << primes.size() << '\n';
  primes.clear();
  sieve_lpf();
  cout << primes.size() << '\n';
  return 0;
}
