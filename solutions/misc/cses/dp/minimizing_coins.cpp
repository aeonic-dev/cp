#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef vector<int> vi;

int n;
vi c;
vi dp;

int go(int x) {
    if (x == 0) return 0;

    auto &res = dp[x];
    if (res != -1) return res;

    res = 1e7;
    rep(i, 0, n) {
        if (c[i] <= x)
            res = min(res, 1 + go(x - c[i]));
    }
    return res;
}

void solve() {
    int x;
    cin >> n >> x;
    c = vi(n), dp = vi(x + 1, -1);
    rep(i, 0, n) cin >> c[i];

    auto res = go(x);
    if (res >= 1e7) cout << "-1\n";
    else cout << res << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
//    cin >> t;
    while (t--) solve();

    return 0;
}
