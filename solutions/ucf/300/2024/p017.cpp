#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
typedef long long ll;
typedef vector<int> vi;

void solve() {
    int n;
    cin >> n;
    vector<bitset<500>> adj(n);
    rep(i, 0, n) {
        rep(j, 0, n) {
            int x;
            cin >> x, adj[i][j] = x;
        }
    }

    // inclusive [l, r]
    vector<vi> dp(n, vi(n, -1));
    auto go = [&](int l, int r, auto &go) -> int {
        if (l >= r) return 0;

        int &res = dp[l][r];
        if (res != -1) return res;

        res = go(l, r - 1, go);
        rep(i, l, r) {
            res = max(res,
                      go(l, i - 1, go)
                              + go(i + 1, r - 1, go)
                              + adj[i][r]);
        }
        return res;
    };

    int res = go(0, n - 1, go);
    cout << res << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
    // cin >> t;
    while (t--) solve();

    return 0;
}
