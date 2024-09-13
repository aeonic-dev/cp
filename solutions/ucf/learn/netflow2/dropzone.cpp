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

int get() {
    int h, t;
    scanf("%d.%d", &h, &t);
    return h * 100 + t;
}

const ll inf = 1e8;

void solve() {
    int n, m;
    cin >> n >> m;

    vector<string> gr(n);
    rep(i, 0, n) cin >> gr[i];

    int so = n * m, si = so + 1;
    Dinic net(si + 1);
    auto add = [&](int i1, int j1, int i2, int j2) -> void {
        if (i2 < 0 || i2 >= n || j2 < 0 || j2 >= m) return;
        if (gr[i2][j2] == 'X') return;

        int u = i1 * m + j1, v = i2 * m + j2;
        net.addEdge(u, v, 1);
        net.addEdge(v, u, 1);
    };
    rep(i, 0, n) {
        rep(j, 0, m) {
            if (gr[i][j] == 'X') continue;

            add(i, j, i + 1, j);
            add(i, j, i, j + 1);

            if (gr[i][j] == 'D')
                net.addEdge(so, i * m + j, inf);

            if (!i) net.addEdge(i * m + j, si, 1);
            if (!j) net.addEdge(i * m + j, si, 1);
            if (i == n - 1) net.addEdge(i * m + j, si, 1);
            if (j == m - 1) net.addEdge(i * m + j, si, 1);
        }
    }
    ll res = net.calc(so, si);
    cout << res << "\n";
}

int main() {
    // cin.tie(0)->sync_with_stdio(0);
    // cin.exceptions(cin.failbit);

    int t = 1;
    cin >> t;
    while (t--) solve();

    return 0;
}
