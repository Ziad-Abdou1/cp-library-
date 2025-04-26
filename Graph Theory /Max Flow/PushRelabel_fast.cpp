// PushRelabel (Fastest) with gap heuristic and highest label selection
// Time Complexity: O(V² * √E)
const double eps = 1e-9;
template<class T>
struct push_relabel {
    struct Edge {
        int to, back;
        T flow, cap;
    };
 
    vector<T> ec;
    vector<int> H;
    vector<Edge *> cur;
    vector<vector<int>> hs;
    vector<vector<Edge>> g;
 
    push_relabel(int n) : g(n), ec(n), cur(n), hs(2 * n), H(n) {}
 
    void add_edge(int u, int v, T cap, T rcap = 0) {
        if (u == v) return;
        g[u].push_back({v, (int) g[v].size(), 0, cap});
        g[v].push_back({u, (int) g[u].size() - 1, 0, rcap});
    }
 
    void add_flow(Edge &e, T flow) {
        Edge &back = g[e.to][e.back];
        if (ec[e.to] <= eps && flow > eps) hs[H[e.to]].push_back(e.to);
        e.flow += flow, e.cap -= flow;
        ec[e.to] += flow;
        back.flow -= flow, back.cap += flow;
        ec[back.to] -= flow;
    }
 
    T max_flow(int s, int t) {
        int n = g.size();
        H[s] = n, ec[t] = 1;
        int co[2 * n];
        co[0] = n - 1;
        for (int i = 0; i < n; i++) cur[i] = g[i].data();
        for (Edge &e: g[s]) add_flow(e, e.cap);
        for (int hi = 0;;) {
            while (hs[hi].empty()) if (!hi--) return -ec[s];
            int u = hs[hi].back();
            hs[hi].pop_back();
            while (ec[u] > eps) {
                if (cur[u] == g[u].data() + g[u].size()) {
                    H[u] = 1e9;
                    for (Edge &e: g[u]) {
                        if (e.cap > eps && H[u] > H[e.to] + 1) {
                            H[u] = H[e.to] + 1, cur[u] = &e;
                        }
                    }
                    if (++co[H[u]], !--co[hi] && hi < n) {
                        for (int i = 0; i < n; i++) {
                            if (hi < H[i] && H[i] < n) {
                                --co[H[i]], H[i] = n + 1;
                            }
                        }
                    }
                    hi = H[u];
                } else if (cur[u]->cap && H[u] == H[cur[u]->to] + 1) {
                    add_flow(*cur[u], min(ec[u], cur[u]->cap));
                } else {
                    ++cur[u];
                }
            }
        }
    }
};
