#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define vec vector
#define all(x) begin(x), end(x)
typedef long long ll;

void dfs(vec<vec<int>> &adj, bitset<100000> &vis, int u) {
    if (vis[u]) return;
    vis[u] = true;

    for (auto v : adj[u])
        dfs(adj, vis, v);
}

void solve() {
    int n, m;
    cin >> n >> m;

    vec<vec<int>> fore(n), back(n);
    rep(i, 0, m) {
        int u, v;
        cin >> u >> v, u--, v--;

        fore[u].push_back(v);
        back[v].push_back(u);
    }

    bitset<100000> vis;
    dfs(fore, vis, 0);
    rep(i, 0, n) {
        if (!vis[i]) return void(cout << "NO\n1 " << i + 1);
    }

    vis = 0;
    dfs(back, vis, 0);
    rep(i, 0, n) {
        if (!vis[i]) return void(cout << "NO\n" << i + 1 << " 1");
    }

    cout << "YES\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
//    cin >> t;
    while (t--) solve();

    return 0;
}
