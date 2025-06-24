// Dinic (Very fast in practice)
// O(V * E * log(C)) where C is the maximum capacity of any edge
struct Dinic {
    struct Edge {
        int to, rev;
        ll c, oc;
        ll flow() { return max(oc - c, 0LL); }
    };

    vector<int> lvl, ptr, q;
    vector<vector<Edge>> g;
    Dinic(int n) : lvl(n), ptr(n), q(n), g(n) {}

    void add_edge(int a, int b, ll c, ll rcap = 0) {
        g[a].push_back({b, (int) size(g[b]), c, c});
        g[b].push_back({a, (int) size(g[a]) - 1, rcap, rcap});
    }

    ll dfs(int v, int t, ll f) {
        if (v == t || !f) return f;
        for (int &i = ptr[v]; i < size(g[v]); i++) {
            Edge &e = g[v][i];
            if (lvl[e.to] == lvl[v] + 1)
                if (ll p = dfs(e.to, t, min(f, e.c))) {
                    e.c -= p, g[e.to][e.rev].c += p;
                    return p;
                }
        }
        return 0;
    }

    ll calc(int s, int t) {
        ll flow = 0;
        q[0] = s;
        for (int L = 0; L <= 30; L++) do {
                lvl = ptr = vector<int>(size(q));
                int qi = 0, qe = lvl[s] = 1;
                while (qi < qe && !lvl[t]) {
                    int v = q[qi++];
                    for (Edge e: g[v])
                        if (!lvl[e.to] && e.c >> (30 - L))
                            q[qe++] = e.to, lvl[e.to] = lvl[v] + 1;
                }
                while (ll p = dfs(s, t, LLONG_MAX)) flow += p;
            } while (lvl[t]);
        return flow;
    }

    bool leftOfMinCut(int a) { return lvl[a] != 0; }
};
