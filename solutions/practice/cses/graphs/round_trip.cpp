#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define vec vector
#define all(x) begin(x), end(x)
typedef long long ll;

bool dfs(vec<vec<int>> &adj, bitset<100000> &vs, vec<int> &par, int n, int u, int l) {
    if (vs[u]) return false;
    vs[u] = true;

    par.push_back(u);
    for (auto v : adj[u]) {
        if (v == l) continue;

        if (vs[v]) return par.push_back(v), true;
        if (dfs(adj, vs, par, n, v, u)) return true;
    }
    par.pop_back();
    return false;
}

void solve() {
    int n, m;
    cin >> n >> m;

    vec<vec<int>> adj(n);
    rep(i, 0, m) {
        int u, v;
        cin >> u >> v, u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    bitset<100000> vs;
    vec<int> par;
    rep(st, 0, n) {
        if (!vs[st] && dfs(adj, vs, par, n, st, st)) {
            rep(i, 0, par.size()) {
                if (par[i] == par.back()) {
                    cout << par.size() - i << '\n';
                    rep(j, i, par.size()) cout << par[j] + 1 << ' ';
                    return;
                }
            }
        }
    }

    cout << "IMPOSSIBLE\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
//    cin >> t;
    while (t--) solve();

    return 0;
}
