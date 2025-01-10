const int N = 1e5;
int lpf[N + 1];
vector<int> prims;
bool is_prime[N + 1];

// donot take root
void lpf_sieve() {
    // o(nloglog(n))
    for (ll i = 2; i < N; ++i) {
        if (lpf[i]) continue;
        prims.push_back(i), lpf[i] = i;
        for (ll j = i * i; j < N; j += i)
            if (!lpf[j]) lpf[j] = i;
    }
}
