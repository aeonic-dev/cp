#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;

const ll mod = 1e9 + 7;
int n;
vi c;
vll dp;

ll go(int x) {
    if (x == 0) return 1;

    auto &res = dp[x];
    if (res != -1) return res;

    res = 0;
    rep(i, 0, n) {
        if (c[i] <= x)
            res += go(x - c[i]), res %= mod;
    }
    return res;
}

void solve() {
    int x;
    cin >> n >> x;
    c = vi(n), dp = vll(x + 1, -1);
    rep(i, 0, n) cin >> c[i];

    auto res = go(x);
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
