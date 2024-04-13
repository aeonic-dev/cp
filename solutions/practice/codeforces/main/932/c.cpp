#include <bits/stdc++.h>
using namespace std;

#define int long long
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;

void solve() {
    int n, l;
    cin >> n >> l;

    vi a(n), b(n);
    rep(i, 0, n) cin >> a[i] >> b[i];

    vector<vector<pair<ll, int>>> adj(n); // {w, v]
    rep(i, 0, n) {
        rep(j, 0, n) {
            if (i == j) continue;

            ll c = abs(b[i] - b[j]);
            adj[i].emplace_back(a[j] + c, j);
            adj[j].emplace_back(a[i] + c, i);
        }
    }
    rep(i, 0, n) sort(all(adj[i]));

    int res = 0;
    rep(st, 0, n) {
        ll m = a[st];
        if (m > l) continue;

        set<int> s{st};
        int u = st;
        while (1) {
            const auto &vs = adj[u];
            rep(i, 0, n - 1) {
                auto [w, v] = vs[i];
                if (m + w > l) break;
                if (s.count(v)) continue;

                s.insert(u = v);
                m += w;
                goto next; // lol, lmao
            }
            break; // can't take any if we got to here
            next:;
        }
        res = max(res, sz(s));
    }
    cout << res << "\n";
}

signed main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
    cin >> t;
    while (t--) solve();

    return 0;
}
