#include <bits/stdc++.h>
using namespace std;

#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx")

#include <tr2/dynamic_bitset>
using dynamic_bitset = tr2::dynamic_bitset<>;
#define db dynamic_bitset
#define ll long long
#define el "\n"
#define pb push_back
#define yes cout << "YES"<<el
#define no cout << "NO" << el
#define all(v)   v.begin(), v.end()
#define sp ' '
#define fast ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define debug(x) cout << #x << " = " << x << "\n";
#define vdebug(a) cout << #a << " = "; for(auto x: a) cout << x << " "; cout << "\n";

vector<int> dx = {1, -1, 0, 0};
vector<int> dy = {0, 0, 1, -1};

struct sparsetable {
    int n, LOG;
    vector<vector<int> > st;

    sparsetable() {
    }

    sparsetable(vector<int> a) {
        n = a.size();
        LOG = bit_width(a.size()) + 1;
        st = vector<vector<int> >(LOG, vector<int>(n));
        st[0] = a;
        for (int j = 1; j < LOG; j++) {
            for (int i = 0; i + (1 << j) - 1 < n; i++) {
                st[j][i] = min(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
            }
        }
    }

    int query(int l, int r) {
        int k = __lg(r - l + 1);
        return min(st[k][l], st[k][r - (1 << k) + 1]);
    }
};

struct suffix_array {
    string s;
    vector<int> sa, lcp, pos;
    sparsetable st;

    suffix_array() {
    }

    suffix_array(string s) : s(s) {
        build_suffix_array();
        get_lcp();
        st = sparsetable(lcp);
    }

    void build_suffix_array() {
        s += ' ';
        const int A = 256;
        int n = s.size(), cls = 1;
        vector<int> c(n), cnt(max(A, n), 0);
        sa.resize(n);
        for (int i = 0; i < n; i++) cnt[s[i]]++;
        for (int i = 1; i < A; i++) cnt[i] += cnt[i - 1];
        for (int i = 0; i < n; i++) sa[--cnt[s[i]]] = i;
        c[sa[0]] = 0;
        for (int i = 1; i < n; i++) {
            if (s[sa[i]] != s[sa[i - 1]]) ++cls;
            c[sa[i]] = cls - 1;
        }
        vector<int> pn(n), cn(n);
        for (int k = 0; (1 << k) < n; ++k) {
            for (int i = 0; i < n; i++) {
                pn[i] = sa[i] - (1 << k);
                if (pn[i] < 0) pn[i] += n;
            }
            fill(begin(cnt), begin(cnt) + cls, 0);
            for (int i = 0; i < n; i++) cnt[c[pn[i]]]++;
            for (int i = 1; i < cls; i++) cnt[i] += cnt[i - 1];
            for (int i = n - 1; i >= 0; i--) sa[--cnt[c[pn[i]]]] = pn[i];
            cls = 1;
            cn[sa[0]] = 0;
            auto prv = make_pair(c[sa[0]], c[(sa[0] + (1 << k)) % n]);
            for (int i = 1; i < n; i++) {
                auto cur = make_pair(c[sa[i]], c[(sa[i] + (1 << k)) % n]);
                if (cur != prv) ++cls;
                cn[sa[i]] = cls - 1;
                swap(prv, cur);
            }
            swap(c, cn);
        }
        s.pop_back();
    }

    void get_lcp() {
        int n = s.size();
        pos.resize(n);
        lcp.resize(n);
        for (int i = 1; i <= n; i++) pos[sa[i]] = i - 1;
        int k = 0;
        for (int i = 0; i < n; i++) {
            int j = sa[pos[i]];
            while (s[i + k] == s[j + k]) k++;
            lcp[pos[i]] = k;
            k = max(k - 1, 0);
        }
    }

    int query_lcp(int i, int j) {
        int pi = pos[i];
        int pj = pos[j];
        if (pi == pj) return (s.size() - i);
        if (pi > pj) swap(pi, pj);
        return st.query(pi + 1, pj);
    }
};

void solve() {
    int n;
    cin >> n;
    string s;
    cin >> s;
    suffix_array sa(s);
    auto lcp = sa.lcp;
    vector<pair<int, int> > a(n);
    for (int i = 0; i < n; i++) {
        a[i] = {lcp[i], i};
    }
    auto F = [&](auto p1, auto p2) { return min(p1, p2); };
    sparsetable<pair<int, int> > st(a, F);
}

signed main() {
    fast
    int tc = 1;
    // cin >> tc;
    while (tc--) {
        solve();
    }
    return 0;
}
