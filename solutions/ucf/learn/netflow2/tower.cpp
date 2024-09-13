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

struct P {
    int x, y;
    P(int x = 0, int y = 0) : x(x), y(y) {}
    P operator+(const P &p) const { return {x + p.x, y + p.y}; }
    P operator-(const P &p) const { return {x - p.x, y - p.y}; }
    int dist2() const { return x * x + y * y; }
};

int tc = 0;
void solve() {
    int n;
    cin >> n;
    cout << "Case #" << ++tc << ": ";

    // {pos, rad, score}
    vector<tuple<P, int, ll>> pts(n);
    ll res = 0;
    rep(i, 0, n) {
        auto &[p, r, s] = pts[i];
        cin >> p.x >> p.y >> r >> s;
        if (s > 0) res += s;
    }

    vector<vi> adj(n);
    rep(i, 0, n) {
        auto &[p1, r1, s1] = pts[i];
        rep(j, 0, n) {
            if (i == j) continue;

            auto &[p2, r2, s2] = pts[j];
            if ((p1 - p2).dist2() <= r1 * r1) {
                adj[i].push_back(j);
            }
        }
    }

    int so = n, si = n + 1;
    Dinic net(n + 2);
    rep(i, 0, n) {
        auto &[p1, r1, s1] = pts[i];

        if (s1 > 0) net.addEdge(so, i, s1);
        else net.addEdge(i, si, -s1);

        for (int j : adj[i]) net.addEdge(i, j, inf);
    }
    ll flow = net.calc(so, si);

    res -= flow;
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
