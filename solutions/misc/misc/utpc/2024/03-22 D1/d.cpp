#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef vector<int> vi;

void solve() {
    int n;
    cin >> n;
    vi r(n);
    vector<vi> adj(n);
    bitset<100000> ge;
    rep(i, 0, n) {
        cin >> r[i];
        if (i > 0 && r[i] >= r[0]) ge[i] = 1;
    }
    rep(i, 0, n - 1) {
        int u, v;
        cin >> u >> v, u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    auto dfs = [&](int u, int l, auto &dfs) -> pair<int, int> {
        int num = ge[u], res = 1;
        for (auto v : adj[u]) {
            if (v == l) continue;
            
            auto [numv, resv] = dfs(v, u, dfs);
            num += numv, res += resv;
        }
        
        if (!num) res = 0; // no nodes ge in the subtree
        else if (ge[u] && num <= 1) res--; // leaf nodes don't need to be asked

//        cout << "dfs(" << u + 1 << ", " << l + 1 << ") -> {" << num << ", " << res << "}\n";
        return {num, res};
    };
    
    auto [_, res] = dfs(0, -1, dfs);
    cout << max(res - 1, 0) << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    
    int t = 1;
//    cin >> t;
    while (t--) solve();
    
    return 0;
}
