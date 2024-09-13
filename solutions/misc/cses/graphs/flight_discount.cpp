#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define vec vector
#define all(x) begin(x), end(x)
typedef long long ll;

void solve() {
    int n, m;
    cin >> n >> m;

    vec<vec<pair<int, ll>>> adj(n * 2);
    rep(i, 0, m) {
        int u, v, w;
        cin >> u >> v >> w, u--, v--;
        adj[u].emplace_back(v, w);
        adj[u].emplace_back(n + v, w / 2);
        adj[n + u].emplace_back(n + v, w);
    }

    vec<ll> dist(n * 2, LLONG_MAX);
    priority_queue<pair<ll, int>, vec<pair<ll, int>>, greater<>> q;
    dist[0] = 0, q.emplace(0, 0);

    while (!q.empty()) {
        auto [d, u] = q.top();
        q.pop();

        if (d != dist[u]) continue;
        for (auto [v, w] : adj[u]) {
            if (d + w < dist[v]) {
                dist[v] = d + w;
                q.emplace(d + w, v);
            }
        }
    }

    cout << dist[n * 2 - 1] << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
//    cin >> t;
    while (t--) solve();

    return 0;
}
