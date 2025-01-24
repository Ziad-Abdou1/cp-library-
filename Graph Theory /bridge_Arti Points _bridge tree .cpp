#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
using namespace std;

#define ll long long
#define el endl
#define pb push_back
// #define sz(a) (int)a.size()
#define yes cout << "YES"<<el
#define no cout << "NO" << el
#define all(v)   v.begin(), v.end()
#define sp ' '


vector<ll> depth, low;
vector<bool> vis, is_bridge;
vector<pair<int, int> > ans;
vector<vector<int> > new_tree;
vector<vector<pair<int, int> > > adj;


// dfs  -  bridge  -  Articulation Points
void dfs(int u, int p) {
    vis[u] = true;
    low[u] = depth[u];
    int kids = 0;
    for (auto to: adj[u]) {
        int v = to.first;
        int index = to.second;
        if (v == p)continue;
        if (vis[v]) {
            // back edge
            low[u] = min(low[u], low[v]);
            continue;
        }
        // Forward edge (tree edge)
        depth[v] = depth[u] + 1;
        dfs(v, u);
        low[u] = min(low[u], low[v]);
        if (low[v] >= depth[u]) {
            // if bridge
            is_bridge[index] = true;
        }
        if (low[v] >= depth[u]) {
            // this is Articulation Points if
            // ( p!= -1 || kids > 1 )
        }
    }
}

int id;
vector<int> group;

void dfs1(int u, int p) {
    vis[u] = true;
    group[u] = id;
    for (auto to: adj[u]) {
        if (to.first == p || is_bridge[to.second] || vis[to.first]) continue;
        dfs1(to.first, u);
    }
}

void solve() {
    int n, m;
    cin >> n >> m;
    adj = vector<vector<pair<int, int> > >(n);
    vis = is_bridge = vector<bool>(n, false);
    low = depth = vector<ll>(n, 0);
    vector<pair<int, int> > edges;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].pb({v, i});
        adj[v].pb({u, i});
        edges.pb({u, v});
    }
    dfs(0, -1);
    vis.clear();
    id = 0;
    for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            dfs1(i, -1);
            id++;
        }
    }

    for (int i = 0; i < m; i++) {
        if (is_bridge[i]) {
            new_tree[group[edges[i].first]].push_back(group[edges[i].second]);
            new_tree[group[edges[i].second]].push_back(group[edges[i].first]);
        }
    }
}


int main() {
    //freopen("filename.in", "r", stdin);
    //freopen("filename.out", "w", stdout);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
#endif

    ios::sync_with_stdio(false);
    cin.tie(nullptr);


    int tt = 1;
    cin >> tt;
    while (tt-- > 0) {
        solve();
    }
    return 0;
}
