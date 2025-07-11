struct TwoSat {
    int N;
    vector<vector<int> > gr;
    vector<int> values;

    TwoSat(int n): N(n), gr(2 * n) {
    }

    int addVar() {
        gr.emplace_back();
        gr.emplace_back();
        return N++;
    }

    // At least one of them is true
    void add_or(int f, int j) {
        f = max(2 * f, -1 - 2 * f);
        j = max(2 * j, -1 - 2 * j);
        gr[f].push_back(j ^ 1);
        gr[j].push_back(f ^ 1);
    }
    // at most one is true
    void at_most_one(int f, int j) {
        add_or(~f, ~j);
    }

    // Set variable x to true
    void setValue(int x) { add_or(x, x); }

    void setValue(int x, bool value) {
        if (value) {
            add_or(x, x);
        } else {
            add_or(~x, ~x);
        }
    }

    // Only one of them is true
    void add_xor(int f, int j) {
        add_or(f, j);
        add_or(~f, ~j);
    }

    // Both of them are true
    void add_and(int f, int j) {
        setValue(f);
        setValue(j);
    }

    // Both of them are false
    void add_nor(int f, int j) {
        add_and(~f, ~j);
    }

    // Both of them have the same value
    void add_xnor(int f, int j) {
        add_or(f, ~j);
        add_or(~f, j);
    }

    // At least one is false
    void add_nand(int f, int j) {
        add_or(~f, ~j);
    }

    // If f is true, then j must also be true
    void add_imply(int f, int j) {
        add_or(~f, j);
    }

    void at_most_oneA(vector<int> a) {
        int h_prv = addVar();
        add_imply(a[0], h_prv);
        for (int i = 1; i < (int) a.size(); i++) {
            int h_cur = addVar();
            add_imply(a[i], h_cur);
            add_imply(h_prv, ~a[i]);
            add_imply(h_prv, h_cur);
            swap(h_prv, h_cur);
        }
    }

    vector<int> val, comp, z;
    int time = 0;

    int dfs(int i) {
        int low = val[i] = ++time, x;
        z.push_back(i);
        for (int e: gr[i])
            if (!comp[e])
                low = min(low, val[e] ? val[e] : dfs(e));
        if (low == val[i])
            do {
                x = z.back();
                z.pop_back();
                comp[x] = low;
                if (values[x >> 1] == -1) values[x >> 1] = x & 1;
            } while (x != i);
        return val[i] = low;
    }

    bool solve() {
        values.assign(N, -1);
        val.assign(2 * N, 0);
        comp = val;
        for (int i = 0; i < 2 * N; ++i) {
            if (!comp[i]) dfs(i);
        }
        for (int i = 0; i < N; ++i) {
            if (comp[2 * i] == comp[2 * i + 1]) return 0;
        }
        return 1;
    }
};
