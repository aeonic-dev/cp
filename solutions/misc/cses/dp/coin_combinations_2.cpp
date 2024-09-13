#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;

const ll mod = 1e9 + 7;
void solve() {
    int n, x;
    cin >> n >> x;

    vi c(n);
    vll dp(x + 1, 0);
    rep(i, 0, n) cin >> c[i];

    dp[0] = 1;
    for (int i = n - 1; i >= 0; i--) {
        rep(j, 1, x + 1) {
            if (c[i] > j) continue;
            dp[j] += dp[j - c[i]];
            dp[j] %= mod;
        }
    }

    auto res = dp[x];
    cout << res << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
//    cin >> t;
    while (t--) solve();

    return 0;
}
