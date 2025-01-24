struct SCC {
    vector<vector<int> > g, reg, scc_group, dag;
    vector<int> comp, vis, id, roots;
    int n, scc_cnt;

    SCC() {
    }

    SCC(int _n) {
        n = _n;
        scc_cnt = 0;
        g.resize(n);
        reg.resize(n);
        vis.resize(n);
        id.resize(n);
        dag.clear();
        comp.clear();
        scc_group.clear();
        roots.clear();
    }

    void add(int u, int v) {
        g[u].push_back(v);
        reg[v].push_back(u);
    }

    void build() {
        for (int u = 0; u < n; ++u) {
            if (!vis[u])dfs(u, g);
        }
        auto topsort = comp;
        reverse(all(topsort));
        vis.assign(n, 0);

        for (auto u: topsort) {
            if (!vis[u]) {
                comp.clear();
                dfs(u, reg);
                for (auto v: comp) {
                    id[v] = comp.front();
                }
                roots.push_back(comp.front());
            }
        }
        
        for (int u = 0; u < n; ++u) {
            for (auto v: g[u]) {
                if (id[u] != id[v]) {
                    dag[id[u]].pb(id[v]);
                }
            }
        }
    }

    void dfs(int u, vector<vector<int> > &g) {
        vis[u] = 1;
        for (auto v: g[u]) {
            if (vis[v])continue;
            dfs(v, g);
        }
        comp.pb(u);
    }
};
