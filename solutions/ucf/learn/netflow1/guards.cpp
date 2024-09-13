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

struct node {
    node *left = nullptr, *rght = nullptr;
    int lo, hi, md;
    ll sum = 0, lazy = -1;

    node(int lo, int hi) : lo(lo), hi(hi), md((lo + hi) / 2) {
        if (lo == hi) return;

        left = new node(lo, md);
        rght = new node(md + 1, hi);
    }

    ~node() {
        if (left) delete left;
        if (rght) delete rght;
    }

    void set(int l, int r, int v) {
        if (r < lo || l > hi) return;
        if (l <= lo && r >= hi) {
            lazy = v;
            sum = v * (hi - lo + 1);
            return;
        }

        if (lazy != -1) {
            left->set(lo, hi, lazy);
            rght->set(lo, hi, lazy);
            sum = left->sum + rght->sum;
            lazy = -1;
        }

        left->set(l, r, v);
        rght->set(l, r, v);
        sum = left->sum + rght->sum;
    }

    ll query(int l, int r) {
        if (r < lo || l > hi) return 0;
        if (l <= lo && r >= hi) return sum;

        if (lazy != -1) {
            left->set(lo, hi, lazy);
            rght->set(lo, hi, lazy);
            sum = left->sum + rght->sum;
            lazy = -1;
        }

        return left->query(l, r) + rght->query(l, r);
    }
};


void solve() {
    int n;
    // int tc = 0;
    while (cin >> n, n) {
        int so = n + 48, si = so + 1;
        vector<bitset<48>> adj(n);
        vi ms(n);
        rep(i, 0, n) {
            int k;
            cin >> k >> ms[i];

            node *st = new node(0, 48 * 60 + 1);
            rep(_, 0, k) {
                int s_h, s_m, e_h, e_m;
                scanf("%d:%d", &s_h, &s_m);
                scanf("%d:%d", &e_h, &e_m);

                if (s_h == e_h && s_m == e_m) {
                    st->set(0, st->hi, 1);
                    continue;
                }

                int s = s_h * 60 + s_m,
                    e = e_h * 60 + e_m - 1;
                if (e < s) {
                    st->set(0, e, 1);
                    st->set(s, st->hi, 1);
                } else {
                    st->set(s, e, 1);
                }
            }
            rep(sh, 0, 48) {
                if (st->query(sh * 30, sh * 30 + 29) == 30) {
                    adj[i][sh] = 1;
                }
            }
            delete st;

        }

        int res = 0;
        rep(num, 1, n + 1) {
            Dinic net(n + 48 + 2);
            rep(i, 0, n) {
                net.addEdge(so, i, ms[i] / 30);
                rep(sh, 0, 48) {
                    if (adj[i][sh]) {
                        net.addEdge(i, n + sh, 1);
                    }
                }
            }

            rep(sh, 0, 48) net.addEdge(n + sh, si, num);
            int flow = net.calc(so, si);

            vector<vector<pair<int, int>>> flows(48);
            rep(u, 0, n) {
                for (auto e : net.adj[u]) {
                    if (e.to < u || e.to < n) continue;
                    if (e.flow() <= 0) continue;

                    flows[e.to - n].emplace_back(u, e.flow());
                }
            }

            if (flow >= num * 48) res = num;
            else break;
        }
        cout << res << "\n";
    }
}

int main() {
    // cin.tie(0)->sync_with_stdio(0);
    // cin.exceptions(cin.failbit);

    int t = 1;
    // cin >> t;
    while (t--) solve();

    return 0;
}
