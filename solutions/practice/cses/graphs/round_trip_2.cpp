#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef vector<ll> vll;

// Finds a cycle; returns the node the cycle starts/ends at
int dfs(int u, vector<vi> &adj, vi &par, bitset<100000> &vs, bitset<100000> &cyc) {
    if (vs[u]) return cyc[u] ? u : -1;
    vs[u] = cyc[u] = true;
    
    for (auto v : adj[u]) {
        if (v == u) continue;
        
        par[v] = u;
        int res = dfs(v, adj, par, vs, cyc);
        if (res != -1) return res;
    }
    
    cyc[u] = false;
    return -1;
};

void solve() {
    int n, m;
    cin >> n >> m;
    
    vector<vi> adj(n);
    rep(i, 0, m) {
        int u, v;
        cin >> u >> v, u--, v--;
        adj[u].push_back(v);
    }
    
    bitset<100000> vs, cyc;
    vi par(n, -1);
    
    rep(st, 0, n) {
        if (vs[st]) continue;
        
        cyc.reset();
        int end = dfs(st, adj, par, vs, cyc);
        if (end == -1) continue;
        
        stack<int> res;
        int cur = par[end];
        while (cur != -1 && cur != end)
            res.push(cur), cur = par[cur];
        res.push(end);
        
        cout << sz(res) + 1 << "\n";
        while (!res.empty()) cout << res.top() + 1 << " ", res.pop();
        cout << end + 1 << "\n";
        
        return;
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
