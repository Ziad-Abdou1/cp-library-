// o(N+M)
void bfs (vector<vector<int>> adj , int  n ) {
    vector<ll> dist(n, inf), par(n, -1); 
    dist[0] = 0;
    queue<ll> q;
    q.push(0);
    while (!q.empty()) {
        ll u = q.front();
        q.pop();
        for (auto v: adj[u]) {
            if (dist[v] > dist[u] + 1) {
                dist[v] = dist[u] + 1;
                q.push(v);
                par[v] = u;
            }
        }
    }
   
    // print path
    vector<ll> path;
    ll u = n - 1;
    while (u != -1) {
        path.pb(u);
        u = par[u];
    }
    reverse(path.begin(), path.end());
    for (auto v: path) {
        cout << v + 1 << endl ;
    }
}
