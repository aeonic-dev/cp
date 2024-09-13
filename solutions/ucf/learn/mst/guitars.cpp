#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef vector<int> vi;

struct dsu {
    vector<int> par, siz;
    dsu(int n) {
        siz = par = vector<int>(n, 1);
        iota(par.begin(), par.end(), 0);
    }
    int find(int a) {
        if (par[a] != a) par[a] = find(par[a]);
        return par[a];
    }
    bool join(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return false;
        if (siz[a] < siz[b]) swap(a, b);
        par[b] = a;
        siz[a] += siz[b];
        return true;
    }
};

void solve() {
    int n, m;
    cin >> n >> m;
    
    vector<vi> adj(n);
    vector<tuple<ll, int, int>> edges(m);
    rep(i, 0, m) {
        auto &[w, u, v] = edges[i];
        cin >> u >> v >> w, u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    bitset<50> vis;
    auto dfs = [&](int u, auto &dfs) {
        if (vis[u]) return;
        vis[u] = true;
        for (int v : adj[u]) dfs(v, dfs);
    };
    dfs(0, dfs);
    rep(i, 0, n) if (!vis[i]) return void(cout << "-1\n");
    
    dsu ds(n);
    ll res = 0;
    sort(edges.begin(), edges.end());
    for (auto [w, u, v] : edges) {
        if (!ds.join(u, v)) continue;
        res += w;
    }
    
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
