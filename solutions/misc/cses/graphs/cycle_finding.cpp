#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define vec vector
#define all(x) begin(x), end(x)
typedef long long ll;

const ll inf = 1e16;

void solve() {
    int n, m;
    cin >> n >> m;

    vec<tuple<int, int, ll>> edges(m);
    rep(i, 0, m) {
        auto &[u, v, w] = edges[i];
        cin >> u >> v >> w;
        u--, v--;
    }

    vec<ll> dist(n, inf);
    vec<int> par(n, -1);

    int st;
    rep(i, 0, n) {
        st = -1;
        for (auto [u, v, w] : edges) {
            if (dist[u] + w < dist[v]) {
                dist[v] = max(dist[u] + w, -inf);
                par[st = v] = u;
            }
        }
    }
    if (st == -1) return void(cout << "NO\n");

    rep(i, 0, n) st = par[st];
    vec<int> path;
    while (st != -1 && (path.empty() || st != path.front()))
        path.push_back(st), st = par[st];
    reverse(all(path));
    path.push_back(path.front());

    cout << "YES\n";
    for (auto v : path) cout << v + 1 << ' ';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
//    cin >> t;
    while (t--) solve();

    return 0;
}
