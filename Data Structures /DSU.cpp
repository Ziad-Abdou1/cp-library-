struct DSU {
    vector<int> par, rnk, sz;
    int comps;

    DSU(int n) : par(n + 1), rnk(n + 1, 0), sz(n + 1, 1), comps(n) {
        iota(begin(par), end(par), 0);
    }

    int find(int u) {
        return (par[u] == u ? u : (par[u] = find(par[u])));
    }
    bool same(int u, int v) {
        return find(u) == find(v);
    }

    int get_size(int u) {
        return sz[find(u)];
    }
    bool merge(int u, int v) {
        if ((u = find(u)) == (v = find(v))) return false;
        if (sz[u] > sz[v]) swap(u, v);
        par[u] = v;
        sz[v] += sz[u];
        comps--;
        return true;
    }
};
