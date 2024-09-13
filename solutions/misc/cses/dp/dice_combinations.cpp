#include <bits/stdc++.h>

using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define vec vector
typedef long long ll;
typedef long double ld;

const ll mod = 1000000007;

ll go(vec<ll> &dp, int n) {
    if (n == 0) return 1;

    ll &res = dp[n];
    if (res != -1) return res;
    res = 0;
    for (int i = 1; i <= min(n, 6); i++) {
        res += go(dp, n - i);
        res %= mod;
    }

    return res;
}

void solve() {
    int n;
    cin >> n;
    vec<ll> dp(n + 1, -1);
    ll res = go(dp, n);
    cout << res << endl;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
//    cin >> t; // uncomment for multiple cases
    while (t--) solve();

    return 0;
}
