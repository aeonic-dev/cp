#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define vec vector
#define all(x) begin(x), end(x)
typedef long long ll;

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
    bool connected() {
        rep(i, 1, par.size()) {
            if (find(i) != find(i - 1)) return false;
        }
        return true;
    }
};

void solve() {
    int n, m;
    cin >> n >> m;

    vec<tuple<ll, int, int>> adj(m);
    rep(i, 0, m) {
        auto &[w, u, v] = adj[i];
        cin >> u >> v >> w, u--, v--;
    }
    dsu ds(n);

    ll total = 0;
    sort(adj.begin(), adj.end());
    for (auto [w, u, v] : adj) {
        if (!ds.join(u, v)) continue;
        total += w;
    }

    if (ds.connected()) cout << total << '\n';
    else cout << "IMPOSSIBLE\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
//    cin >> t;
    while (t--) solve();

    return 0;
}
