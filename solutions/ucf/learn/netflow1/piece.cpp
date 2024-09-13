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
    cin >> n >> m;

    vector<string> gr(n);
    int num_black = 0, num_white = 0;
    for (auto &s : gr) {
        cin >> s;
        num_black += count(all(s), 'B');
        num_white += count(all(s), 'W');
    }
    if (num_black * 2 != num_white) return void(cout << "NO\n");

    int so = 2 * n * m, si = so + 1;
    Dinic net(2 * n * m + 2);
    rep(i, 0, n) {
        rep(j, 0, m) {
            int l = i * m + j, r = n * m + l;
            if (gr[i][j] == 'B') {
                net.addEdge(l, r, 1);
                continue;
            }
            if (gr[i][j] != 'W') continue;

            if (i % 2) net.addEdge(so, l, 1);
            else net.addEdge(r, si, 1);

            if (i && gr[i - 1][j] == 'B') {
                if (i % 2) net.addEdge(l, l - m, 1);
                else net.addEdge(r - m, r, 1);
            }
            if (i < n - 1 && gr[i + 1][j] == 'B') {
                if (i % 2) net.addEdge(l, l + m, 1);
                else net.addEdge(r + m, r, 1);
            }
            if (j && gr[i][j - 1] == 'B') {
                if (i % 2) net.addEdge(l, l - 1, 1);
                else net.addEdge(r - 1, r, 1);
            }
            if (j < m - 1 && gr[i][j + 1] == 'B') {
                if (i % 2) net.addEdge(l, l + 1, 1);
                else net.addEdge(r + 1, r, 1);
            }
        }
    }

    int res = net.calc(so, si);
    if (res == num_black) cout << "YES\n";
    else cout << "NO\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
    cin >> t;
    while (t--) solve();

    return 0;
}
