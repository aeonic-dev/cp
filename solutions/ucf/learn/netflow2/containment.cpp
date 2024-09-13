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

const ll inf = 1e8;
void solve() {
    int so = 1000, si = so + 1;
    Dinic net(si + 1);

    vector<vector<bitset<10>>> def(10, vector<bitset<10>>(10));
    int n;
    cin >> n;
    rep(i, 0, n) {
        int x, y, z;
        cin >> x >> y >> z;
        def[x][y][z] = 1;
    }

    vector<vi> adj(si + 1, vi(si + 1));
    auto ind = [&](int i, int j, int k) -> int { return i * 100 + j * 10 + k; };
    auto add = [&](int i1, int j1, int k1, int i2, int j2, int k2) -> void {
        if (i2 < 0 || i2 > 9
            || j2 < 0 || j2 > 9
            || k2 < 0 || k2 > 9) return;
        int u = ind(i1, j1, k1), v = ind(i2, j2, k2);
        adj[u][v] = adj[v][u] = 1;
        net.addEdge(ind(i1, j1, k1), ind(i2, j2, k2), 1);
        net.addEdge(ind(i2, j2, k2), ind(i1, j1, k1), 1);
    };
    rep(i, 0, 10) rep(j, 0, 10) rep(k, 0, 10) {
        add(i, j, k, i + 1, j, k);
        add(i, j, k, i, j + 1, k);
        add(i, j, k, i, j, k + 1);

        if (!i || i == 9) net.addEdge(ind(i, j, k), si, 1);
        if (!j || j == 9) net.addEdge(ind(i, j, k), si, 1);
        if (!k || k == 9) net.addEdge(ind(i, j, k), si, 1);
        
        if (def[i][j][k]) net.addEdge(so, ind(i, j, k), 6);
    }
    int res = net.calc(so, si);
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
