#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define el endl
#define pb push_back
#define sz(a) (int)a.size()
#define yes cout << "YES"<<el
#define no cout << "NO" << el
#define all(v)   v.begin(), v.end()
#define sp ' '
using ld = long double;

const int inf = 1e9;

vector<vector<int> > adj;

vector<int> farthest(int s, const int n) {
    vector<int> dis(n, inf);
    vector<bool> vis(n);
    queue<int> q;
    q.push(s);
    dis[s] = 0;
    vis[s] = true;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v: adj[u]) {
            if (vis[v])continue;
            dis[v] = dis[u] + 1;
            q.push(v);
            vis[v] = true;
        }
    }
    return dis;
}


void solve() {
    int n;
    cin >> n;
    adj.resize(n);
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    if (n == 1) {
        cout << 0 << endl;
        return;
    }
    vector<int> dis = farthest(0, n);
    int x = max_element(all(dis)) - dis.begin();
    vector<int> dx = farthest(x, n);
    int y = max_element(all(dx)) - dx.begin();
    vector<int> dy = farthest(y, n);

    int diameter = dx[y];
    cout << diameter << endl;

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
