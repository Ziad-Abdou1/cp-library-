#include <bits/stdc++.h>
using ld = long double;
using namespace std;
// #define int long long
#define ll long long
#define el endl


#define all(v)   v.begin(), v.end()
#define sp ' '


vector<bool>  is_bridge , vis ;
vector<int> tin , low ;
const int N = 3e5 + 10;
vector<vector<pair<int, int> > > g;
vector<vector<int>> new_tree;
int time_in ;
void dfs0 ( int u , int  p ) { // find bridge
    vis[u]=true;
    tin[u]=low[u]=++time_in;
    for ( auto to : g[u] ) {
        if ( to.first == p ) continue;
        if ( vis[to.first] ) { // back edge
            low[u]=min(low[u],tin[to.first]);
        }
        else {
            dfs0(to.first,u);
            low[u]=min(low[u],low[to.first]);
            if (low[to.first] > tin[u]) {
                is_bridge[to.second]=true;
            }
        }
    }
}

 // dfs to group
int id ;
vector<int> group ;
void dfs1 ( int u , int p) {
    vis[u]=true;
    group[u]=id ;
    for ( auto to : g[u] ) {
        if ( to.first == p || is_bridge[to.second] || vis[to.first] ) continue;
        dfs1(to.first,u);
    }
}


void solve() {
    int n, m;
    cin >> n >> m;
    tin.assign(n,0);is_bridge.assign(m,0);low.assign(n,0);vis.assign(n,false);group.assign(n, 0);
    time_in=-1;
    vector<pair<int, int> > edges;
    new_tree.assign(n, vector<int>());
    g.assign(n, vector<pair<int, int> >());
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v, u--, v--;
        g[u].emplace_back(v, i);
        g[v].emplace_back(u, i);
        edges.push_back(make_pair(u, v));

    }
    dfs0(0,-1);
    vis.assign(n,false);
    id=0;
    for(int i = 0; i < n; i++) {
        if(!vis[i]) {
            dfs1(i, -1);
            id++;
        }
    }
    for(int i = 0; i < m; i++) {
        if(is_bridge[i]) {
            new_tree [group[edges[i].first]].push_back(group[edges[i].second]);
            new_tree [group[edges[i].second]].push_back(group[edges[i].first]);
        }
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

    int tt = 1;
    // cin >> tt;
    while (tt-- > 0) {
        solve();
    }
    return 0;
}
