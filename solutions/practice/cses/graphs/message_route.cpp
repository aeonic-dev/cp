#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define vec vector
#define all(x) begin(x), end(x)
typedef long long ll;

typedef pair<int, ll> P;
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

    map<int, int> par;
    vec<ll> dist(n, LLONG_MAX);
    queue<pair<int, int>> q;
    dist[0] = 0, q.emplace(0, 0);

    while (!q.empty()) {
        auto p = q.front();
        int u = p.first, d = p.second;
        q.pop();

        if (d != dist[u]) continue;
        for (auto v : adj[u]) {
            if (d + 1 < dist[v]) {
                dist[v] = d + 1, par[v] = u;
                q.emplace(v, d + 1);
            }
        }
    }

    if (dist[n - 1] == LLONG_MAX) return void(cout << "IMPOSSIBLE");

    cout << dist[n - 1] + 1 << "\n1 ";
    stack<int> path;

    int cur = n - 1;
    while (cur) path.push(cur), cur = par[cur];
    while (!path.empty()) cout << path.top() + 1 << ' ', path.pop();
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
//    cin >> t;
    while (t--) solve();

    return 0;
}
