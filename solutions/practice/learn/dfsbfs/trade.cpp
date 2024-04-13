#include <bits/stdc++.h>

using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define vec vector
typedef long long ll;
typedef long double ld;

void solve() {
    int n, s;
    cin >> n >> s;
    vec<int> val(s);
    rep(i, 0, s) cin >> val[i];

    vec<vec<int>> adj(s);
    rep(i, 0, n) {
        int d, t, tmp;
        cin >> d >> t;
        rep(j, 0, t) {
            cin >> tmp;
            adj[tmp - 1].push_back(d - 1);
        }
    }

    bitset<1000> vs;
    queue<int> q;
    q.push(0);

    int max = val[0];
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        
        vs[u] = 1;
        max = ::max(max, val[u]);

        for (auto v : adj[u]) {
            if (!vs[v]) q.push(v);
        }
    }

    cout << max << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
    cin >> t; // uncomment for multiple cases
    while (t--) solve();

    return 0;
}
