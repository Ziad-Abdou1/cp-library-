#include <bits/stdc++.h>
using namespace std;
// #define int long long
#define ll long long
#define el endl
#define pb push_back
#define sz(a) (int)a.size()
#define yes cout << "YES"<<el
#define no cout << "NO" << el
#define vi(v, n) vector<int> v(n); for (int i = 0; i < n; ++i) cin >> v[i]
#define vll(v, n) vector<ll> v(n); for (int i = 0; i < n; ++i) cin >> v[i]
#define all(v)   v.begin(), v.end()
#define sp ' '
using ld = long double;

const int N = 2e5 + 7;


vector<vector<pair<int, int> > > adj;
bitset<N> vis;
vector<int> ord;

void dfs(int u) {
    vis[u] = true;
    for (auto v: adj[u]) {
        if (vis[v.first]) continue ;
        dfs(v.first);
    }
    ord.pb(u);
}



vector<int> topsort(int n) {
    vis.reset();
    ord.clear();
    for (int i = 0; i < n; ++i) {
        if (!vis[i]) dfs(i);
    }
    reverse(all(ord));
    vector<int> pos(n);
    for (int i = 0; i < n; ++i) {
        pos[ord[i]] = i;
    }
    for (int u = 0; u < n; ++u) {
        for (auto v: adj[u]) {
            if (pos[u] > pos[v.first]) {
                // cycle detection
                cout << "IMPOSSIBLE" << el;
                return {} ;
            }
        }
    }
    return ord;
}


// finds the shortest path from a start node to all other nodes in the graph  (DAG) .
vector<ll> topsort_shortpath(int n, int start) {
    vector<int> ord = topsort(n);
    vector<ll> dist(n, 1e9);  // note change 1e9
    dist[start] = 0;
    for (int i = 0; i < n; ++i) {
        int u = ord[i];
        // if node is reachable
        if (dist[u] != 1e9) {
            for (auto to: adj[u]) {
                ll newDist = dist[u] + to.second;
                dist[to.first] = min(dist[to.first], newDist);
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        if (dist[i] == 1e9) dist[i] = -1; // unreachable nodes
    }
    return dist;
}


// Kahn's Algorithm Topological sort
vector<int> topsort_kahn(int n) {
    vector<int> deg(n);
    for (int i = 0; i < n; ++i) {
        for (auto v: adj[i]) {
            deg[v.first]++;
        }
    }
    queue<int> q;
    for (int i = 0; i < n; ++i) {
        if (deg[i] == 0) q.push(i);
    }
    vector<int> ord;
    int num = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        ord.pb(u);
        num++;
        for (auto v: adj[u]) {
            deg[v.first]--;
            if (deg[v.first] == 0) q.push(v.first);
        }
    }
    // cycle detection
    if ( num!= n) {
        cout << "IMPOSSIBLE" << el;
        return {} ;
    }
    return ord ;
}

void solve() {
    int n, m;
    cin >> n >> m;
    adj.resize(n);
    bool ok = true;
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v>> w;
        if (u == v) ok = false; // Self-loop detection
        u--;
        v--;
        adj[u].pb({v, w});
    }
    if (!ok) {
        cout << "Graph contains self-loops";
        return;
    }

}


int main() {

#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
#endif

    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);


    int tt = 1;
    // cin >> tt;
    while (tt-- > 0) {
        solve();
    }
    return 0;
}
