#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define vec vector
#define all(x) begin(x), end(x)
typedef long long ll;

const ll mod = 1e9 + 7;
ll dfs(vec<vec<int>> &adj, vec<vec<ll>> &dp, bitset<20> vs, int u) {
    if (u == 0) return vs.count() == adj.size() - 1;
    vs[u] = true;

    auto &res = dp[u][vs.to_ulong()];
    if (res != -1) return res;

    res = 0;
    for (auto v : adj[u]) {
        if (vs[v]) continue;

        res += dfs(adj, dp, vs, v);
        res %= mod;
    }
    return res;
}

void solve() {
    int n, m;
    cin >> n >> m;

    vec<vec<int>> adj(n);
    rep(i, 0, m) {
        int u, v;
        cin >> u >> v;
        adj[v - 1].push_back(u - 1);
    }

    vec<vec<ll>> dp(n, vec<ll>(1 << n, -1));
    ll res = dfs(adj, dp, 0, n - 1);
    cout << res << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
//    cin >> t;
    while (t--) solve();

    return 0;
}
