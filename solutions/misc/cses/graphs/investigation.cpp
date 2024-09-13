#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define vec vector
#define all(x) begin(x), end(x)
typedef long long ll;

const ll mod = 1e9 + 7;
void solve() {
    int n, m;
    cin >> n >> m;

    vec<vec<pair<int, ll>>> adj(n);
    rep(i, 0, m) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u - 1].emplace_back(v - 1, w);
    }

    bitset<100000> vis;
    vec<ll> dist(n, LLONG_MAX), mins(n, 0); // min dist to node; # of min paths to node
    vec<int> mine(n, INT_MAX), maxe(n, -1); // min/max # of edges on path to node
    priority_queue<tuple<ll, int>, vec<tuple<ll, int>>, greater<>> q; // {dist, node}

    dist[0] = 0, mins[0] = 1, mine[0] = maxe[0] = 0;
    q.emplace(0, 0);
    while (!q.empty()) {
        auto [d, u] = q.top();
        q.pop();

        if (vis[u]) continue;
        vis[u] = true;

        for (auto [v, w] : adj[u]) {
            if (d + w == dist[v]) {
                mins[v] = (mins[v] + mins[u]) % mod;
                mine[v] = min(mine[v], mine[u] + 1);
                maxe[v] = max(maxe[v], maxe[u] + 1);
            }

            if (d + w < dist[v]) {
                dist[v] = d + w;
                mins[v] = mins[u];
                mine[v] = mine[u] + 1;
                maxe[v] = maxe[u] + 1;
                q.emplace(d + w, v);
            }
        }
    }

    cout << dist[n - 1] << ' '
         << mins[n - 1] << ' '
         << mine[n - 1] << ' '
         << maxe[n - 1] << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
//    cin >> t;
    while (t--) solve();

    return 0;
}
