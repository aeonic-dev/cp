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
    int n, m;
    cin >> n >> m;
    vi s(n);
    rep(i, 0, n) cin >> s[i];

    vll dp(m + 2, 0), dp2(m + 2, 0);
    if (s[n - 1] == 0) {
        rep(i, 1, m + 1) dp[i] = 1;
    } else dp[s[n - 1]] = 1;

    for (int i = n - 2; i >= 0; i--) {
        int v = s[i];
        rep(j, 1, m + 1) {
            if (v == 0 || j == v)
                dp2[j] = ((dp[j - 1] + dp[j]) % mod + dp[j + 1]) % mod;
            else dp2[j] = 0;
        }
        swap(dp, dp2);
    }

    ll res = 0;
    rep(i, 1, m + 1) res = (res + dp[i]) % mod;
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
