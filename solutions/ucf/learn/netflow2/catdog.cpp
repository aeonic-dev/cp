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
        for (int& i = ptr[v]; i < sz(adj[v]); i++) {
            Edge& e = adj[v][i];
            if (lvl[e.to] == lvl[v] + 1)
                if (ll p = dfs(e.to, t, min(f, e.c))) {
                    e.c -= p, adj[e.to][e.rev].c += p;
                    return p;
                }
        }
        return 0;
    }
    ll calc(int s, int t) {
        ll flow = 0; q[0] = s;
        rep(L,0,31) do { // 'int L=30' maybe faster for random data
            lvl = ptr = vi(sz(q));
            int qi = 0, qe = lvl[s] = 1;
            while (qi < qe && !lvl[t]) {
                int v = q[qi++];
                for (Edge e : adj[v])
                    if (!lvl[e.to] && e.c >> (30 - L))
                        q[qe++] = e.to, lvl[e.to] = lvl[v] + 1;
            }
            while (ll p = dfs(s, t, LLONG_MAX)) flow += p;
        } while (lvl[t]);
        return flow;
    }
    bool leftOfMinCut(int a) { return lvl[a] != 0; }
};

const ll inf = 1e8;
void solve() {
    int n, m, e;
    cin >> n >> m >> e;

    // catlovers[i] = {cat stay, dog go}
    // doglovers[i] = {cat go, dog stay}
    vector<pair<int, int>> catl, dogl;
    rep(_, 0, e) {
        string s_a, s_b;
        cin >> s_a >> s_b;

        int a = stoi(s_a.substr(1)) - 1;
        int b = stoi(s_b.substr(1)) - 1;
        if (s_a[0] == 'C') catl.emplace_back(a, b);
        else dogl.emplace_back(b, a);
    }
    int c = sz(catl), d = sz(dogl);

    int so = c + d, si = so + 1;
    Dinic net(c + d + 2);
    rep(i, 0, c) net.addEdge(so, i, 1);
    rep(j, 0, d) net.addEdge(c + j, si, 1);
    rep(i, 0, c) {
        auto [c_a, d_a] = catl[i];
        rep(j, 0, d) {
            auto [c_b, d_b] = dogl[j];
            if (c_a == c_b || d_a == d_b) {
                net.addEdge(i, c + j, inf);
            }
        }
    }

    int res = net.calc(so, si);
    cout << e - res << "\n";
    // cout << "e = " << e << ", flow = " << res << "\n\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
    cin >> t;
    while (t--) solve();

    return 0;
}
