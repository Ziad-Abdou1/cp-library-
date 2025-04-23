#include <bits/stdc++.h>
using namespace std;

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
/*
        This is not laziness, this is just power saving
*/
// O(V * E^2)
// Edmonds-Karp (BFS-based Ford-Fulkerson)
const long long INF = 1e18;
int V, s, t;
vector<vector<long long> > res;

long long maxflow() {
    long long max_flow = 0;
    while (true) {
        vector<int> par(V, -1);
        queue<int> q;
        q.push(s);
        par[s] = -2;

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v = 0; v < V; v++) {
                if (res[u][v] > 0 && par[v] == -1) {
                    par[v] = u;
                    q.push(v);
                    if (v == t) break;
                }
            }
        }

        if (par[t] == -1) break;

        ll flow = INF;
        for (int u = t; u != s; u = par[u])
            flow = min(flow, res[par[u]][u]);

        for (int u = t; u != s; u = par[u]) {
            res[par[u]][u] -= flow;
            res[u][par[u]] += flow;
        }

        max_flow += flow;
    }
    return max_flow;
}

void dfs_min_cut(int u, vector<bool> &visited) {
    visited[u] = true;
    for (int v = 0; v < V; ++v) {
        if (!visit[v] && res[u][v] > 0) {
            dfs_min_cut(v, visited);
        }
    }
}

void solve() {
    int E;
    cin >> V >> E;
    res.assign(V, vector<long long>(V, 0));

    for (int i = 0; i < E; i++) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        u--;
        v--;
        res[u][v] += w;
    }

    s = 0;
    t = V - 1;

    cout << maxflow() << "\n";

    vector<bool> visited(V, false);
    dfs_min_cut(s, visited);
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
