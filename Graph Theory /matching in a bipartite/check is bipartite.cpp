 vector<int> grp(n, 0);
    for (int u = 0; u < n; u++) {
        if (grp[u] == 0) {
            queue<int> q;
            grp[u] = 1;
            q.push(u);
            while (!q.empty()) {
                int v = q.front();
                q.pop();
                for (int w : adj[v]) {
                    if (grp[w] == 0) {
                        grp[w] = 3 - grp[v];
                        q.push(w);
                    } else if (grp[w] == grp[v]) {
                        cout << -1 << endl;
                        return 0;
                    }
                }
            }
        }
    }
