#include <bits/stdc++.h>

using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define vec vector
typedef long long ll;
typedef long double ld;

int tc = 0;
void solve() {
    cout << "City #" << ++tc << "\n";
    int n;
    cin >> n;
    vec<vec<int>> adj(n);
    rep(i, 0, n) {
        int l, v;
        cin >> l;
        rep(j, 0, l) {
            cin >> v;
            adj[i].push_back(v - 1);
            adj[v - 1].push_back(i);
        }
    }

    int c;
    cin >> c;
    rep(i, 0, c) {
        int cl;
        cin >> cl;

        bitset<50> vs;
        vs[--cl] = 1;
        queue<int> q;
        q.push(0);

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            vs[u] = 1;

            for (auto v: adj[u]) {
                if (!vs[v]) q.push(v);
            }
        }

        if (vs.count() < n) cout << "yes\n";
        else cout << "no\n";
    }
    cout << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
    cin >> t; // uncomment for multiple cases
    while (t--) solve();

    return 0;
}
