#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define vec vector
#define all(x) begin(x), end(x)
typedef long long ll;

int cycle_len(vec<int> &par, int st, int u, int d = 0) {
    if (d && u == st) return d;
    return cycle_len(par, st, par[u], d + 1);
}

// {value, cycle sentinel}
pair<int, int> dfs(vec<int> &par, vec<int> &res, bitset<200000> &vis, int u) {
    if (res[u] != -1) return {res[u], -1};
    if (par[u] == u) {
        vis[u] = true;
        return {res[u] = 0, -1};
    }

    if (vis[u]) {
        // visited but no value = cycle here
        int len = cycle_len(par, u, par[u]);
        return {len, u};
    }
    vis[u] = true;

    auto ret = dfs(par, res, vis, par[u]);
    if (ret.second == -1) return {res[u] = ret.first + 1, -1}; // not in a cycle
    return {res[u] = ret.first, u == ret.second ? -1 : ret.second}; // u is part of a cycle
}

void solve() {
    int n;
    cin >> n;
    vec<int> par(n);
    rep(i, 0, n) cin >> par[i], par[i]--;

    vec<int> res(n, -1);
    bitset<200000> vis;
    rep(i, 0, n) {
        if (!vis[i]) dfs(par, res, vis, i);
    }
    for (auto r : res) cout << max(r + 1, 1) << ' ';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
//    cin >> t;
    while (t--) solve();

    return 0;
}
