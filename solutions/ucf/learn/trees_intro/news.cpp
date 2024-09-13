#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;

void solve() {
    int n, tmp;
    cin >> n;
    vector<vi> adj(n);
    rep(i, 1, n) {
        cin >> tmp;
        adj[tmp].push_back(i);
    }
    vi siz(n);
    auto dfs_siz = [&](int u, auto &f) -> int {
        int res = 1;
        for (int v : adj[u]) res += f(v, f);
        return siz[u] = res;
    };
    dfs_siz(0, dfs_siz);
    for (vi &vec : adj) {
        sort(all(vec), [&](int u, int v) {
            return siz[u] > siz[v];
        });
    }
    auto dfs = [&](int u, auto &f) -> int {
        int res = 0;
        rep(i, 0, sz(adj[u])) {
            int v = adj[u][i];
            res = max(res, 1 + i + f(v, f));
        }
        return res;
    };
    int res = dfs(0, dfs);
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
