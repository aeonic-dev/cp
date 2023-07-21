template<typename n_t = int, typename f_t = int, f_t infinity = INT_MAX>
struct ffa {
    n_t n;
    vector<vector<f_t>> residual;
    vector<bool> seen;

    ffa(n_t n) : n(n) {
        static_assert(is_integral<n_t>::value, "node index type must be integral");
        static_assert(is_integral<f_t>::value, "flow value type must be integral");

        residual = vector<vector<f_t>>(n, vector<f_t>(n));
    }

    // Adds an edge to the network
    void add_edge(n_t u, n_t v, f_t capacity, bool bidirectional = false) {
        residual[u][v] += capacity;
        if (bidirectional) residual[v][u] += capacity;
    }

    // Find augmenting paths in the network
    f_t dfs(n_t cur, n_t t, f_t flow) {
        if (cur == t) return flow;

        for (n_t next = 0; next < n; next++) {
            if (residual[cur][next] == 0 || seen[next]) continue;

            seen[next] = true;
            f_t f = dfs(next, t, min(flow, residual[cur][next]));
            if (f != 0) {
                residual[cur][next] -= f;
                residual[next][cur] += f;
                return f;
            }
        }

        return 0;
    }

    // Gets the max flow from s to t
    f_t max_flow(n_t s, n_t t) {
        f_t flow = 0;

        while (true) {
            seen = vector<bool>(n, false);
            seen[s] = true;

            f_t f = dfs(s, t, infinity);
            if (f == 0) break;

            flow += f;
        }

        return flow;
    }
};