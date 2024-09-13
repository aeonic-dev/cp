#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
typedef long long ll;
typedef vector<int> vi;

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

int tc = 0;
void solve() {
    int n, m, k;
    cin >> m >> n >> k;
    cout << "Case #" << ++tc << ": ";

    vector<bitset<100>> gr(n);
    rep(_, 0, k) {
        int i1, j1, i2, j2;
        cin >> j1 >> i1 >> j2 >> i2;
        rep(i, i1, i2 + 1) rep(j, j1, j2 + 1) gr[i][j] = 1;
    }

    // cout << "\n";
    // rep(i, 0, n) {
    //     rep(j, 0, m) cout << "-x"[gr[i][j]];
    //     cout << '\n';
    // }

    int so = 2 * n * m, si = so + 1;
    Dinic net(si + 1);
    auto ind = [&](int i, int j, int side) -> int { return side * n * m + i * m + j; };
    auto add = [&](int i1, int j1, int i2, int j2) -> void {
        if (i2 < 0 || i2 >= n || j2 < 0 || j2 >= m) return;
        int u = ind(i1, j1, 1), v = ind(i2, j2, 0);
        net.addEdge(u, v, 1);
    };

    rep(i, 0, n) {
        rep(j, 0, m) {
            if (gr[i][j]) continue;

            net.addEdge(ind(i, j, 0), ind(i, j, 1), 1);
            add(i, j, i - 1, j);
            add(i, j, i + 1, j);
            add(i, j, i, j - 1);
            add(i, j, i, j + 1);
        }
    }
    rep(j, 0, m) {
        net.addEdge(so, ind(0, j, 0), 1);
        net.addEdge(ind(n - 1, j, 1), si, 1);
    }
    ll res = net.calc(so, si);
    cout << res << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
    cin >> t;
    while (t--) solve();

    return 0;
}
