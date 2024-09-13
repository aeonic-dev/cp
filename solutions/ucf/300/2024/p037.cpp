#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;

const ll inf = INT_MAX;
void floydWarshall(vector<vector<ll>> &m) {
    int n = sz(m);
    rep(i, 0, n) m[i][i] = min(m[i][i], 0LL);
    rep(k, 0, n) rep(i, 0, n) rep(j, 0, n) if (m[i][k] != inf && m[k][j] != inf) {
        auto newDist = max(m[i][k] + m[k][j], -inf);
        m[i][j] = min(m[i][j], newDist);
    }
    rep(k, 0, n) if (m[k][k] < 0) rep(i, 0, n) rep(j, 0, n) if (m[i][k] != inf && m[k][j] != inf) m[i][j] = -inf;
}

struct Dinic {
    struct Edge {
        int to, rev;
        ll c, oc;
        ll flow() { return max(oc - c, 0LL); } // if you need flows
    };
    vi lvl, ptr, q;
    vector<vector<Edge>> adj;
    Dinic(int n) : lvl(n), ptr(n), q(n), adj(n) {}
    void addEdge(int a, int b, ll c, ll rcap = 0) {
        adj[a].push_back({b, sz(adj[b]), c, c});
        adj[b].push_back({a, sz(adj[a]) - 1, rcap, rcap});
    }
    ll dfs(int v, int t, ll f) {
        if (v == t || !f) return f;
        for (int &i = ptr[v]; i < sz(adj[v]); i++) {
            Edge &e = adj[v][i];
            if (lvl[e.to] == lvl[v] + 1)
                if (ll p = dfs(e.to, t, min(f, e.c))) {
                    e.c -= p, adj[e.to][e.rev].c += p;
                    return p;
                }
        }
        return 0;
    }
    ll calc(int s, int t) {
        ll flow = 0;
        q[0] = s;
        rep(L, 0, 31) do { // 'int L=30' maybe faster for random data
            lvl = ptr = vi(sz(q));
            int qi = 0, qe = lvl[s] = 1;
            while (qi < qe && !lvl[t]) {
                int v = q[qi++];
                for (Edge e : adj[v])
                    if (!lvl[e.to] && e.c >> (30 - L))
                        q[qe++] = e.to, lvl[e.to] = lvl[v] + 1;
            }
            while (ll p = dfs(s, t, LLONG_MAX)) flow += p;
        }
        while (lvl[t]);
        return flow;
    }
    bool leftOfMinCut(int a) { return lvl[a] != 0; }
};

void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<vll> adj(n, vll(n, inf));
    rep(_, 0, m) {
        int u, v, w;
        cin >> u >> v >> w, u--, v--;
        adj[u][v] = w;
    }
    floydWarshall(adj);
    vector<tuple<int, int, ll, ll>> trips(k); // {start, end, start time, end time}
    rep(i, 0, k) {
        auto &[u, v, s, e] = trips[i];
        cin >> u >> v >> s, u--, v--;
        e = s + adj[u][v];
    }

    Dinic meta(2 * k + 2); // {out, in} for i = {2i, 2i+1}
    int so = 2 * k, si = so + 1;
    rep(i, 0, k) {
        meta.addEdge(so, 2 * i, 1);
        meta.addEdge(2 * i + 1, si, 1);

        auto [u_i, v_i, s_i, e_i] = trips[i];
        rep(j, 0, k) {
            if (i == j) continue;
            auto [u_j, v_j, s_j, e_j] = trips[j];
            ll d = adj[v_i][u_j];
            if (e_i + d > s_j) continue;

            meta.addEdge(2 * i, 2 * j + 1, 1);
        }
    }
    int res = k - meta.calc(so, si);
    cout << res << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
    // cin >> t;
    while (t--) solve();

    return 0;
}
