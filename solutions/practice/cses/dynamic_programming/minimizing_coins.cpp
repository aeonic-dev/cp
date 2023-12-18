#include <bits/stdc++.h>

using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define vec vector
typedef long long ll;
typedef long double ld;

const ll inf = INT_MAX;

ll go(vec<vec<ll>> &dp, vec<int> &c, ll x, int i = 0) {
    if (x == 0) return 0;
    if (i >= c.size()) return inf;
    auto &res = dp[x][i];
    if (res != -1) return res;
    res = inf;

    int num = 0;
    while (c[i] * num <= x) {
        res = min(res, num + go(dp, c, x - c[i] * num, i + 1));
        num++;
    }

    return res;
}

void solve() {
    int n, x;
    cin >> n >> x;
    vec<int> c(n);
    rep(i, 0, n) cin >> c[i];

    vec<vec<ll>> dp(x + 1, vec<ll>(n, -1));
    cout << go(dp, c, x) << endl;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
//    cin >> t; // uncomment for multiple cases
    while (t--) solve();

    return 0;
}
