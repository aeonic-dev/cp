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
    int n, m;
    ll D, F, B;
    cin >> m >> n >> D >> F >> B;
    vector<string> gr(n);
    rep(i, 0, n) cin >> gr[i];

    int so = n * m, si = so + 1;
    auto index = [&](int i, int j) { return i * m + j; };
    Dinic net(n * m + 2);
    ll res = 0;

    rep(i, 0, n) {
        rep(j, 0, m) {
            if (i < n - 1) {
                net.addEdge(index(i, j), index(i + 1, j), B);
                net.addEdge(index(i + 1, j), index(i, j), B);
            }
            if (j < m - 1) {
                net.addEdge(index(i, j), index(i, j + 1), B);
                net.addEdge(index(i, j + 1), index(i, j), B);
            }

            if (!i || i == n - 1 || !j || j == m - 1) {
                if (gr[i][j] == '.') res += F;
                gr[i][j] = '#';

                net.addEdge(so, index(i, j), inf);
                continue;
            }

            if (gr[i][j] == '#') net.addEdge(so, index(i, j), D);
            else net.addEdge(index(i, j), si, F);
        }
    }
    res += net.calc(so, si);
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
