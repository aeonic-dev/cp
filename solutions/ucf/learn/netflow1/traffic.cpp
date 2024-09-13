#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;

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
    void popEdge(int a, int b) {
        adj[a].pop_back();
        adj[b].pop_back();
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
            } while (lvl[t]);
        return flow;
    }
    bool leftOfMinCut(int a) { return lvl[a] != 0; }
};

const ll inf = INT_MAX;
void solve() {
    int n, m;
    cin >> n >> m;
    
    Dinic gold(n);
    map<string, vector<tuple<int, int, int>>> edges;
    rep(i, 0, m) {
        string ustr, vstr, wstr, name;
        getline(cin, ustr, ',');
        getline(cin, vstr, ',');
        getline(cin, wstr, ',');
        getline(cin, name, '\n');
        
        int u = stoi(ustr), v = stoi(vstr), w = stoi(wstr);
        gold.addEdge(u, v, w);
        edges[name].emplace_back(u, v, w);
    }
    
    int old = gold.calc(0, n - 1);
    int max = 0;
    string max_name;
    for (auto &[name, adds] : edges) {
        Dinic g(n);
        for (auto &[str, adj] : edges) {
            if (str == name) {
                for (auto [u, v, w] : adj) g.addEdge(u, v, inf);
                continue;
            }
            for (auto [u, v, w] : adj) g.addEdge(u, v, w);
        }
        int flow = g.calc(0, n - 1);
        if (flow > max) {
            max = flow;
            max_name = name;
        }
    }
    cout << max_name << " " << max - old << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    
    int t = 1;
    cin >> t;
    while (t--) solve();
    
    return 0;
}
