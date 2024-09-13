#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;

void solve() {
    int n, x;
    cin >> n >> x;

    vi w(n), v(n);
    rep(i, 0, n) cin >> w[i];
    rep(i, 0, n) cin >> v[i];

    vll dp(x + 1, 0), dp2(x + 1, 0);
    for (int i = n - 1; i >= 0; i--) {
        rep(j, 1, x + 1) {
            if (w[i] > j) continue;
            dp2[j] = max(dp[j],
                         dp[j - w[i]] + v[i]);
        }
        copy(all(dp2), dp.begin());
    }
    cout << dp[x] << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
//    cin >> t;
    while (t--) solve();

    return 0;
}
