#include<bits/stdc++.h>
using namespace std;

// O(log(n))
// requires sieve_lpf 
vector<pair<int, int> > prime_factors_lpf(int n) {
    vector<pair<int, int> > ans;
    while (n != 1) {
        int p = lpf[n];
        int e = 0;
        while (p == lpf[n]) {
            e++;
            n /= p;
        }
        ans.push_back({p, e});
    }
    return ans;
}

// O(sqrt(n)/log(n))
//requires sieve take root(n)
vector<pair<int, int> > prime_factors_sieve(int n) {
    vector<pair<int, int> > ans;
    for (auto it: primes) {
        if (it * it > n) break;
        int pow = 0;
        while (n % it == 0) {
            n /= it;
            pow++;
        }
        if (pow) {
            ans.push_back({it, pow});
            if (n == 1) break;
        }
        if (n != 1) ans.push_back({n, 1});
        return ans;
    }
}

// O(sqrt(n))
vector<pair<int, int> > prime_factors(int n) {
    vector<pair<int, int> > ans;
    for (ll i = 2; i * i <= n; ++i) {
        if (n % i == 0) {
            ans.pb({i, 0});
            while (n % i == 0) n /= i;
        }
    }
    if (n != 1) ans.pb({n, 1});
    return ans;
}
