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
    int n;
    cin >> n;

    vector<string> s(n);
    rep(i, 0, n) cin >> s[i];

    if (s[0][0] == '*' || s[n - 1][n - 1] == '*')
        return void(cout << "0\n");

    vll dp(n + 1, 0);
    dp[n - 1] = 1;
    for (int j = n - 1; j >= 0; j--) {
        for (int i = n - 1; i >= 0; i--) {
            if (s[j][i] == '*') {
                dp[i] = 0;
                continue;
            }
            dp[i] += dp[i + 1];
            dp[i] %= mod;
        }
    }
    cout << dp[0] << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t = 1;
//    cin >> t;
    while (t--) solve();

    return 0;
}
